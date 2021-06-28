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

int main() {
	string clientusrname = "Liu";//到时候根据登录名进行修改
	char winusrname[256] = { 0 };
	DWORD dwSize = 256;
	GetUserNameA(winusrname, &dwSize);
	string file;
	file += file1;
	file.append(winusrname);
	file += file2;
	file += clientusrname;
	file += file3;

	ifstream in;
	in.open(file.c_str());
	if (in) {
		cout << "exist" << endl;


		in.close();
	}//配置文件存在，可以读取绑定目录
	else {
		string path;
		path += path1;
		path.append(winusrname);
		path += path2;
		path += clientusrname;
		path += path3;
		MakeSureDirectoryPathExists(path.c_str());
		ofstream out;
		out.open(file.c_str(), ios::out);
		out << clientusrname << "\\root" << endl;
		out << clientusrname << "\\root\\folderA" << endl;
		out << clientusrname << "\\root\\folderB" << endl;
		out << clientusrname << "\\root\\folderC" << endl;


		out.close();
		
	}//进行目录绑定
}
