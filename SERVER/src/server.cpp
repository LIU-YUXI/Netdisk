#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "../include/server.h"
#include "../include/Database.h"
#include "../include/Communication.h"
#include <map>
using namespace std;
typedef struct sockaddr SA;
Database db;
map<int, Communication> commap;
int my_daemon(int nochdir, int noclose)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        cerr << "fork error" << endl;
        return -1;
    }
    else if (pid > 0)
    {
        exit(0);
    }
    setsid();
    umask(0);
    if (!nochdir)
        chdir("/");
    if (!noclose)
    {
        int i = 0;
        for (; i < getdtablesize(); ++i)
            close(i);
    }
    return 0;
}

void parseParameter(int argc, char *argv[], uint16_t &port)
{
    char opt;
    const struct option long_options[] = {
        {"port", required_argument, NULL, 'p'}};
    const char *optstring = "p:";
    while ((opt = getopt_long(argc, argv, optstring, long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'p':
            port = htons(atoi(optarg));
            break;
        default:
            cerr << "argument error" << endl;
            exit(1);
        }
    }
}

int open_listenfd(uint16_t port)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // set nonblocking
    int flag = fcntl(listenfd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(listenfd, F_SETFL, flag);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = port;
    server_address.sin_addr.s_addr = INADDR_ANY;
    int optval = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
    if (bind(listenfd, (SA *)&server_address, sizeof(server_address)) != 0)
    {
        cerr << "bind unsuccessful" << endl;
        exit(1);
    }
    if (listen(listenfd, 1024) < 0)
    {
        close(listenfd);
        cerr << "listen unsuccessful" << endl;
        exit(1);
    }
    return listenfd;
}

int main(int argc, char *argv[])
{
    mkdir(USERFILEDIR, 0777);
    mkdir(USERCONFIGDIR, 0777);
    mkdir(FILEPOOL, 0777);
    // 守护进程
    daemon(1, 1);
    uint16_t port;
    parseParameter(argc, argv, port);
    // 打开监听描述符等待连接
    int listenfd = open_listenfd(port);
    // init epoll
    int epfd = epoll_create1(0);
    epoll_event event;
    event.data.fd = listenfd;
    event.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);
    epoll_event events[2048];
    struct sockaddr_in clientaddr;
    socklen_t clientlen = sizeof(clientaddr);
    cout << "debug 1" << endl;
    while (true)
    {
        cout << "debug 2" << endl;
        int eventsNumber = epoll_wait(epfd, events, 2048, -1);
        cout << "epoll_wait return, eventsNumber is " << eventsNumber << endl;
        cout << "debug 3" << endl;
        for (int i = 0; i < eventsNumber; ++i)
        {
            if (events[i].events & (EPOLLERR | EPOLLHUP)) /* 监控到错误或者挂起 */
            {
                cout << "epoll error, fd is " << events[i].data.fd << endl;
                int curfd = events[i].data.fd;
                epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                commap.erase(curfd);
                close(events[i].data.fd);
                continue;
            }
            cout << "debug 4" << endl;
            if (events[i].events & EPOLLIN) // 可读事件
            {
                if (events[i].data.fd == listenfd) // 监听描述符上可读
                {
                    // accept socket connection
                    int connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
                    cout << "Connected to client at (" << inet_ntoa(clientaddr.sin_addr) << ", " << ntohs(clientaddr.sin_port) << ")" << endl
                         << "connfd is " << connfd << endl
                         << endl;
                    // set non-blocking
                    // int flag = fcntl(connfd, F_GETFL);
                    // flag |= O_NONBLOCK;
                    // fcntl(connfd, F_SETFL, flag);
                    // register event
                    event.data.fd = connfd;
                    event.events = EPOLLIN;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
                    Communication newCom(connfd);
                    commap.insert({connfd, newCom});
                }
                else // 已连接描述符上可读
                {
                    cout << "readable" << endl;
                    int curfd = events[i].data.fd;
                    netdisk_message msg;
                    commap[curfd].recv_message(msg);
                    if (commap[curfd].neterror())
                    {
                        cout << "net error" << endl;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                        commap.erase(curfd);
                        close(curfd);
                    }
                    else
                        commap[curfd].state_next(msg);
                }
            }
        }
    }
    return 0;
}