#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string>
#include <ImageHlp.h>  
#pragma comment(lib,"imagehlp.lib")
#pragma comment(lib,"Advapi32.lib")
using namespace std;


const string file1 = "C:\\Users\\";
const string file2 = "\\Documents\\mycloud\\";
const string file3 = "\\usrconfig.conf";

const string path1 = "C:\\Users\\";
const string path2 = "\\Documents\\mycloud\\";
const string path3 = "\\";

bool addDir(string filename,string dirname,string clientusrname) {
	fstream out;
	out.open(filename, ios::out | ios::app |ios::in);
	while (1) {
		char buff[1024] = { 0 };
		out.getline(buff, 1024);
		if (!out.good())
			break;
		string child = buff;
		if (child.find(dirname, 0) != -1){
			cout << "path already exist" << endl;
			return false;
		}
	}
	out.clear();
	out << dirname << endl;
	string path;
	path += path1;
	//path.append(winusrname);
	path.append("fyl06");
	path += path2;
	path += clientusrname;
	path += path3;
	path += dirname;
	path.append("\\");
	MakeSureDirectoryPathExists(path.c_str());
	out.close();
	return true;
}
bool bondDir(string filename,string dir1,string dir2) {

	WIN32_FIND_DATAA fdfile;
	HANDLE hFind = FindFirstFileA((dir2+"\\*.*").c_str(), &fdfile);
	if (hFind == INVALID_HANDLE_VALUE) {
		cout << "file doesn't exist" << endl;
		return false;//目的路径不存在
	}
	int level = 0;
	fstream file;
	file.open(filename.c_str(), ios::in | ios::out);
	for (int i = 0; i < (int)dir1.length(); i++) {
		if (dir1[i] == '\\')
			level++;
	}
	file.seekg(0, ios::beg);
	bool found=false;
	while (1) {
		char buff[1024] = { 0 };
		file.getline(buff, 1024);
		if (!file.good())
			break;

		int cur_level = 0;
		bool bonded = false;
		int i = 0;
		for (i = 0; buff[i] != '\0'; i++) {
			if (buff[i] == '\\')
				cur_level++;
			if (buff[i] == '>') {
				bonded = true;
				break;
			}
		}
		string child = buff;
		//cout << child << endl;
		//cout << cur_level << ' ' << level << endl;
		if (child.find(dir1, 0) != -1 && bonded == true && cur_level>level) {//子文件夹被绑定了
			cout << "child path have been boned" << endl;
			return false;
		}
		if (dir1.find(child.substr(0,i), 0) != -1 && bonded == true && cur_level < level) {//子文件夹被绑定了
			cout << "father path have been boned" << endl;
			return false;
		}
		if (child.find(dir1, 0) != -1 && cur_level == level)
			found = true;

	}
	file.close();
	if (!found) {
		cout << "netdisk folder dosen't exist" << endl;
		return false;
	}
	file.open(filename.c_str(), ios::in | ios::out);
	string content;
	while(1){
		char buff[1024] = { 0 };
		file.getline(buff, 1024);
		if (!file.good())
			break;

		int cur_level = 0;
		bool bonded = false;
		int i = 0;
		for (i = 0; buff[i] != '\0'; i++) {
			if (buff[i] == '\\')
				cur_level++;
			if (buff[i] == '>')
				break;
		}
		string line = buff;
		if (line.find(dir1) != -1 && cur_level == level) {
			buff[i] = '>';
			for (int j = i + 1; buff[j] != '\0'; j++)
				buff[j] = '\0';
			strcat(buff, dir2.c_str());
		}
		content.append(buff);
		content.append("\n");
	}
	file.close();
	file.open(filename.c_str(), ios::out | ios::trunc);
	//cout <<  content << endl;
	file << content;
	file.close();
	return true;
}
bool deleteDir(string filename, string dirname,string clientusrname) {//可以优化 是否删除目录下的全部文件
	fstream out;
	out.open(filename, ios::out | ios::app | ios::in);
	int level = 0;
	for (int i = 0; i < (int)dirname.length(); i++) {
		if (dirname[i] == '\\')
			level++;
	}
	string content;
	bool found=false;
	while (1) {
		char buff[1024] = { 0 };
		out.getline(buff, 1024);
		if (!out.good())
			break;

		int cur_level = 0;
		bool bonded = false;
		int i = 0;
		for (i = 0; buff[i] != '\0'; i++) {
			if (buff[i] == '\\')
				cur_level++;
			if (buff[i] == '>')
				break;
		}
		string child = buff;
		//cout << child << endl;
		//cout << cur_level << ' ' << level << endl;
		if (child.find(dirname, 0) != -1&&cur_level>level) {
			cout << "other folders in this folder" << endl;
			return false;
		}
		if (child.find(dirname, 0) != -1 && cur_level == level) {
			found=true;
			continue;

		}
		content += child;
		content.append("\n");
	}
	if (!found) {
		cout << "netdisk folder dosen't exist" << endl;
		return false;
	}
	string path;
	path += path1;
	//path.append(winusrname);
	path.append("fyl06");
	path += path2;
	path += clientusrname;
	path += path3;
	path += dirname;
	path.append("\\");
	RemoveDirectoryA(path.c_str());
	out.close();
	out.open(filename.c_str(), ios::out | ios::trunc);
	out << content;
	out.close();
	return true;
}
bool unbondDir(string filename, string dirname) {
	fstream out;
	out.open(filename, ios::out | ios::app | ios::in);
	int level = 0;
	for (int i = 0; i < (int)dirname.length(); i++) {
		if (dirname[i] == '\\')
			level++;
	}
	string content;
	bool found = false;
	while (1) {
		char buff[1024] = { 0 };
		out.getline(buff, 1024);
		if (!out.good())
			break;

		int cur_level = 0;
		bool bonded = false;
		int i = 0;
		for (i = 0; buff[i] != '\0'; i++) {
			if (buff[i] == '\\')
				cur_level++;
			if (buff[i] == '>')
				break;
		}
		string child = buff;
		//cout << child << endl;
		//cout << cur_level << ' ' << level << endl;
		if (child.find(dirname, 0) != -1 && cur_level == level) {
			if (buff[i] != '>') {
				cout << "this folder isn't bonded" << endl;
				return false;
			}
			found = true;
			content += child.substr(0,child.find(">"));
			content.append("\n");
			continue;
		}
		content += child;
		content.append("\n");
	}
	if (!found) {
		cout << "netdisk folder dosen't exist" << endl;
		return false;
	}
	out.close();
	out.open(filename.c_str(), ios::out | ios::trunc);
	out << content;
	out.close();
	return true;
}
void createFoldersbyFile(string filename,string dir) {
	string path = dir+"\\";
	fstream file;
	file.open(filename.c_str(), ios::in);
	while (1) {
		char buff[1024] = { 0 };
		file.getline(buff, 1024);
		if (!file.good())
			break;
		int i = 0;
		for (i = 0; buff[i] != '\0'&&buff[i]!='\r'; i++) {
			if (buff[i] == '>') {
				
				break;
			}
		}
		buff[i] = '\0';
		MakeSureDirectoryPathExists((path+buff+"\\").c_str());
	}
	file.close();
}
int masin() {
	string clientusrname = "Liu";//到时候根据登录名进行修改
	char winusrname[256] = { 0 };
	DWORD dwSize = 256;
	GetUserNameA(winusrname, &dwSize);
	string file;
	file += file1;
	//file.append(winusrname);
	file.append("fyl06");
	file += file2;
	file += clientusrname;
	file += file3;

	fstream in;
	in.open(file.c_str());
	if (in) {
		//createFoldersbyFile(file, file1 + "fyl06" + file2 + clientusrname);
		bondDir(file,clientusrname + "-root\\folderB", "D:\\linux_beta");
		//addDir(file, "rootB",clientusrname);
		//cout<<deleteDir(file, "Liu-root\\folderA", clientusrname);
		//cout << unbondDir(file, clientusrname + "-root\\folderA");
		in.close();
	}//配置文件存在，可以读取绑定目录
	else {
		string path;
		path += path1;
		//path.append(winusrname);
		path.append("fyl06");
		path += path2;
		path += clientusrname;
		path += path3;
		MakeSureDirectoryPathExists(path.c_str());
		fstream out;
		out.open(file.c_str(), ios::out);
		path += clientusrname;
		path.append("-root\\");
		MakeSureDirectoryPathExists(path.c_str());
		out << clientusrname << "-root" << endl;
		MakeSureDirectoryPathExists((path+"folderA\\").c_str());
		out << clientusrname << "-root\\folderA" << endl;
		MakeSureDirectoryPathExists((path + "folderB\\").c_str());
		out << clientusrname << "-root\\folderB" << endl;
		MakeSureDirectoryPathExists((path + "folderC\\").c_str());
		out << clientusrname << "-root\\folderC" << endl;

		out.close();

		
		
	}//进行目录绑定
	return 0;
}

