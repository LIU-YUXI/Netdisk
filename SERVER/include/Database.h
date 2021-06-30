#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <mysql.h>
using namespace std;

#define myOK 0
#define myERROR -1

class Database
{
public:
    Database();
    bool accountUsed(string account);
    int addUser(string username, string account, string password);
    int findIdByAccount(string account, int &id);
    int loginUser(int &id, string &username, string account, string password);
    int addFile(string md5);
    bool fileExists(string md5);
    int increaseFileLinks(string md5);
    int decreaseFileLinks(string md5);
    int createUserTable(int userId);
    int addLog(int userId, string operation, string message);
    int addBindDirectory(int userId, string dirName);
    bool directoryIsBind(int userId, string dirName);
    int deleteBindDirectory(int userId, string dirName);
    ~Database();

private:
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char queryString[256];
};