#include "../include/Database.h"
using namespace std;

Database::Database()
{
    cout << "calling function: Database constructor" << endl;
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
    cout << "calling function: accountUsed" << endl;
    sprintf(queryString, "select * from users where account = '%s'", account.c_str());
    cout << "queryString: " << queryString << endl;
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
    cout << "calling function: addUser" << endl;
    sprintf(queryString, "insert into users(username, account, password) values('%s', '%s', '%s')", username.c_str(), account.c_str(), password.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::findIdByAccount(string account, int &id)
{
    cout << "calling function: findIdByAccount" << endl;
    sprintf(queryString, "select * from users where account = '%s'", account.c_str());
    cout << "queryString: " << queryString << endl;
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
        return myERROR;
    }
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        id = atoi(row[0]);
        return myOK;
    }
    return myERROR;
}

int Database::loginUser(int &id, string &username, string account, string password)
{
    cout << "calling function: loginUser" << endl;
    sprintf(queryString, "select * from users where account = '%s'", account.c_str());
    cout << "queryString: " << queryString << endl;
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
    {
        cout << "账号不存在" << endl;
        return myERROR;
    }
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        cout << "id " << row[0] << endl;
        cout << "username " << row[1] << endl;
        cout << "account " << row[2] << endl;
        cout << "password " << row[3] << endl;
        if (!strcmp(row[3], password.c_str()))
        {
            id = atoi(row[0]);
            username = string(row[1]);
            return myOK;
        }
    }
    cout << "密码错误" << endl;
    return myERROR;
}

int Database::addFile(string md5)
{
    cout << "calling function: addFile" << endl;
    sprintf(queryString, "insert into fileLinks(md5) values('%s')", md5.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

bool Database::fileExists(string md5)
{
    cout << "calling function: fileExists" << endl;
    sprintf(queryString, "select * from fileLinks where md5 = '%s'", md5.c_str());
    cout << "queryString: " << queryString << endl;
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
    cout << "calling function: increaseFileLinks" << endl;
    sprintf(queryString, "update fileLinks set links = links + 1 where md5 = '%s'", md5.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::decreaseFileLinks(string md5)
{
    cout << "calling function: decreaseFileLinks" << endl;
    sprintf(queryString, "update fileLinks set links = links - 1 where md5 = '%s'", md5.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::createUserTable(int userId)
{
    cout << "calling function: createUserTable" << endl;
    sprintf(queryString, "create table user%d(dirId integer primary key auto_increment, dirName varchar(128)) ", userId);
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::addLog(int userId, string operation, string message)
{
    cout << "calling function: addLog" << endl;
    sprintf(queryString, "insert into logs(userId, operation, message) values(%d, '%s', '%s')", userId, operation.c_str(), message.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

int Database::addBindDirectory(int userId, string dirName)
{
    cout << "calling function: addBindDirectory" << endl;
    sprintf(queryString, "insert into user%d(dirName) values('%s')", userId, dirName.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

bool Database::directoryIsBind(int userId, string dirName)
{
    cout << "calling function: directoryIsBind" << endl;
    sprintf(queryString, "select * from user%d where dirName = '%s'", userId, dirName.c_str());
    cout << "queryString: " << queryString << endl;
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
    cout << "calling function: deleteBindDirectory" << endl;
    sprintf(queryString, "delete from user%d where dirName = '%s'", userId, dirName.c_str());
    cout << "queryString: " << queryString << endl;
    if (mysql_query(mysql, queryString))
    {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return myERROR;
    }
    return myOK;
}

Database::~Database()
{
    cout << "Database deconstructor" << endl;
    mysql_close(mysql);
}