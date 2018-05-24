#include "stdio"
#define oops(m,x) {perror(m); exit(x);}

void main()
{
	int pid,todc[2],fromdc[2];
	if(pipe(todc) == -1||pipe(fromdc) == -1)
	{
		oops("pipe failed",1);
	}

	if((pid = fork()) == -1)
	{
		oops("cannot fork",2);
	}

	
}
