#include "../include/Communication.h"
#include "../include/Database.h"
#include "../include/crud.h"
#include "../include/server.h"
#include <sstream>
extern Database db;
extern map<int, Communication> commap;
ostream &operator<<(ostream &out, netdisk_message &msg)
{

    out << "消息号 " << msg.no << endl;
    out << "操作符 " << msg.op << endl;
    out << "文件名 " << msg.filename << endl;
    out << "路径 " << msg.path << endl;
    out << "是否文件 " << msg.is_file << endl;
    out << "是否文件结尾部分 " << msg.is_tail << endl;
    out << "是否文件内容 " << msg.content << endl;
    out << "md5码 " << msg.md5 << endl;
    out << "用户名 " << msg.username << endl;
    out << "用户账号 " << msg.userid << endl;
    out << "用户密码 " << msg.passwd << endl;
    out << "账号密码是否合法 " << msg.user_correct << endl;
    return out;
}
Communication::Communication()
{
    this->ConnectError = false;
    memset(message_count_use, 0, MAXMESSAGE);
}
Communication::Communication(const Communication &c2)
{
    this->configname = c2.configname;
    this->ConnectError = c2.ConnectError;
    this->connfd = c2.connfd;
    this->initialfiles = c2.initialfiles;
    // this->message_count_use = c2.message_count_use;
    for (int i = 0; i < MAXMESSAGE; i++)
    {
        this->message_count_use[i] = c2.message_count_use[i];
    }
    this->msg_doing = c2.msg_doing;
    this->rootpath = c2.rootpath;
    this->STATE = c2.STATE;
    this->userid = c2.userid;
}
string Communication::message_to_string(netdisk_message &msg)
{
    string re;
    re += char(msg.no);
    re += char(msg.op);
    if (msg.op == LOGIN || msg.op == LOGOUT || msg.op == REGIST)
    {
        re += (char)(msg.user_correct + 1);
        re += msg.username;
        re += "\t";
        re += msg.userid;
        re += "\t";
        re += msg.passwd;
        re += '\t';
    }
    else if (msg.op != SURE_GET && msg.op != NOT_GET)
    {
        re += (char)(msg.is_tail + 1);
        re += (char)(msg.is_file + 1);
        re += msg.filename;
        re += "\t";
        re += msg.path;
        re += "\t";
        if (msg.op != BIND_DIR && msg.op != RM_BIND_DIR)
        {
            re += msg.md5;
            re += "\t";
            if (msg.op == SEND_FILE || msg.op == SENDCONFIG || msg.op == INITIAL_CLIENT || msg.op == INITIAL_SERVER)
            {
                re += msg.content;
                re += "\t";
            }
        }
    }

    return re;
}

