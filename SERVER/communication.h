#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <vector>
#include <queue>
using namespace std;
#define myOK 0
#define myERROR -1

/* 信息發送的操作符 */
#define INITIAL_CLIENT 1
#define INITIAL_SERVER 17
#define SEND 2 // 询问要不要发这个文件
#define SEND_FILE 3 // 发文件（真的文件）
#define REMOVE 4
#define RENAME 5
#define CHANGE 6 // 修改
#define SURE_GET 7 // 确认要收这个文件
#define NOT_GET 20 // 不真正接收此文件
#define EXIST 21 // 初始化比对时，完全相同
#define BIND_DIR 8 // 綁定目錄
#define RM_BIND_DIR 9 // 目錄解綁
#define FINISH 10 // 完成
#define LOGIN 11
#define LOGOUT 12
#define REGIST 13
#define FINISH_INITIAL 14
#define SENDCONFIG 15 // 发送记录目录的配置文件内容
#define GETCONFIG 16 // 索取初始化目录结构
/* 处理未完成的异常事件 */
#define PROCSEXCP 18
/* 开始同步状态 */
#define NORMAL 19
/* 初始等待询问状态 */
#define INITIAL_CONSULT 22
/* 信息發送字符串的信息 */
#define msgno_begin 0 // string中对应的位置
#define op_begin 1
#define flagtail_begin 2
#define flagfile_begin 3
#define SENDFILESIZE 1024 // 每次发送的文件大小
#define SENDSIZE 2048
#define usercorrect_begin 2 // 判断用户账号密码是否合法，包括注册、登录时都要用到
#define MAXMESSAGE 128
// 文件名，路径，md5码之间用\t作为分割，因为长度不定（呜呜
// 如果是传输文件，后面还跟文件内容
struct netdisk_message{
    int no; // 事件编号，用来确认是不是完成了,或者确认要不要真正传输文件
    int op; // 操作码
    bool is_tail; // 发送文件时，是不是到最尾部一段了
    bool is_file; // true表示是文件
    string md5; // md5码
    string path; // 路径（不包括文件名
    string filename; // 文件名
    string content; // 内容
    string username;
    string userid;
    string passwd;
    bool user_correct;
    netdisk_message(){
        ;
    }
    netdisk_message(int no,int op,string filename,bool is_file,bool is_tail,string path,string md5,string content,string username,string useerid,string passwd,bool user_correct){
        this->no=no;
        this->op=op;
        this->filename=filename;
        this->is_file=is_file;
        this->md5=md5;
        this->content=content;
        this->path=path;
        this->username=username;
        this->userid=userid;
        this->passwd=passwd;
        this->user_correct=user_correct;
    }
};

// 负责针对某个客户端的通信，使用 Communication(int connfd);传入连接好的句柄
class Communication {
private:
    vector <netdisk_message> msg_doing; // 已经发送但还没有收到finish的事件
    queue <file> initialfiles; // 初始要同步的文件
    bool message_count_use[MAXMESSAGE]; // 标记该消息号是否用过
    // 状态，用op表示
    int STATE;
    int connfd;
    bool ConnectError;
    string message_to_string(netdisk_message & msg);
    netdisk_message string_to_message(string &msg);
public:
    // 用户id
    string userid;
    string configname;
    string rootpath;
    // 與服務端鏈接是否錯誤
    bool connecterror();
    // no表示指定消息序号，如果不指定则随机生成
    // 发送配置文件
    int send_configmessage(int op,string filename,string content,int no=-1);
    // 發送信息
    int send_message(int op,string filename,bool is_file,string path="",string md5="",string content="",int no=-1);
    // 发送用户登录、登出、注册信息
    int send_usermessage(int op,string username,string useri,string passwd,bool user_correct,int no=-1);   
    // 初始化類類型
    Communication(int connfd);
    // 斷開鏈接
    int disconnection();
    ~Communication();
    // 接受來自服務端的信息，並返回到recv_content
    int recv_message(netdisk_message &recv_content);
    // 状态转移函数，进行初始化的阶段性转移
    // (注册)->登录->发送目录配置文件(如果没有，则客户端要求初始化一个目录结构，并发给服务端)->
    // -> 接收客户端的逐个文件询问，没有的就让客户端上传 -> 服务端向客户端发文件->
    // -> 遗留的未完成事件(异常表中)的处理
    // 开始等待各种随机事件，如绑定目录，增删改
    // 如果中途断网了，从登录开始重新走
    int state_next(netdisk_message msg);
    int state_rst();
    // 接收到登录消息后，确认账号密码对不对，如果对，则把用户名发给客户端，并且把id存到类的数据成员userid里
    int procs_login(netdisk_message msg);
    // 发配置文件
    int send_cfg();
    // 下列两个函数的msg包括要发送的文件的除完整内容外的所有信息
    // 发送文件
    int sendfile(netdisk_message msg,string &content);
    // 接收文件，返回已经接收的字节
    int recvfile(netdisk_message msg);
};
