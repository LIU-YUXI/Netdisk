#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<windows.h>
#include<sstream>
#include<string.h>
#include<direct.h>
using namespace std;
bool search_folder(const char para[])
{
	WIN32_FIND_DATAA fdfile;
	HANDLE hFind = FindFirstFileA(para, &fdfile);//��һ��������·����������ʹ��ͨ�����fd�洢���ļ�����Ϣ
	bool done = true, found_fondfolder = false;
	while (1)
	{
		done = FindNextFileA(hFind, &fdfile); //���ص�ֵ���Ϊ0��û���ļ�ҪѰ��
		if (!done)
			break;
		if (!strcmp(fdfile.cFileName, "..") || !strcmp(fdfile.cFileName, "."))
			continue;
		if (fdfile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			return true;
			FindClose(hFind);
		}
	}
	FindClose(hFind);
	return false;
}
void open_folder(const char para[], int round, int ctrl[])
{
	WIN32_FIND_DATAA fdfile;
	HANDLE hFind = FindFirstFileA(para, &fdfile);//��һ��������·����������ʹ��ͨ�����fd�洢���ļ�����Ϣ
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "��Ч��·�� - ";
		for (int i = 2; para[i + 1] != '*'; i++)
		{
			if (para[i] <= 'z' && para[i] >= 'a')
				cout << char(para[i] - 32);
			else
				cout << para[i];
		}
		cout << "\nû�����ļ���\n\n";
		return;
	}
	bool done = true, found_ = search_folder(para);
	if (!found_)
		ctrl[round] = 0;
	int if_is_round1 = 1;
	while (1)
	{
		done = FindNextFileA(hFind, &fdfile);//���ص�ֵ���Ϊ0��û���ļ�ҪѰ��

		if (!done && if_is_round1)
			return;
		if (!strcmp(fdfile.cFileName, "..") || !strcmp(fdfile.cFileName, "."))
			continue;

		if (!done)
			break;
		if_is_round1 = 0;
		if (fdfile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		else
		{
			for (int i = 1; i <= round; i++)
				if (ctrl[i])
					cout << "|   ";
				else
					cout << "    ";
		}
		cout << fdfile.cFileName << endl;
		if (!done)
		{
			cout << endl;
			break;
		}
	}
	for (int i = 1; i <= round; i++)
		if (ctrl[i])
			cout << "|   ";
		else
			cout << "    ";
	cout << endl;
	FindClose(hFind);
	done = true;
	if (!found_)
	{
		return;
	}


	WIN32_FIND_DATAA fdfolder;
	HANDLE hfFind = FindFirstFileA(para, &fdfolder);
	while (1)
	{
		bool done = true;
		done = FindNextFileA(hfFind, &fdfolder); //���ص�ֵ���Ϊ0��û���ļ�ҪѰ

		if (!done)
			break;
		if (!(fdfolder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || (fdfolder.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			continue;
		if (!strcmp(fdfolder.cFileName, ".."))
			continue;
		else//�ҵ������ļ���
		{
			for (int i = 1; i <= round - 1; i++)
				if (ctrl[i])
					cout << "|   ";
				else
					cout << "    ";
		}
		char filename[260] = { 0 };
		strcat(filename, fdfolder.cFileName);
		WIN32_FIND_DATAA temp;
		HANDLE tempFind = FindFirstFileA(para, &temp);
		bool final = true, final_folder = false;
		while (1)
		{
			final = FindNextFileA(tempFind, &temp);
			if (!strcmp(temp.cFileName, filename))
				break;
		}
		while (1)
		{
			final = FindNextFileA(tempFind, &temp);
			if (temp.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				break;
			if (!final)
			{
				final_folder = true;
				break;
			}

		}
		if (final)
			cout << "+---" << fdfolder.cFileName << endl;
		else
		{
			cout << "\\---" << fdfolder.cFileName << endl;
			ctrl[round] = 0;
		}
		ctrl[round + 1] = 1;
		char adr[256] = { 0 };
		for (int i = 0; para[i] != '*'; i++)
			adr[i] = para[i];
		strcat(adr, filename);
		strcat(adr, "/*.*");
		open_folder(adr, round + 1, ctrl);
		if (!done)
		{
			FindClose(hfFind);
			cout << endl;
			return;
		}
	}
}
void openfile(string filename) {
	//���ļ����õ����֣����û�м�ͷ��ʾû�б���
	//�����ʾ���󶨣��滻Ϊ��������ݣ�����open_folder
	ifstream in;
	in.open(filename.c_str(), ios::in);
	while (1) {
		char buff[1024] = { 0 };
		in.getline(buff, 1024);
		if (!in.good())
			break;

		string netdiskname, localname;
		bool link = false;
		int i = 0;
		for (; buff[i] != '\0'; i++) {
			if (buff[i] == '>') {
				link = true;
				break;
			}
		}

		cout << buff << endl;
		buff[i] = 0;
		netdiskname = buff;
		if (!link)
			continue;
		localname = &buff[i + 1];
		localname.append("\\*.*");
		int ctrl[20] = { 0,1 };
		open_folder(localname.c_str(), 1, ctrl);

	}

}
int main() {
	openfile("C:\\Users\\XYxiyang\\Documents\\mycloud\\Liu\\usrconfig.conf");
	return 0;
}