netdisk_message Communication::string_to_message(string &msg)
{
    netdisk_message re;
    re.no = msg[msgno_begin];
    re.op = msg[op_begin];
    if (re.op == LOGIN || re.op == LOGOUT || re.op == REGIST)
    {
        re.user_correct = (msg[usercorrect_begin] - 1);
        int pos = usercorrect_begin + 1;
        while (msg[pos] != '\t')
        {
            re.username += msg[pos];
            pos++;
        }
        pos++;
        while (msg[pos] != '\t')
        {
            re.userid += msg[pos];
            pos++;
        }
        pos++;
        while (msg[pos] != '\t')
        {
            re.passwd += msg[pos];
            pos++;
        }
    }
    else if (re.op != SURE_GET && re.op != NOT_GET)
    {
        re.is_tail = (msg[flagtail_begin] - 1);
        re.is_file = (msg[flagfile_begin] - 1);
        int pos = flagfile_begin + 1;
        while (msg[pos] != '\t')
        {
            re.filename += msg[pos];
            pos++;
        }
        pos++;
        while (msg[pos] != '\t')
        {
            re.path += msg[pos];
            pos++;
        }
        if (re.op != BIND_DIR && re.op != RM_BIND_DIR)
        {
            pos++;
            while (msg[pos] != '\t')
            {
                re.md5 += msg[pos];
                pos++;
            }
            pos++;
            if (re.op == SEND_FILE || re.op == SENDCONFIG || re.op == INITIAL_CLIENT || re.op == INITIAL_SERVER)
            {
                while (msg[pos] != '\t')
                {
                    re.content += msg[pos];
                    pos++;
                }
            }
        }
    }
    return re;
}
int Communication::send_configmessage(int op, string filename, string content, int no)
{
    int message_no = no;
    if (no == -1)
    {
        for (int i = 1; i < MAXMESSAGE; i++)
        {
            if (message_count_use[i] == 0)
            {
                message_no = i;
                break;
            }
        }
    }
    netdisk_message msg(message_no, op, filename, 0, true, "", "", content, "", "", "", 0);
    cout << "send" << endl;
    cout << msg << endl;
    string sendstr = message_to_string(msg);
    if (send(connfd, sendstr.c_str(), sendstr.length(), 0) <= 0)
    {
        cout << "fail to send message, please check the network" << endl;
        return myERROR;
    }
    if (no == -1)
    {
        message_count_use[message_no] = 1;
        msg_doing.push_back(msg);
    }
    return message_no;
}
// 返回消息号
int Communication::send_usermessage(int op, string username, string userid, string passwd, bool user_correct, int no)
{
    int message_no = no;
    if (no == -1)
    {
        for (int i = 1; i < MAXMESSAGE; i++)
        {
            if (message_count_use[i] == 0)
            {
                message_no = i;
                break;
            }
        }
    }
    netdisk_message msg(message_no, op, "", 0, 0, "", "", "", username, userid, passwd, user_correct);
    string sendstr = message_to_string(msg);
    if (send(connfd, sendstr.c_str(), sendstr.length(), 0) <= 0)
    {
        cout << "fail to send message, please check the network" << endl;
        return myERROR;
    }
    if (no == -1)
    {
        message_count_use[message_no] = 1;
        msg_doing.push_back(msg);
    }
    return message_no;
}
// 返回消息号
int Communication::send_message(int op, string filename, bool is_file, string path, string md5, string content, int no, bool is_tail)
{
    int message_no = no;
    if (no == -1)
    {
        for (int i = 1; i < MAXMESSAGE; i++)
        {
            if (message_count_use[i] == 0)
            {
                message_no = i;
                break;
            }
        }
    }
    netdisk_message msg(message_no, op, filename, is_file, is_tail, path, md5, content, "", "", "", 0);
    cout << "send" << endl;
    cout << msg << endl;
    string sendstr = message_to_string(msg);
    if (send(connfd, sendstr.c_str(), sendstr.length(), 0) <= 0)
    {
        cout << "fail to send message, please check the network" << endl;
        return myERROR;
    }
    if (no == -1)
    {
        message_count_use[message_no] = 1;
        msg_doing.push_back(msg);
    }
    return message_no;
}
Communication::Communication(int fd) : connfd(fd)
{
    this->ConnectError = false;
    cout << "communication constructor" << endl;
    memset(message_count_use, 0, MAXMESSAGE);
}

bool Communication::connecterror()
{
    return this->ConnectError;
}

int Communication::recv_message(netdisk_message &recv_content)
{
    string recvstr;
    char buf[SENDSIZE];
    int length = 0;
    if ((length = recv(connfd, buf, SENDSIZE, 0)) <= 0)
    {
        this->ConnectError = true;
        return myERROR;
    }
    buf[length] = 0;
    recvstr = string(buf);
    // cout << recvstr << endl;
    recv_content = string_to_message(recvstr);
    cout << recv_content << endl;
    if (recv_content.op == FINISH || recv_content.op == EXIST)
    { // 如果通信结束，把消息号释放
        message_count_use[recv_content.no] = 0;
        for (int i = 0; i < int(msg_doing.size()); i++)
        {
            if (msg_doing[i].no == recv_content.no)
            {
                msg_doing.erase(vector<netdisk_message>::iterator(msg_doing.begin() + i));
                break;
            }
        }
    }
    return myOK;
}

