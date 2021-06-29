#include "./readfile.h"
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
        re+=(char)(msg.is_tail+1);
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
        re.is_tail=(msg[flagtail_begin]-1);
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
            while(msg[pos]!='\t'){
                re.md5+=msg[pos];
                pos++;
            }
            pos++;
            if(re.op==SEND_FILE){
                while(msg[pos]!='\t'){
                    re.content+=msg[pos];
                    pos++;
                }
            }
        }
    }
    return re;
} 
int Communication::send_configmessage(int op,string filename,string content,int no){
    int message_no=no;
    if(no==-1){
        for(int i=1;i<MAXMESSAGE;i++){
            if(message_count_use[i]==0){
                message_no=i;
                break;
            }
        }
    }
    netdisk_message msg(message_no,op,filename,0,,"","",content,"","","",0);
    string sendstr=message_to_string(msg);
    if(send(connfd,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return myERROR;
    }
    if(no==-1){
        message_count_use[message_no]=1;
        msg_doing.push_back(msg);
    }
    return message_no;
}
// 返回消息号
int Communication::send_usermessage(int op,string username,string userid,string passwd,bool user_correct,int no)
{
    int message_no=no;
    if(no==-1){
        for(int i=1;i<MAXMESSAGE;i++){
            if(message_count_use[i]==0){
                message_no=i;
                break;
            }
        }
    }
    netdisk_message msg(message_no,op,"",0,"","","",username,userid,passwd,user_correct);
    string sendstr=message_to_string(msg);
    if(send(connfd,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return myERROR;
    }
    if(no==-1){
        message_count_use[message_no]=1;
        msg_doing.push_back(msg);
    }
    return message_no;
}
// 返回消息号
int Communication::send_message(int op,string filename,bool is_file,string path,string md5,string content,int no,bool is_tail)
{
    int message_no=no;
    if(no==-1){
        for(int i=1;i<MAXMESSAGE;i++){
            if(message_count_use[i]==0){
                message_no=i;
                break;
            }
        }
    }
    netdisk_message msg(message_no,op,filename,is_file,path,md5,content,"","","",0);
    string sendstr=message_to_string(msg);
    if(send(sclient,sendstr.c_str(),sendstr.length(),0)<=0){
        cout<<"fail to send message, please check the network"<<endl;
        return myERROR;
    }
    if(no==-1){
        message_count_use[message_no]=1;
        msg_doing.push_back(msg);
    }
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
    if(recv_content.op==FINISH||recv_content.op==EXIST){// 如果通信结束，把消息号释放
        message_count_use[recv_content.no]=0;
        for(int i=0;i<msg_doing.size();i++){
            if(msg_doing[i].no==recv_content.no){
                msg_doing.erase(vector<netdisk_message>::iterator(msg_doing.begin() + i));
                break;
            }
        }
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

int Communication::state_next(netdisk_message msg){
    if(this->STATE==REGIST)
        this->STATE=LOGIN;
    else if(this->STATE==LOGIN){
        int ret=procs_login(msg);
        if(ret==myOK){
            if(send_cfg()==myERROR){
                send_configmessage(GETCONFIG,"","");
                this->STATE=GETCONFIG;
            }
            else{
                this->STATE=SENDCONFIG;
            }
        }
    }
    else if(this->STATE==GETCONFIG){
        if(msg.op==SENDCONFIG){// 收到客户端发来的初始化
            writefile(this->configname,msg.content);
            this->STATE=INITIAL_CLIENT;
            send_message(FINISH,msg.filename,0,"","","",msg.no);
        }
    }
    else if(this->STATE==SENDCONFIG){
        this->STATE=INITIAL_CLIENT;
        if(msg.op==FINISH){
            this->STATE=INITIAL_CLIENT;
        }
    }
    else if(this->STATE==INITIAL_CLIENT){
        if(msg.op==FINISH_INITIAL){
            this->STATE=INITIAL_SERVER;
            // 开始遍历云端文件
            userfiles(this->userid,this->rootpath,this->initialfiles,true);
            if(!this->initialfiles.empty()){
                file temp=this->initialfiles.front();
                // 询问是否要发
                send_message(INITIAL_SERVER,temp,temp.is_file,temp.path,temp.md5,"");
            }
        }
        else{
            if(msg.op==INITIAL_CLIENT){
                int re=/* 检查文件是否存在 */;
                if(re==0||re==2){
                    string filename=(re==0?msg.filename:msg.filename+"-crash"); // 冲突
                    if(/* 检查文件池里有没有这个文件 */==0){
                        send_message(SURE_GET,msg.filename,msg.is_file,msg.is_tail,msg.md5,msg.content,msg.no);
                        // 分裂线程开始接收
                        recvfile(msg);
                    }
                    else{
                        send_message(NOT_GET,msg.filename,msg.is_file,msg.is_tail,msg.md5,msg.content,msg.no);
                    }
                }
                // 存在且相同
                else if(re==1){
                    send_message(EXIST,msg.filename,0,"","","",msg.no);
                }
            }
        }
    }
    else if(this->STATE==INITIAL_SERVER){
        // 这里的终止是靠我遍历结束以后自己调用一下state_next
        if(msg.op==FINISH_INITIAL){
            this->STATE=PROCSEXCP;
        }
        // 遍历云端的所有同步文件夹
        // 先接收上一次的结果，再发送下一次的
        else{
            if(!this->initialfiles.empty()){
                if(msg.op==SURE_GET){
                    file temp=this->initialfiles.front();
                    string content;
                    read(msg.path,content);
                    sendfile(msg,content);
                    this->initialfiles.pop();
                    if(!this->initialfiles.empty()){
                        temp=this->initialfiles.front();
                        // 询问是否要发
                        send_message(INITIAL_SERVER,temp,temp.is_file,temp.path,temp.md5,"");
                    }
                    else{
                        this->STATE=PROCSEXCP;
                    }
                }
            }
        }
    }
    else if(this->STATE==PROCSEXCP){
        this->STATE=NORMAL;
    }
    // 正常状态
    else{
        if(msg.op==SURE_SEND||msg.op==CHANGE){
            recvfile(msg);
        }
        else if(msg.op==SEND){
            int re=/* 检查文件是否存在 */;
            string filename=(re==0?msg.filename:msg.filename+"-crash"); // 冲突
            if(/* 检查文件池里有没有这个文件 */==0){
                send_message(SURE_GET,msg.filename,msg.is_file,msg.is_tail,msg.md5,msg.content,msg.no);
                // 分裂线程开始接收
                recvfile(msg);
            }
            else{
                send_message(NOT_GET,msg.filename,msg.is_file,msg.is_tail,msg.md5,msg.content,msg.no);
            }
        }
        else if(msg.op==REMOVE){
            
            send_message(FINISH,msg.filename,msg.is_file,"","","",msg.no);
        }
        else if(msg.op==RENAME){

            send_message(FINISH,msg.filename,msg.is_file,"","","",msg.no);
        }
        else if(msg.op==BIND_DIR){

        }
        else if(msg.op==RM_BIND_DIR){

        }
    }
}

int Communication::state_rst(){
    this->STATE=REGIST;
}

int Communication::procs_login(netdisk_message msg){
    if(msg.op!=LOGIN)
        return myERROR;
    if(/* 查询账号密码 获得用户名*/<0){
        send_usermessage(LOGIN,msg.username,msg.userid,msg.passwd,false,msg.no);
        return myERROR;
    }
    this->userid=msg.userid;
    this->configname="./"+msg.userid+"/"+"dir.cfg";
    if(send_usermessage(FINISH,msg.username,msg.userid,msg.passwd,true,msg.no)<0)
        return myERROR;
    return myOK;
}

int Communication::send_cfg(){
    string cfgcontent;
    if(readfile(configname,cfgcontent)>=0){
        // 发送目录配置文件
        int msgno=send_configmessage(CONFIGFILE,configname,cfgcontent);
    }
    return msgno;
}


// 如果同一用户的另一端有文件更改，该端直接调用这个函数发送
// 发送文件
int sendfile(netdisk_message msg,string &content){
    
}
// 接收文件，返回已经接收的字节
int recvfile(netdisk_message msg){

}