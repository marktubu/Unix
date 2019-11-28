#include "mydb.h"

#include <iostream>

using namespace std;

MyDB::MyDB()
{
	connection = mysql_init(NULL);
	if(connection == NULL)
	{
		cout << "Error: " << mysql_error(connection) << endl;
		exit(1);
	}
}

MyDB::~MyDB()
{
	if(connection != NULL)
	{
		mysql_close(connection);
	}
}

bool MyDB::initDB(string host, string user, string passwd, string dbname)
{
	connection = mysql_real_connect(connection, host.c_str(), user.c_str(), passwd.c_str(), dbname.c_str(), 0, NULL, 0);
	if(connection == NULL)
	{
		cout << "Error: " << mysql_error(connection) << endl;
		exit(1);
	}
	return true;
}

bool MyDB::execSql(string sql)
{
	if(mysql_query(connection, sql.c_str()))
	{
		cout << "Query Error: " << mysql_error(connection) << endl;
		exit(1);
	}
	else
	{
		result = mysql_use_result(connection);
		for(unsigned int i=0;i<mysql_field_count(connection);++i)
		{
			row = mysql_fetch_row(result);
			if(row <= 0)
			{
				break;
			}

			for(unsigned int j=0;j<mysql_num_fields(result);++j)
			{
				cout << row[j] << "  ";
			}

			cout << endl;
		}
	}
	return true;
}

