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
int read(const char *filename, string &content);
struct file
{
    bool is_file;
    string filename;
    string md5 = NULL;
    string path;
};
// ��Ŀ¼�������ļ�����files
int userfiles(int userid, const char *rootdir, queue<file> &files, bool is_root = false);
// ������ڸ��ļ�������д��������������ͷд
int writefile(const char *filename, string content);
