#include "../include/crud.h"
#include "../include/Database.h"
// 以下fileName全部指代从用户根目录开始的路径，并且包括文件名，如果目录则包括目录名，最后没有斜杠
// 如，.../users/1/homework.pdf，则userId为1，fileName为homework.pdf;
// 如，.../users/1/sports/images/swimming.jpg，则userId为1，fileName为sports/images/swimming.jpg;

string rootPath = "/home/u1951247/netdisk/CRUD/test/";

string getFullFileName(int userId, string fileName)
{
    stringstream ss;
    ss << rootPath << userId << '/' << fileName;
    return ss.str();
}

int sameNameFile(int userId, string fileName, string md5)
{
    string fullFileName = getFullFileName(userId, fileName);
    if ((access(fullFileName.c_str(), F_OK)) == -1)
        return 0;
    else
    {
        ifstream infile(fullFileName, ios::in);
        string serverMd5;
        infile >> serverMd5;
        infile.close();
        if (serverMd5 == md5)
            return 1;
        else
            return 2;
    }
}

int createFile(int userId, bool isDirectory, string fileName, string md5)
{
    string fullFileName = getFullFileName(userId, fileName);
    if (isDirectory)
    {
        if (mkdir(fullFileName.c_str(), 0755) == -1)
        {
            cerr << "mkdir error" << endl;
            return myERROR;
        }
    }
    else
    {
        ofstream outfile(fullFileName, ios::out);
        outfile << md5;
        outfile.close();
    }
    return 0;
}

int deleteFile(int userId, string fileName)
{
    string fullFileName = getFullFileName(userId, fileName);
    if (remove(fullFileName.c_str()) == 0)
        return myOK;
    else
        return myERROR;
}

int renameFile(int userId, string fileName, string newFileName)
{
    int i = 0;
    for (i = fileName.length() - 1; i >= 0; i--)
    {
        if (fileName[i] == '/')
            break;
    }
    string fullnewpath = fileName;
    fullnewpath.resize(i + 1);
    fullnewpath += newFileName;
    newFileName = fullnewpath;
    string fullFileName = getFullFileName(userId, fileName);
    if (rename(fullFileName.c_str(), newFileName.c_str()) == 0)
        return myOK;
    else
        return myERROR;
}

int updateFile(int userId, string fileName, string md5)
{
    string fullFileName = getFullFileName(userId, fileName);
    ofstream outfile(fullFileName, ios::out);
    outfile << md5;
    outfile.close();
    return myOK;
}
/*
int main()
{
    if (true)
    {
        // test same name file
        string fileName, md5;
        while (true)
        {
            cout << "Please input the filename: ";
            cin >> fileName;
            cout << "Please input the md5: ";
            cin >> md5;
            cout << "sameNameFile: " << sameNameFile(1, fileName, md5) << endl;
        }
    }
    return 0;
}
*/
