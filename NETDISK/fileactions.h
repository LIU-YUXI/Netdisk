#ifndef FILEACTIONS_H
#define FILEACTIONS_H

#endif // FILEACTIONS_H
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<cstdlib>
#include<thread>
#include<time.h>
#include<string>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<cstring>
#include<direct.h>
#include <ImageHlp.h>
using namespace std;
const string file1 = "C:\\mycloud\\";
const string file2 = "\\usrconfig.conf";

const string path1 = "C:\\mycloud\\";
const string path2 = "\\";

void openMonitorThread(string dir);
string openFile(string filename,int length);
void makesureConfigexist();
void createFoldersbyFile(string filename,string dir);
bool addDir(string filename,string dirname,string clientusrname);
bool bondDir(string filename,string dir1,string dir2);
bool deleteDir(string filename, string dirname,string clientusrname);
bool unbondDir(string filename, string dirname);
