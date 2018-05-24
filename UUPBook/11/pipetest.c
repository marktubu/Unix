#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		fprintf(stderr,"%s\n", "pipe error!");
		exit(-1);
	}

	int pid = fork();
	if(pid < 0)
	{
		fprintf(stderr,"%s\n", "pipe error!");
		exit(-1);
	}

	if(pid == 0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		ret = execl("./toUpper","toUpper","",NULL);
		if(ret == -1)
		{
			fprintf(stderr, "%s\n","execl error!");
			exit(-1);
		}

		return 0;
	}

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	char buf[1024];
	int n = read(STDIN_FILENO,buf,1024);
	if(n<0)
	{
		exit(-1);
	}
	write(STDOUT_FILENO,buf,n);
	sleep(1);
	return 0;
}
