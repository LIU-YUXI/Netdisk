#include <iostream>
#include "Database.h"
using namespace std;

int main(int argc, char *argv[])
{
    Database db;
    if (false)
    {
        // test accountUsed
        string account;
        while (true)
        {
            cin >> account;
            if (account == "exit")
                break;
            else
            {
                cout << "accountUsed: " << boolalpha << db.accountUsed(account) << endl;
            }
        }
    }
    if (false)
    {
        // test addUser
        string username, account, password;
        while (true)
        {
            cout << "Please input the username: ";
            cin >> username;
            if (username == "exit")
                break;
            cout << "Please input the account: ";
            cin >> account;
            cout << "Please input the password: ";
            cin >> password;
            cout << "addUser: " << db.addUser(username, account, password) << endl;
        }
    }
    if (false)
    {
        // test loginUser
        int id;
        string username, account, password;
        while (true)
        {
            cout << "Please input the account: ";
            cin >> account;
            if (account == "exit")
                break;
            cout << "Please input the password: ";
            cin >> password;
            cout << "loginUser: " << db.loginUser(id, username, account, password) << endl;
            cout << "id: " << id << endl;
            cout << "username: " << username << endl;
        }
    }
    if (false)
    {
        // test addFile
        string md5;
        while (true)
        {
            cout << "Please input the md5: ";
            cin >> md5;
            if (md5 == "exit")
                break;
            cout << "addFile: " << db.addFile(md5) << endl;
        }
    }
    if (false)
    {
        // test increase and decrease file links
        string md5;
        bool increase;
        while (true)
        {
            cout << "Please input the md5: ";
            cin >> md5;
            if (md5 == "exit")
                break;
            cout << "Please input the increase: ";
            cin >> increase;
            if (increase)
                cout << "increaseFileLinks: " << db.increaseFileLinks(md5) << endl;
            else
                cout << "increaseFileLinks: " << db.decreaseFileLinks(md5) << endl;
        }
    }
    if (false)
    {
        // test create user table
        int userId;
        while (true)
        {
            cout << "Please input the userId: ";
            cin >> userId;
            if (userId == -1)
                break;
            cout << "createUserTable: " << db.createUserTable(userId) << endl;
        }
    }
    if (false)
    {
        // test add log
        int userId;
        string operation, message;
        while (true)
        {
            cout << "Please input the userId: ";
            cin >> userId;
            if (userId == -1)
                break;
            cout << "Please input the operation: ";
            cin >> operation;
            cout << "Please input the message: ";
            cin >> message;
            cout << "addLog: " << db.addLog(userId, operation, message) << endl;
        }
    }
    if (false)
    {
        // test add bind directory
        int userId;
        string dirName;
        while (true)
        {
            cout << "Please input the userId: ";
            cin >> userId;
            if (userId == -1)
                break;
            cout << "Please input the dirName: ";
            cin >> dirName;
            cout << "addBindDirectory: " << db.addBindDirectory(userId, dirName) << endl;
        }
    }
    if (true)
    {
        // test directoryIsBind and deleteBindDirectory
        int userId;
        string dirName;
        bool deleteDir;
        while (true)
        {
            cout << "Please input the userId: ";
            cin >> userId;
            if (userId == -1)
                break;
            cout << "Please input the dirName: ";
            cin >> dirName;
            cout << "directoryIsBind: " << db.directoryIsBind(userId, dirName) << endl;
            cout << "Delete this directory? ";
            cin >> deleteDir;
            if (deleteDir)
                cout << "deleteBindDirectory: " << db.deleteBindDirectory(userId, dirName) << endl;
        }
    }
    return 0;
}
