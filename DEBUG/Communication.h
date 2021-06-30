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

/* ��Ϣ�l�͵Ĳ����� */
#define INITIAL_CLIENT 1
#define INITIAL_SERVER 17
#define SEND 2      // ѯ��Ҫ��Ҫ������ļ�
#define SEND_FILE 3 // ���ļ�������ļ���
#define REMOVE 4
#define RENAME 5
#define CHANGE 6      // �޸�
#define SURE_GET 7    // ȷ��Ҫ������ļ�
#define NOT_GET 20    // ���������մ��ļ�
#define EXIST 21      // ��ʼ���ȶ�ʱ����ȫ��ͬ
#define BIND_DIR 8    // ����Ŀ�
#define RM_BIND_DIR 9 // Ŀ䛽⽉
#define FINISH 10     // ���
#define LOGIN 11
#define LOGOUT 12
#define REGIST 13
#define FINISH_INITIAL 14
#define SENDCONFIG 15 // ���ͼ�¼Ŀ¼�������ļ�����
#define GETCONFIG 16  // ��ȡ��ʼ��Ŀ¼�ṹ
/* ����δ��ɵ��쳣�¼� */
#define PROCSEXCP 18
/* ��ʼͬ��״̬ */
#define NORMAL 19
/* ��ʼ�ȴ�ѯ��״̬ */
#define INITIAL_CONSULT 22
/* ���ڽ���/����״̬�����ⲿ�¼���Ҫ�ȴ� */
#define BUZY 23
/* ��Ϣ�l���ַ�������Ϣ */
#define msgno_begin 0 // string�ж�Ӧ��λ��
#define op_begin 1
#define flagtail_begin 2
#define flagfile_begin 3
#define SENDFILESIZE 1024 // ÿ�η��͵��ļ���С
#define SENDSIZE 2048
#define usercorrect_begin 2 // �ж��û��˺������Ƿ�Ϸ�������ע�ᡢ��¼ʱ��Ҫ�õ�
#define MAXMESSAGE 128
// �ļ�����·����md5��֮����\t��Ϊ�ָ��Ϊ���Ȳ���������
// ����Ǵ����ļ������滹���ļ�����
struct netdisk_message
{
    int no;          // �¼���ţ�����ȷ���ǲ��������,����ȷ��Ҫ��Ҫ���������ļ�
    int op;          // ������
    bool is_tail;    // �����ļ�ʱ���ǲ��ǵ���β��һ����
    bool is_file;    // true��ʾ���ļ�
    string md5;      // md5��
    string path;     // ·�����������ļ���
    string filename; // �ļ���
    string content;  // ����
    string username;
    string userid;
    string passwd;
    bool user_correct;
    netdisk_message()
    {
        ;
    }
    netdisk_message(int no, int op, string filename, bool is_file, bool is_tail, string path, string md5, string content, string username, string useerid, string passwd, bool user_correct, bool is_tail)
    {
        this->no = no;
        this->op = op;
        this->filename = filename;
        this->is_file = is_file;
        this->md5 = md5;
        this->content = content;
        this->path = path;
        this->username = username;
        this->userid = userid;
        this->passwd = passwd;
        this->user_correct = user_correct;
        this->is_tail = is_tail;
    }
};

// �������ĳ���ͻ��˵�ͨ�ţ�ʹ�� Communication(int connfd);�������Ӻõľ��
class Communication
{
private:
    vector<netdisk_message> msg_doing;  // �Ѿ����͵���û���յ�finish���¼�
    queue<file> initialfiles;           // ��ʼҪͬ�����ļ�
    bool message_count_use[MAXMESSAGE]; // ��Ǹ���Ϣ���Ƿ��ù�
    // ״̬����op��ʾ
    int STATE;
    int connfd;
    bool ConnectError;
    string message_to_string(netdisk_message &msg);
    netdisk_message string_to_message(string &msg);

public:
    // �û�id
    int userid;
    string configname;
    string rootpath;
    // �c���ն�朽��Ƿ��e�`
    bool connecterror();
    // no��ʾָ����Ϣ��ţ������ָ�����������
    // ���������ļ�
    int send_configmessage(int op, string filename, string content, int no = -1);
    // �l����Ϣ
    int send_message(int op, string filename, bool is_file, string path = "", string md5 = "", string content = "", int no = -1, int tail = false);
    // �����û���¼���ǳ���ע����Ϣ
    int send_usermessage(int op, string username, string useri, string passwd, bool user_correct, int no = -1);
    // ��ʼ������
    Communication(int connfd);
    // ���_朽�
    int disconnection();
    bool neterror();
    ~Communication();
    // ���܁��Է��ն˵���Ϣ���K���ص�recv_content
    int recv_message(netdisk_message &recv_content);
    // ״̬ת�ƺ��������г�ʼ���Ľ׶���ת��
    // (ע��)->��¼->����Ŀ¼�����ļ�(���û�У���ͻ���Ҫ���ʼ��һ��Ŀ¼�ṹ�������������)->
    // -> ���տͻ��˵�����ļ�ѯ�ʣ�û�еľ��ÿͻ����ϴ� -> �������ͻ��˷��ļ�->
    // -> ������δ����¼�(�쳣����)�Ĵ���
    // ��ʼ�ȴ���������¼������Ŀ¼����ɾ��
    // �����;�����ˣ��ӵ�¼��ʼ������
    int state_next(netdisk_message msg);
    int state_rst();
    // ���յ���¼��Ϣ��ȷ���˺�����Բ��ԣ�����ԣ�����û��������ͻ��ˣ����Ұ�id�浽������ݳ�Աuserid��
    int procs_login(netdisk_message &msg);
    int procs_regist(netdisk_message msg);
    // �������ļ�
    int send_cfg();
    // ��������������msg����Ҫ���͵��ļ��ĳ������������������Ϣ
    // �����ļ�
    int sendfile(netdisk_message msg, string &content);
    // �����ļ��������Ѿ����յ��ֽ�
    int recvfile(netdisk_message msg);
    // ͬһ�ͻ��������û����¼�ִ�У���Ҫͬ��
    int synchronous(netdisk_message msg);
};
