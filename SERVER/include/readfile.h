#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <stdio.h>
#include <dirent.h>
using namespace std;
#define myOK 0
#define myERROR -1
// ����һ���ļ�
int read(string filename, string &content);
struct file
{
    bool is_file;
    string filename;
    string md5;
    string path;
};
// ��Ŀ¼�������ļ�����files
int userfiles(int userid, string rootdir, queue<file> &files, bool is_root = false);
// ������ڸ��ļ�������д��������������ͷд
int writefile(string filename, string content);
int renewfile(string filename, string content);