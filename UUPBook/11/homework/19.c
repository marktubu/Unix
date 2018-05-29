#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	FILE* fp;
	char buf[100];

	pid_t mypid = getpid();
	char command[100];
	sprintf(command, "%s%d","ps | grep ", mypid);
	printf("command is %s\n",command);
	fp = popen(command, "r");

	while(fgets(buf,100,fp) != NULL)
	{
		printf("%s\n",buf);
	}

	memset(command, 0, 100);
	memset(buf,0,100);
	//sprintf(command, "${%s#(.*:.*:[0-9]*)}", buf);
	sprintf(command, "${%s#.*}", buf);

	fp = popen(command, "r");
	
	while(fgets(buf,100,fp)!=NULL)
		printf("%s\n",buf);

	pclose(fp);
	return 0;
}
