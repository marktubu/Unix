#ifndef MYSQL_H
#define MYSQL_H

#include <string>
#include <mysql/mysql.h>

using namespace std;

class MyDB
{
public:
	MyDB();
	~MyDB();

	bool initDB(string host, string user, string passwd, string dbname);
	bool execSql(string sql);
private:
	MYSQL* connection;
	MYSQL_RES* result;
	MYSQL_ROW row;
};


#endif