int Communication::disconnection()
{
    return myOK;
}

Communication::~Communication()
{
    disconnection();
}

int Communication::state_next(netdisk_message msg)
{
    if (msg.op == REGIST)
    {
        this->STATE = REGIST;
    }

    if (msg.op == LOGIN)
    {
        this->STATE = LOGIN;
    }
    cout << "state" << this->STATE << "msgop" << msg.op << endl;
    if (this->STATE == REGIST)
    {
        int ret = procs_regist(msg);
        if (ret == myOK)
        {
            send_usermessage(REGIST, msg.username, msg.userid, msg.passwd, true, msg.no);
        }
        else
        {
            send_usermessage(REGIST, msg.username, msg.userid, msg.passwd, false, msg.no);
        }
    }
    else if (this->STATE == LOGIN)
    {
        int ret = procs_login(msg);
        if (ret == myOK)
        {
            // send_usermessage(LOGIN, msg.username, msg.userid, msg.passwd, true, msg.no);
            if (send_cfg() == myERROR)
            {
                send_configmessage(GETCONFIG, "", "");
                this->STATE = GETCONFIG;
            }
            else
            {
                this->STATE = SENDCONFIG;
            }
        }
        else
        {
            send_usermessage(LOGIN, msg.username, msg.userid, msg.passwd, false, msg.no);
        }
    }
    else if (this->STATE == GETCONFIG)
    {
        if (msg.op == SENDCONFIG)
        {
            cout << "成功接收到初始配置文件" << endl; // 收到客户端发来的初始化
            writefile(this->configname, msg.content);
            this->STATE = INITIAL_CLIENT;
            send_message(FINISH, msg.filename, 0, "", "", "", msg.no);
        }
    }
    else if (this->STATE == SENDCONFIG)
    {
        this->STATE = INITIAL_CLIENT;
        if (msg.op == FINISH)
        {
            this->STATE = INITIAL_CLIENT;
        }
    }
    else if (this->STATE == INITIAL_CLIENT)
    {
        cout << "flag" << endl;
        if (msg.op == FINISH_INITIAL)
        {
            cout << "flag_2" << endl;
            this->STATE = INITIAL_SERVER;
            // 开始遍历云端文件
            userfiles(this->userid, this->rootpath, this->initialfiles, true);
            if (!this->initialfiles.empty())
            {
                file temp = this->initialfiles.front();
                // 询问是否要发
                send_message(INITIAL_SERVER, temp.filename, temp.is_file, temp.path, temp.md5, "");
            }
            else
            {
                send_message(FINISH_INITIAL, "", false);
                this->STATE = PROCSEXCP;
                state_next(msg);
            }
        }
        else
        {
            if (msg.op == INITIAL_CLIENT)
            {
                int re = sameNameFile(this->userid, msg.path, msg.md5) /* 检查文件是否存在 */;
                cout << re << endl;
                if (re == 0 || re == 2)
                {
                    string filename = (re == 0 ? msg.filename : msg.filename + "-crash"); // 冲突
                    if (msg.is_file && db.fileExists(msg.md5) == false)
                    { /* 检查文件池里有没有这个文件 */
                        send_message(SURE_GET, msg.filename, msg.is_file, msg.path, msg.md5, msg.content, msg.no, msg.is_tail);
                        db.addFile(msg.md5);
                        // 分裂线程开始接收
                        recvfile(msg);
                    }
                    else
                    {
                        if (msg.is_file)
                        {
                            send_message(NOT_GET, msg.filename, msg.is_file, msg.path, msg.md5, msg.content, msg.no, msg.is_tail);
                            createFile(this->userid, false, msg.path, msg.md5);
                        }
                        else
                        {
                            send_message(EXIST, msg.filename, msg.is_file, msg.path, msg.md5, msg.content, msg.no, msg.is_tail);
                            cout << "create" << msg.path << endl;
                            createFile(this->userid, true, msg.path, "");
                        }
                    }
                }
                // 存在且相同
                else if (re == 1)
                {
                    send_message(EXIST, msg.filename, 0, "", "", "", msg.no);
                }
            }
        }
    }
    else if (this->STATE == INITIAL_SERVER)
    {
        if (!this->initialfiles.empty())
        {
            if (msg.op == SURE_GET)
            {
                file temp = this->initialfiles.front();
                sendfile(msg);
                this->initialfiles.pop();
                if (!this->initialfiles.empty())
                {
                    temp = this->initialfiles.front();
                    // 询问是否要发
                    send_message(INITIAL_SERVER, temp.filename, temp.is_file, &(temp.path[this->rootpath.length() - 1]), temp.md5, "");
                }
                else
                {
                    send_message(FINISH_INITIAL, "", false);
                    this->STATE = PROCSEXCP;
                    state_next(msg);
                }
            }
        }
    }
    else if (this->STATE == PROCSEXCP)
    {
        this->STATE = NORMAL;
    }
    // 正常状态
    else if (this->STATE == NORMAL)
    {
        if (msg.op == SEND_FILE)
        {
            db.addFile(msg.md5);
            // 分裂线程开始接收
            recvfile(msg);
        }
        else if (msg.op == SEND || msg.op == CHANGE)
        {
            int re = sameNameFile(this->userid, msg.filename, msg.md5);           /* 检查文件是否存在 */
            string filename = (re == 0 ? msg.filename : msg.filename + "-crash"); // 冲突
            if (msg.is_file && db.fileExists(msg.md5) == 0)
            { /* 检查文件池里有没有这个文件 */
                send_message(SURE_GET, msg.filename, msg.is_file, msg.path, msg.md5, msg.content, msg.no, msg.is_tail);
                db.addFile(msg.md5);
                // 分裂线程开始接收
                recvfile(msg);
            }
            else
            {
                send_message(NOT_GET, msg.filename, msg.is_file, msg.path, msg.md5, msg.content, msg.no, msg.is_tail);
                if (!msg.is_file)
                {
                    createFile(this->userid, true, msg.path, "");
                }
            }
        }
        else if (msg.op == REMOVE)
        {
            deleteFile(userid, msg.path);
            db.decreaseFileLinks(msg.md5);
            send_message(FINISH, msg.filename, msg.is_file, "", "", "", msg.no);
        }
        else if (msg.op == RENAME)
        {
            renameFile(userid, msg.path, msg.filename);
            send_message(FINISH, msg.filename, msg.is_file, "", "", "", msg.no);
        }
        else if (msg.op == BIND_DIR)
        {
            db.addBindDirectory(this->userid, msg.path);
            send_message(FINISH, msg.filename, 0, msg.path, "", "", msg.no);
        }
        else if (msg.op == RM_BIND_DIR)
        {
            db.deleteBindDirectory(this->userid, msg.path);
            send_message(FINISH, msg.filename, 0, msg.path, "", "", msg.no);
        }
        else if (msg.op == SENDCONFIG)
        {
        }
    }
    return myOK;
}

