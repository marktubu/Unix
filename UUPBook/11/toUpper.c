#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFSIZE 1024

char toUp(char c)
{
	if(c > 'a' && c < 'z')
	{
		c=c-32;
	}
	return c;
}

int main()
{
	int i=0;
	char buf[BUFSIZE];
	int n=read(STDIN_FILENO,buf,BUFSIZE);
	if(n<0)
	{
		fprintf(stderr,"%s\n","read error!");
		exit(-1);
	}

	for(;i<n;i++)
	{
		buf[i]=toUp(buf[i]);
	}
	printf("%s\n",buf);
	return 0;
}
