#include <iostream>
#include <cstring>
#include <WinSock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

const int BUF_SIZE = 1024,
		  INSTR_LEN = 4,
		  EMAIL_LEN = 32,
		  PWD_LEN = 16,
		  RETSTR_LEN = 2;

int main(int argc, char **argv)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		cerr << "Load WinSock Failed!\n";
		return -1;
	}

	SOCKET client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd == INVALID_SOCKET)
	{
		cerr << "socket error\n";
		return -2;
	}

	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	if (connect(client_fd, (SOCKADDR *)&server_addr, sizeof(SOCKADDR_IN)) == INVALID_SOCKET)
	{
		cerr << "connect error\n";
		return -1;
	}

	//test
	char buf[BUF_SIZE];
	for (;;)
	{
		cout << "test signup\n";
		send(client_fd, "0101", INSTR_LEN, 0);
		sprintf(buf, "1595606114@qq.com");
		send(client_fd, buf, EMAIL_LEN, 0);
		sprintf(buf, "1234567890");
		send(client_fd, buf, PWD_LEN, 0);
		recv(client_fd, buf, RETSTR_LEN, 0);
		buf[2] = 0;
		if (!strcmp(buf, "00"))
		{
			cout << "ע��ɹ���\n";
		}
		else if (!strcmp(buf, "02"))
		{
			cout << "�û��Ѵ��ڣ�\n";
		}
		else
		{
			cout << buf << "\n��������\n";
		}

		getchar();

		cout << "test login\n";
		send(client_fd, "0102", INSTR_LEN, 0);
		sprintf(buf, "1595606114@qq.com");
		send(client_fd, buf, EMAIL_LEN, 0);
		sprintf(buf, "1234567890");
		send(client_fd, buf, PWD_LEN, 0);
		recv(client_fd, buf, RETSTR_LEN, 0);
		buf[2] = 0;
		if (!strcmp(buf, "00"))
		{
			cout << "��¼�ɹ���\n";
		}
		else if (!strcmp(buf, "02"))
		{
			cout << "�û������������\n";
		}
		else if (!strcmp(buf, "03")) //�����˵Ӧ�ñ����жϣ������������ᴦ��������Ϊ����˫����
		{
			cout << "�ѵ�¼��\n";
		}
		else
		{
			cout << buf << "\n��������\n";
		}

		getchar();
	}

	WSACleanup();
	return 0;
}