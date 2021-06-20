#include "./communication.h"
string Communication::message_to_string(netdisk_message & msg)
{
    string re;
    re+=(unsigned char)(msg.no);
    re+=(unsigned char)(msg.op);
    if(msg.op!=SURE_GET&&msg.op!=NOT_GET){
        re+=(unsigned char)(msg.is_file);
        re+=msg.filename;
        re+="\t";
        re+=msg.path;
        re+="\t";
        re+=msg.md5;
        re+="\t";
        if(msg.op==SEND_FILE){
            re+=msg.content;
            re+="\t";
        }
    }

    return re;
}

netdisk_message Communication::string_to_message(string &msg)
{
    netdisk_message re;
    re.no=msg[msgno_begin];
    re.op=msg[op_begin];
    re.is_file=msg[flagfile_begin];
    if(re.op!=SURE_GET&&re.op!=NOT_GET){
        re.is_file=msg[flagfile_begin];
        int pos=flagfile_begin+1;
        while(msg[pos]!='\t'){
            re.filename+=msg[pos];
            pos++;
        }
        pos++;
        while(msg[pos]!='\t'){
            re.path+=msg[pos];
            pos++;
        }
        pos++;
        while(msg[pos!='\t']){
            re.md5+=msg[pos];
            pos++;
        }
        pos++;
        if(re.op==SEND_FILE){
            while(msg[pos!='\t']){
                re.content+=msg[pos];
                pos++;
            }
        }
    }
    return re;
} 

// 返回消息号
int Communication::send_message(int op,string filename,bool is_file,string path,string md5,string content)
{
    message_count++;
    netdisk_message msg(message_count,op,filename,is_file,path,md5,content);
    string sendstr=message_to_string(msg);
    if(send(sclient,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return message_count;
    }
    return message_count;
}
Communication::Communication(string ip,int port)
{
    this->ip=ip;
    this->port=port;
    this->connection();
}
int Communication::connection(){
    sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        cout<<"invalid socket!"<<endl;
        return myERROR;
    }
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(this->port);
    serAddr.sin_addr.S_un.S_addr = inet_addr(this->ip.c_str());
    if(connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {  //连接失败
        cout<<"connect error !"<<endl;
        closesocket(sclient);
        return myERROR;
    }
    return myOK;
}