int Communication::state_rst()
{
    this->STATE = REGIST;
    return myOK;
}

int Communication::procs_login(netdisk_message &msg)
{
    if (msg.op != LOGIN)
        return myERROR;
    int dbuserid;
    if (db.loginUser(dbuserid, msg.username, msg.userid, msg.passwd) == myERROR)
    {
        cout << "密码账号错误" << endl;
        send_usermessage(LOGIN, msg.username, msg.userid, msg.passwd, false, msg.no);
        return myERROR;
    }
    this->userid = dbuserid;
    stringstream ss;
    ss << USERCONFIGDIR << dbuserid << "_";
    this->configname = ss.str();
    this->configname += "dir.cfg";
    stringstream sss;
    sss << USERFILEDIR << dbuserid;
    this->rootpath = sss.str();
    if (send_usermessage(FINISH, msg.username, msg.userid, msg.passwd, true, msg.no) < 0)
        return myERROR;
    return myOK;
}
int Communication::procs_regist(netdisk_message msg)
{
    cout << "calling function: procs_regist" << endl;
    if (db.accountUsed(msg.userid) == true)
    {
        cout << "账号重复" << endl;
        return myERROR;
    }
    db.addUser(msg.username, msg.userid, msg.passwd);
    int id;
    db.findIdByAccount(msg.userid, id);
    db.createUserTable(id);
    stringstream ss;
    ss << USERFILEDIR << id;
    string rootpath = ss.str();
    if (mkdir(rootpath.c_str(), 0755) == -1)
    {
        cout << rootpath << endl;
        cout << "生成用户目录失败" << endl;
        return myERROR;
    }
    cout << "注册成功" << endl;
    return myOK;
}
int Communication::send_cfg()
{
    int msgno = myERROR;
    string cfgcontent;
    cout << "尝试发送配置文件" << configname << endl;
    if (read(configname, cfgcontent) >= 0)
    {
        // 发送目录配置文件
        msgno = send_configmessage(SENDCONFIG, configname, cfgcontent);
    }
    return msgno;
}

