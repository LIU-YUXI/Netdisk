#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <dirent.h>
using namespace std;
// 读入一个文件
int read(const char* filename,string &content);
struct file{
    bool is_file;
    string filename;
    string md5=NULL;
    string path;
};
// 将目录下所有文件存入files
int userfiles(const char* rootdir,vector<file>&files);