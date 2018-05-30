#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main(int ac, char* av[])
{
	int pipefd[2];
	int childpipefd[2];
	char* buf;
	pid_t pid;
	printf("%s\n","test");
	if(ac < 2)
	{
		fprintf(stderr, "argument too short");
		exit(1);
	}

    buf = av[1]; 
    
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	
	if(pipe(childpipefd) == -1)
	{
		perror("child pipe");
		exit(1);
	}

	pid = fork();
	if(pid == -1)
	{
		perror("fork");
		exit(1);
	}
	printf("fork");	
	if(pid == 0)
	{
		printf("%s\n","child");
		int file = open("test2.txt", O_RDWR);
		close(pipefd[WRITE]);
		close(childpipefd[READ]);
		sleep(0.2);
		char arr[50];
		printf("%s\n","before read");
		read(pipefd[READ],arr,50);
		printf("arr %s\n",arr);
		write(file,arr,50);
		close(file);
		char command[100];
		sprintf(command,"sort %s", "test2.txt");
		FILE* fp = popen(command, "r");
		int c;
		printf("%s\n","test2");
		FILE* pfp2 = fdopen(childpipefd[WRITE],"w");
		while((c=getc(fp))!=EOF)
			putc(c, pfp2);

	}
	else
	{
		printf("%s\n","parent");
		FILE* file = fopen("test.txt", "r+w");
		close(pipefd[READ]);
		close(childpipefd[WRITE]);
		int c;
		FILE* pfp2 = fdopen(pipefd[WRITE],"w");
		while((c=getc(file))!=EOF)
			putc(c,pfp2);
		printf("%s\n","parent test");
		sleep(2);
		char arr[50];
		read(childpipefd[READ],arr,50);
		printf("%s\n",arr);
	}
	
	return 0;
}
