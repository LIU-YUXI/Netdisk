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

string findlinkFolder(string in,string path,bool &linked,int length) {
	linked = false;
	if (path.length() < length)
		return "no";
	int pos1 = 0, pos2 = 0;
	
	path.erase(path.length()- 4);
	string folder = path.substr(length);
	while (1) {
		if (pos2 == in.length()) {
			return "nothing";
		}
		if (in[pos2] == '\n') {
			string temp = in.substr(pos1, pos2 - pos1 + 1);
			
			if (temp.find(folder) != -1) {
				if (temp.find(">") != -1) {
					linked = true;
					return temp.substr(temp.find(">")+1);
				}
				else {
					linked = false;
					return "ababa";
				}
			}
			pos1 = pos2 + 1;
		}
		pos2++;
	}

}
bool search_folder(const char para[],string content,int length)
{
	WIN32_FIND_DATAA fdfile;
	HANDLE hFind = FindFirstFileA(para, &fdfile);//第一个参数是路径名，可以使用通配符，fd存储有文件的信息
	bool done = true, found_fondfolder = false;
	while (1)
	{
		done = FindNextFileA(hFind, &fdfile); //返回的值如果为0则没有文件要寻了
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
void open_folder(const char para[], int round, int ctrl[],string content,int length)
{
	WIN32_FIND_DATAA fdfile;
	HANDLE hFind = FindFirstFileA(para, &fdfile);//第一个参数是路径名，可以使用通配符，fd存储有文件的信息
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "无效的路径 - ";
		for (int i = 2; para[i + 1] != '*'; i++)
		{
			if (para[i] <= 'z' && para[i] >= 'a')
				cout << char(para[i] - 32);
			else
				cout << para[i];
		}
		cout << "\n没有子文件夹\n\n";
		return;
	}
	bool done = true, found_ = search_folder(para,content,length);
	if (!found_)
		ctrl[round] = 0;
	int if_is_round1 = 1;
	while (1)
	{
		done = FindNextFileA(hFind, &fdfile);//返回的值如果为0则没有文件要寻了

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
		done = FindNextFileA(hfFind, &fdfolder); //返回的值如果为0则没有文件要寻

		if (!done)
			break;
		if (!(fdfolder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || (fdfolder.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			continue;
		if (!strcmp(fdfolder.cFileName, ".."))
			continue;
		else//找到的是文件夹
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
		char adr[512] = { 0 };
		for (int i = 0; para[i] != '*'; i++)
			adr[i] = para[i];
		strcat(adr, filename);
		bool islinked;
		strcat(adr, "\\*.*");
		
		string a=findlinkFolder(content, adr, islinked, length);
		if (islinked) {
			memset(adr, 0, 260);
			a.erase(a.length() - 1);
			sprintf_s(adr, 260, "%s", a.c_str());
			strcat(adr, "\\*.*");
		}
		open_folder(adr, round + 1, ctrl,content,length);
		if (!done)
		{
			FindClose(hfFind);
			cout << endl;
			return;
		}
	}
}
void openfile(string filename) {
	//从文件中拿到名字，如果没有箭头表示没有被绑定
	//否则表示被绑定，替换为后面的内容，调用open_folder
	ifstream in;
	in.open(filename.c_str(), ios::in);
	int ctrl[20] = { 0,1 };
	string content;
	while (in.good())
		content.insert(content.length(),1,(char)in.get());
	in.close();
	cout << "Liu-root" << endl;
	int length = strlen("C:\\Users\\fyl06\\Documents\\mycloud\\Liu\\");
	open_folder("C:\\Users\\fyl06\\Documents\\mycloud\\Liu\\Liu-root\\*.*",1, ctrl, content,length);

}

int main() {
	openfile("C:\\Users\\fyl06\\Documents\\mycloud\\Liu\\usrconfig.conf");
	return 0;
}