// 发送文件
int Communication::sendfile(netdisk_message msg)
{
    netdisk_message msgtemp;
    stringstream ss;
    ss << this->rootpath << "/" << msg.path;
    string fullFileName = ss.str();
    cout << "debug message: in sendfilefunction, fullFileName is " << fullFileName << endl;
    int orifd = open(fullFileName.c_str(), O_RDONLY);
    char buffer[1024];
    read(orifd, buffer, 1024);
    close(orifd);
    buffer[32] = '\0';
    stringstream ss2;
    ss2 << FILEPOOL << buffer;
    string realFileName = ss2.str();
    int realfd = open(realFileName.c_str(), O_RDONLY);
    int readret = read(realfd, buffer, 1024);
    while (true)
    {
        string content;
        for (int i = 0; i < readret; ++i)
        {
            content += buffer[i];
        }
        if (readret == 1024)
        {
            send_message(SEND_FILE, msg.filename, true, msg.path, msg.md5, content, msg.no, false);
            if (recv_message(msgtemp) == myERROR)
            {
                /* 写到异常表里 */
                return myERROR;
            }
        }
        else
        {
            send_message(SEND_FILE, msg.filename, true, msg.path, msg.md5, content, msg.no, true);
            if (recv_message(msgtemp) == myERROR)
            {
                /* 写到异常表里 */
                return myERROR;
            }
            break;
        }
        readret = read(realfd, buffer, 1024);
    }
    close(realfd);
    return myOK;
}
// 接收文件，返回已经接收的字节
int Communication::recvfile(netdisk_message msg)
{
    cout << "receive" << endl;
    // 写用户目录下的文件
    stringstream ss;
    ss << this->rootpath << "/" << msg.path;
    string fullFileName = ss.str();
    cout << fullFileName << endl;
    ofstream outfile(fullFileName, ios::out);
    outfile << msg.md5;
    outfile.close();
    // 写文件池中的文件
    stringstream ss2;
    ss2 << FILEPOOL << msg.md5;
    string realFileName = ss2.str();
    ofstream realOutFile(realFileName, ios::out);
    cout << realFileName << endl;
    netdisk_message msgtemp;
    while (true)
    {
        cout << "this" << endl;
        recv_message(msgtemp);
        send_message(FINISH, msg.filename, msg.is_file);
        cout << "content: " << msg.content << endl;
        cout << "content length: " << msg.content.length() << endl;
        realOutFile << msg.content;
        if (msgtemp.is_tail)
            //if (msgtemp.content.length() != 1024)
            break;
    }
    realOutFile.close();
    return myOK;
}

bool Communication::neterror()
{
    if (this->ConnectError)
        return true;
    else
        return false;
}

// 接收文件，返回已经接收的字节
int Communication::synchronous(netdisk_message msg)
{
    if (STATE != NORMAL)
    {
        msg_doing.push_back(msg); // 放在待办事件
    }
    else
    {
        state_next(msg); ///// 还没写完
    }
    return myOK;
}