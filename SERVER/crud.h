#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
using namespace std;

#define myOK 0
#define myERROR -1
string getFullFileName(int userId, string fileName);
int sameNameFile(int userId, string fileName, string md5)
int createFile(int userId, bool isDirectory, string fileName, string md5);
int deleteFile(int userId, string fileName);
int renameFile(int userId, string fileName, string newFileName);
int updateFile(int userId, string fileName, string md5);
