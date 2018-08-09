#include <stdio.h>
#include <string.h>

int main()
{
	char* param = "snlua launcher test test2";
	size_t sz = strlen(param);
	char tmp[sz + 1];
	strcpy(tmp,param);
	char* args = tmp;
	char* mod = strsep(&args," \t\r\n");
	args = strsep(&args,"\r\n");
	printf("mod %s\n",mod);
	printf("args %s\n",args);
}
