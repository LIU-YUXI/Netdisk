#include "./communication.h"
string Communication::message_to_string(netdisk_message & msg)
{
    string re;
    re+=char(msg.no);
    re+=char(msg.op);
    if(msg.op==LOGIN||msg.op==LOGOUT||msg.op==REGIST){
        re+=(char)(msg.user_correct+1);
        re+=msg.username;
        re+="\t";
        re+=msg.userid;
        re+="\t";
        re+=msg.passwd;
        re+='\t';
    }
    else if(msg.op!=SURE_GET&&msg.op!=NOT_GET){
        re+=(char)(msg.is_file+1);
        re+=msg.filename;
        re+="\t";
        re+=msg.path;
        re+="\t";
        if(msg.op!=BIND_DIR&&msg.op!=RM_BIND_DIR){
            re+=msg.md5;
            re+="\t";
            if(msg.op==SEND_FILE){
                re+=msg.content;
                re+="\t";
            }
        }
    }

    return re;
}

netdisk_message Communication::string_to_message(string &msg)
{
    netdisk_message re;
    re.no=msg[msgno_begin];
    re.op=msg[op_begin];
    if(re.op==LOGIN||re.op==LOGOUT||re.op==REGIST){
        re.user_correct=(msg[usercorrect_begin]-1);
        int pos=usercorrect_begin+1;
        while(msg[pos]!='\t'){
            re.username+=msg[pos];
            pos++;
        }
        pos++;
        while(msg[pos]!='\t'){
            re.userid+=msg[pos];
            pos++;
        }
        pos++;
        while(msg[pos]!='\t'){
            re.passwd+=msg[pos];
            pos++;
        }
    }
    else if(re.op!=SURE_GET&&re.op!=NOT_GET){
        re.is_file=(msg[flagfile_begin]-1);
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
        if(re.op!=BIND_DIR&&re.op!=RM_BIND_DIR){
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
    }
    return re;
} 
int Communication::send_configmessage(int op,string filename,string content){
    int message_no=1;
    for(int i=1;i<MAXMESSAGE;i++){
        if(message_count_use[i]==0){
            message_no=i;
            break;
        }
    }
    netdisk_message msg(message_no,op,filename,0,"","",content,"","","",0);
    string sendstr=message_to_string(msg);
    if(send(connfd,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return myERROR;
    }
    message_count_use[message_no]=1;
    return message_no;
}
// 返回消息号
int Communication::send_usermessage(int op,string username,string userid,string passwd,bool user_correct)
{
    int message_no=1;
    for(int i=1;i<MAXMESSAGE;i++){
        if(message_count_use[i]==0){
            message_no=i;
            break;
        }
    }
    netdisk_message msg(message_no,op,"",0,"","","",username,userid,passwd,user_correct);
    string sendstr=message_to_string(msg);
    if(send(connfd,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return myERROR;
    }
    message_count_use[message_no]=1;
    return message_no;
}
// 返回消息号
int Communication::send_message(int op,string filename,bool is_file,string path,string md5,string content)
{
    int message_no=1;
    for(int i=1;i<MAXMESSAGE;i++){
        if(message_count_use[i]==0){
            message_no=i;
            break;
        }
    }
    netdisk_message msg(message_no,op,filename,is_file,path,md5,content,"","","",0);
    string sendstr=message_to_string(msg);
    if(send(sclient,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return myERROR;
    }
    message_count_use[message_no]=1;
    return message_no;
}
Communication::Communication(int connfd)
{
    this->connfd=connfd;
    memset(message_count_use,0,MAXMESSAGE);
}


bool Communication::connecterror(){
    return this->ConnectError;
}

int Communication::recv_message(netdisk_message &recv_content)
{
    string recvstr;
    char buf[SENDSIZE];
    if(recv(connfd,buf,SENDSIZE,0)<=0)
        return myERROR;
    recvstr=string(buf);
    recv_content=string_to_message(recvstr);
    if(recv_content.op==FINISH){// 如果通信结束，把消息号释放
        message_count_use[recv_content.no]=0;
    }
    return myOK;
}

int Communication::disconnection(){
    if(connecterror()==false){
        closesocket(connfd);
    }
    return myOK;
}


Communication::~Communication(){
    disconnection();
}

int Communication::state_next(int choose2){
    if(this->STATE==REGIST)
        this->STATE=LOGIN;
    else if(this->STATE==LOGIN){
        if(choose2==1){
            this->STATE=GETCONFIG;
        }
        else{
            this->STATE=SENDCONFIG;
        }
    }
    else if(this->STATE==GETCONFIG||this->STATE==SENDCONFIG){
        this->STATE=INITIAL_CLIENT;
    }
    else if(this->STATE==INITIAL_CLIENT){
        this->STATE=PROCSEXCP;
    }
    else if(this->STATE==PROCSEXCP){
        this->STATE=NORMAL;
    }
}

int Communication::state_rst(){
    this->STATE=REGIST;
}

int Communication::procs_login(netdisk_message msg){
    if(/* 查询账号密码 */<0)
        return myERROR;
    this->userid=msg.userid;
    this->configname="./"+msg.userid+"/"+"dir.cfg";
    
}