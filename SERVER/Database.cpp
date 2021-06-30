#include "Database.h"
using namespace std;

Database::Database()
{
    if ((mysql = mysql_init(NULL)) == NULL)
    {
        cout << "mysql_init failed" << endl;
        exit(0);
    }
    if (mysql_real_connect(mysql, "localhost", "u1951247", "u1951247", "db1951247", 0, NULL, 0) == NULL)
    {
        cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        exit(0);
    }
    mysql_set_character_set(mysql, "gbk");
}

bool Database::accountUsed(string account)
{
    sprintf(queryString, "select * from users where account = '%s'", account.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        exit(0);
    }
    /* 将查询结果存储起来，出现错误则返回NULL
       注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        cout << "mysql_store_result failed" << endl;
        exit(0);
    }
    /* 打印当前查询到的记录的数量 */
    if ((int)mysql_num_rows(result) == 0)
    {
        mysql_free_result(result);
        return false;
    }
    else
    {
        mysql_free_result(result);
        return true;
    }
}

int Database::addUser(string username, string account, string password)
{
    sprintf(queryString, "insert into users(username, account, password) values('%s', '%s', '%s')", username.c_str(), account.c_str(), password.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::loginUser(int &id, string &username, string account, string password)
{
    sprintf(queryString, "select * from users where account = '%s'", account.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        cout << "mysql_store_result failed" << endl;
        return myERROR;
    }
    if ((int)mysql_num_rows(result) == 0)
        return myERROR;
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        if (!strcmp(row[3], password.c_str()))
        {
            id = atoi(row[0]);
            username = string(row[1]);
            return myOK;
        }
    }
    return myERROR;
}

int Database::addFile(string md5)
{
    sprintf(queryString, "insert into fileLinks(md5) values('%s')", md5.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

bool Database::fileExists(string md5)
{
    sprintf(queryString, "select * from fileLinks where md5 = '%s'", md5.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        exit(0);
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        cout << "mysql_store_result failed" << endl;
        exit(0);
    }
    if ((int)mysql_num_rows(result) == 0)
    {
        mysql_free_result(result);
        return false;
    }
    else
    {
        mysql_free_result(result);
        return true;
    }
}

int Database::increaseFileLinks(string md5)
{
    sprintf(queryString, "update fileLinks set links = links + 1 where md5 = '%s'", md5.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::decreaseFileLinks(string md5)
{
    sprintf(queryString, "update fileLinks set links = links - 1 where md5 = '%s'", md5.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::createUserTable(int userId)
{
    sprintf(queryString, "create table user%d(dirId integer primary key auto_increment, dirName varchar(128)) ", userId);
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::addLog(int userId, string operation, string message)
{
    sprintf(queryString, "insert into logs(userId, operation, message) values(%d, '%s', '%s')", userId, operation.c_str(), message.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::addBindDirectory(int userId, string dirName)
{
    sprintf(queryString, "insert into user%d(dirName) values('%s')", userId, dirName.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

bool Database::directoryIsBind(int userId, string dirName)
{
    sprintf(queryString, "select * from user%d where dirName = '%s'", userId, dirName.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        exit(0);
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        cout << "mysql_store_result failed" << endl;
        exit(0);
    }
    if ((int)mysql_num_rows(result) == 0)
        return false;
    else
        return true;
}

int Database::deleteBindDirectory(int userId, string dirName)
{
    sprintf(queryString, "delete from user%d where dirName = '%s'", userId, dirName.c_str());
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

Database::~Database()
{
    mysql_close(mysql);
}