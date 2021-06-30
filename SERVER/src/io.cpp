#include "../include/Communication.h"
#include "../include/Database.h"
#include "../include/crud.h"
#include "../include/server.h"
#include<sstream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
// 发送文件
int Communication::sendfile(netdisk_message msg)
{
    netdisk_message msgtemp;
    stringstream ss;
    ss<<this->rootpath<<this->userid<<msg.path;
    string fullFileName = ss.str();
    cout<<"debug message: in sendfilefunction, fullFileName is "<<fullFileName<<endl;
    int orifd = open(fullFileName.c_str(), O_RDONLY);
    char buffer[1024];
    read(orifd, buffer, 1024);
    close(orifd);
    buffer[32]='\0';
    stringstream ss2;
    ss2<<FILEPOOL<<buffer;
    string realFileName = ss2.str();
    int realfd = open(realFileName.c_str(), O_RDONLY);
    int readret = read(realfd, buffer, 1024);
    while(true){
        string content;
        for(int i = 0; i < readret;++i){
            content += buffer[i];
        }
        if(readret == 1024){
            send_message(SEND_FILE,msg.filename,true,msg.path,msg.md5, content,msg.no,false);
            if(recv_message(msgtemp)==myERROR){
                /* 写到异常表里 */
                return myERROR;
            }
        }
        else{
            send_message(SEND_FILE,msg.filename,true,msg.path,msg.md5, content,msg.no,true);
            if(recv_message(msgtemp)==myERROR){
                /* 写到异常表里 */
                return myERROR;
            }
            break;
        }
        readret = read(realfd, buffer, 1024);
    }
    close(fd);
    return myOK;
}
// 接收文件，返回已经接收的字节
int Communication::recvfile(netdisk_message msg)
{
    // 写用户目录下的文件
    stringstream ss;
    ss<<this->rootpath<<this->userid<<msg.path;
    string fullFileName = ss.str();
    ofstream outfile(fullFileName, ios::out);
    outfile<<msg.md5;
    outfile.close();
    // 写文件池中的文件
    stringstream ss2;
    ss2<<FILEPOOL<<msg.md5;
    string realFileName = ss2.str();
    char buffer[1024];
    int fd = open(realFileName.c_str(), O_WRONLY);
    netdisk_message msgtemp;
    while(true){
        recv_message(msgtemp);
        send_message(FINISH,msg.filename,msg.is_file);
        for(int i = 0; i < msgtemp.content.length(); ++i){
            buffer[i] = msgtemp.content[i];
        }
        write(fd, buffer, msgtemp.content.length());
        if(msgtemp.content.length() != 1024)
            break;
    }
    close(fd);
    return myOK;
}



// 多线程框架


// 以下函数为Communication类的函数，要加一下域运算符

struct MultithreadStruct{
    netdisk_message
}

void *sendFileRoutine(void *arg){
    
}