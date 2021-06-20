#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#endif // COMMUNICATION_H
#include <iostream>
#include <string>
#include <winsock2.h>
using namespace std;
#define myOK 0
#define myERROR -1
#define INITIAL 1
#define SEND 2 // 询问要不要发这个文件
#define SEND_FILE 3 // 发文件（真的文件）
#define REMOVE 4
#define RENAME 5
#define CHANGE 6 // 修改
#define SURE_GET 7 // 确认要收这个文件
#define NOT_GET -1
#define FINISH 8 // 完成
#define msgno_begin 0 // string中对应的位置
#define op_begin 1
#define flagfile_begin 2
#define SENDSIZE 1024 // 每次发送的文件大小
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
    netdisk_message(){
        ;
    }
    netdisk_message(int no,int op,string filename,bool is_file,string path,string md5,string content){
        this->no=no;
        this->op=op;
        this->filename=filename;
        this->is_file=is_file;
        this->md5=md5;
        this->content=content;
        this->path=path;
    }
};
// 负责联网和通信，使用 Communication(string ip,string port); 初始化，并自动连接
class Communication {
private:
    int message_count=0;
    string ip;
    int port;
    SOCKET sclient;
    string message_to_string(netdisk_message & msg);
    netdisk_message string_to_message(string &msg);
public:

    int send_message(int op,string filename,bool is_file,string path="",string md5="",string content="");
    Communication(string ip,int port);
    int connection();

};
