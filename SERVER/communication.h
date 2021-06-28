#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
using namespace std;
#define myOK 0
#define myERROR -1

/* 信息發送的操作符 */
#define INITIAL 1
#define SEND 2 // 询问要不要发这个文件
#define SEND_FILE 3 // 发文件（真的文件）
#define REMOVE 4
#define RENAME 5
#define CHANGE 6 // 修改
#define SURE_GET 7 // 确认要收这个文件
#define NOT_GET -1 // 不真正接收此文件
#define BIND_DIR 8 // 綁定目錄
#define RM_BIND_DIR 9 // 目錄解綁
#define FINISH 10 // 完成
#define LOGIN 11
#define LOGOUT 12
#define REGIST 13
#define FINISH_INITIAL 14
#define CONFIGFILE 15 // 记录目录的配置文件内容
/* 信息發送字符串的信息 */
#define msgno_begin 0 // string中对应的位置
#define op_begin 1
#define flagfile_begin 2
#define SENDFILESIZE 1024 // 每次发送的文件大小
#define SENDSIZE 2048
#define usercorrect_begin 3 // 判断用户账号密码是否合法，包括注册、登录时都要用到
#define MAXMESSAGE 128
// 文件名，路径，md5码之间用\t作为分割，因为长度不定（呜呜
// 如果是传输文件，后面还跟文件内容
struct netdisk_message{
    int no; // 事件编号，用来确认是不是完成了,或者确认要不要真正传输文件
    int op; // 操作码
    bool is_file; // true表示是文件
    string md5=NULL; // md5码
    string path=NULL; // 路径（不包括文件名
    string filename=NULL; // 文件名
    string content=NULL; // 内容
    string username=NULL;
    string userid=NULL;
    string passwd=NULL;
    bool user_correct;
    netdisk_message(){
        ;
    }
    netdisk_message(int no,int op,string filename,bool is_file,string path,string md5,string content,string username,string useerid,string passwd,bool user_correct){
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
    bool message_count_use[MAXMESSAGE]; //标记该消息号是否用过
    // string ip;
    // int port;
    int connfd;
    bool ConnectError;
    string message_to_string(netdisk_message & msg);
    netdisk_message string_to_message(string &msg);
public:
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
    // (注册)->登录->

    
};
