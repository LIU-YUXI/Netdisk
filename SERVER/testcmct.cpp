#include <unistd.h>
#include <errno.h>
#include "./readfile.h"
#include "./class_aat.h"
#include "./socket_error.h"
#include "./server_tool.h"
#include "./communication.h"
#define MAXLINE 65537
#define MAXCLIENT 1024

enum OPT_ARGS
{
	OPT_ARGS_PORT,
	OPT_ARGS_IP,
	OPT_ARGS_RBYTE,
	OPT_ARGS_SBYTE,
	OPT_ARGS_RDELAY,
	OPT_ARGS_WDELAY,
	OPT_ARGS_DEBUG
};
void usage(const char* exename)
{
	cout << exename << endl;
	cout << "--port 端口号" << endl;
	cout << "--ip 服务端IP地址" << endl;
	cout << "--readbyte 每次读入的字节数" << endl;
	cout << "--writebyte 每次写入的字节数" << endl;
	cout << "--delay 每次循环的延时" << endl;
	cout << "--debug 打印收发的总字节数" << endl;
}
int main(int argc, char** argv)
{
	AAT args[] = {
	AAT("--port", ST_EXTARGS_TYPE::int_with_default, 1, 4000, 0, 65535, false),
	AAT("--ip", ST_EXTARGS_TYPE::ipaddr_with_default, 1, "192.168.80.230", false),
	AAT("--readbyte", ST_EXTARGS_TYPE::int_with_default, 1, 1024, 0, 65536, false),
	AAT("--writebyte", ST_EXTARGS_TYPE::int_with_default, 1, 1024, 0, 65536, false),
	AAT("--rdelay", ST_EXTARGS_TYPE::int_with_default, 1, 0, 0,15, false),
	AAT("--wdelay", ST_EXTARGS_TYPE::int_with_default, 1, 0, 0,15, false),
	AAT("--debug", ST_EXTARGS_TYPE::boolean,0,false),
	AAT()
	};
	if (args_analyse(argc, argv, args, 0) < 0) {
		return -1;
	}
	args_analyse_print(args);
	if (args[OPT_ARGS_PORT].existed() == 0) {
		usage(argv[0]);
		cout << "缺少参数[" << args[OPT_ARGS_PORT].get_name() << "]" << endl;
		return -1;
	}
	if (args[OPT_ARGS_IP].existed() == 0) {
		usage(argv[0]);
		cout << "缺少参数[" << args[OPT_ARGS_IP].get_name() << "]" << endl;
		return -1;
	}
	//-------------打印所有网卡的所有ip,并检查输入的ip是不是本机ip------------
	char ip[16];
	memset(ip, 0, sizeof(ip));
	if (get_local_ip(ip, args[OPT_ARGS_IP].get_str_ipaddr().c_str()) == -1) {
		cout << "本机不存在绑定的ip地址！" << endl;
		exit(-1);
	}
	//-------------end---------------------------------------------------------
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	int sock_array[MAXCLIENT] = {0};
	int client_num = 0;
	char buf[MAXLINE];
	char str[MAXLINE];
	for (int i = 0; i < args[OPT_ARGS_SBYTE].get_int(); i++) {
		str[i] = '*';
	}
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	/*
	socket()打开一个网络通讯端口，如果成功的话，就像open()一样返回一个文件描述符，应用程序
	可以像读写文件一样用read/write在网络上收发数据，如果socket()调用出错则返回-1。对
	于IPv4，family参数指定为AF_INET。对于TCP协议，type参数指定为SOCK_STREAM，表示面向
	流的传输协议。如果是UDP协议，则type参数指定为SOCK_DGRAM，表示面向数据报的传输协
	议。protocol参数的介绍从略，指定为0即可。
	*/
	int one = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
		close(listenfd);
		return -1;
	}
	// 设置非阻塞
	set_nonblock(listenfd);
	server_bind(listenfd, servaddr, args[OPT_ARGS_IP].get_str_ipaddr().c_str(), args[OPT_ARGS_PORT].get_int());
	Listen(listenfd, 20);
	/*
	典型的服务器程序可以同时服务于多个客户端，当有客户端发起连接时，服务器调用的accept()返
	回并接受这个连接，如果有大量的客户端发起连接而服务器来不及处理，尚未accept的客户端就处
	于连接等待状态，listen()声明sockfd处于监听状态，并且最多允许有backlog个客户端处于连接待
	状态，如果接收到更多的连接请求就忽略。listen()成功返回0，失败返回-1
	*/

	fd_set client_fdset, write_fdset;    /*监控文件描述符集合*/
	int maxsock;            /*监控文件描述符中最大的文件号*/
	struct timeval tv;      /*超时返回时间*/
	maxsock = listenfd;
	int ret = 0;
	/*初始化文件描述符号到集合*/
	FD_ZERO(&client_fdset);
	FD_ZERO(&write_fdset);
	/*加入服务器描述符*/
	FD_SET(listenfd, &client_fdset);
	FD_SET(listenfd, &write_fdset);
	ret = select(maxsock + 1, &client_fdset, &write_fdset, NULL, NULL);
	cout << "select return is " << ret << endl;
	if (ret <= 0) {

		cout << "errno is" << errno << endl;
	}
	else
		cout << "Select success" << endl;

	/*检查是否有新的连接，如果有，接收连接加入到client_sockfd中*/
	if (FD_ISSET(listenfd, &client_fdset))
	{
		/*接受连接*/
		struct sockaddr_in client_addr;
		size_t size = sizeof(struct sockaddr_in);
		int sock_client = Accept(listenfd, (struct sockaddr*)(&client_addr), (unsigned int*)(&size));
		// 加入client列表
		sock_array[client_num++] = sock_client;
		int fd_max = listenfd;
		if (sock_client > fd_max)
			fd_max = sock_client;
		// 设置非阻塞
		set_nonblock(sock_client);
		int recv_count[MAXCLIENT] = { 0 };
		int write_count[MAXCLIENT] = { 0 };
		// 开一个新的select
		fd_set cr_fdset, cw_fdset;    /*监控文件描述符集合*/
		struct timeval timec;      /*超时返回时间*/
		timec.tv_sec = args[OPT_ARGS_WDELAY].get_int();
		timec.tv_usec = 0;
		int ret = 0;
		// ret = select(sock_client + 1, &cr_fdset, &cw_fdset, timec, NULL)
		// 连接成功后就开始读
		int begin = 1;
		while (1) {
			/*初始化文件描述符号到集合*/
			FD_ZERO(&cr_fdset);
			FD_ZERO(&cw_fdset);
			/*加入服务器描述符*/
			FD_SET(sock_client, &cr_fdset);
			FD_SET(listenfd, &cr_fdset);
			/*把活动的句柄加入到文件描述符中*/
			for (int i = 0; i < MAXCLIENT; i++) {
				if (sock_array[i] != 0) {
					FD_SET(sock_array[i], &cr_fdset);
				}
			}
			int n = 0;
			// cout << "begin to select" << endl;
			ret = select(fd_max + 1, &cr_fdset, NULL, NULL, NULL)//&timec);
			// cout << "ret=" << ret << endl;
			if (ret > 0) {
				if (FD_ISSET(listenfd, &cr_fdset)) {
					struct sockaddr_in client_addr;
					size_t size = sizeof(struct sockaddr_in);
					int sock_client = Accept(listenfd, (struct sockaddr*)(&client_addr), (unsigned int*)(&size));
					set_nonblock(sock_client);
					/*把连接加入到文件描述符集合中*/
					if (client_num < MAXCLIENT)
					{
						sock_array[client_num++] = sock_client;
						cout << "new connection client " << client_num << " " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << endl;
						//更新maxsock,因为下一次进入while循环调用时，需要传当前最大的fd值+1给select函数
						if (sock_client > maxsock) {
							fd_max = sock_client;
						}
                        // 初始化通信类
                        Communication cm(sock_client);
                        string cfgcontent;
                        if(readfile("./config.txt",cfgcontent)>=0){
                            // 发送目录配置文件
                            int msgno=cm.send_configmessage(CONFIGFILE,"config.txt",cfgcontent);
                            
                        }
					}
					else {
						cout<<("max connections\n");
					}
				}
				for (int i = 0; i < client_num; i++) {
					sock_client = sock_array[i];
					if (FD_ISSET(sock_client, &cr_fdset)) {
						if (FD_ISSET(sock_client, &cr_fdset)) {
							n = read(sock_client, buf, args[OPT_ARGS_RBYTE].get_int()); //MSG_WAITALL);
							if (n >= 0)
								recv_count[i] += n;
							if (args[OPT_ARGS_DEBUG].existed()) {
								cout << recv_count[i] << "has been read , from client " << i + 1 << endl;
							}
						}
					}
				}
			}
			if (ret == 0 || begin) { // 超时即时间为0秒
				timec.tv_sec = args[OPT_ARGS_WDELAY].get_int(); // 重新计时
				for (int i = 0; i < client_num; i++) {
					sock_client = sock_array[i];
					n = write(sock_client, str, args[OPT_ARGS_SBYTE].get_int());
					if (n >= 0)
						write_count[i] += n;
					if (args[OPT_ARGS_DEBUG].existed()) {
						cout << write_count[i] << "has been send,to client "<<i+1 << endl;
					}
				}
				begin = 0;
			}
			if (ret < 0) {
				cout << "fail to select" << endl;
				break;
			}
		}
		Close(sock_client);
	}
//最后，把已连接上的clent的fd和server自身的fd都关闭
	Close(listenfd);
	return 0;
}
