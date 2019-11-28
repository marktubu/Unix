#include "mydb.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "arg error" << endl;
		exit(1);
	}
	string sql(argv[1]);
	MyDB db;
	string host("localhost");
	string user("root");
	string passwd("123456");
	string dbname("game");
	db.initDB(host, user, passwd, dbname);
	db.execSql(sql);
	return 0;
}
