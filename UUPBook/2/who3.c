#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define UTMP_ARRAY_SIZE 16

void show_info(struct utmp*);
struct utmp* utmp_next();

struct utmp buf[UTMP_ARRAY_SIZE];
int utmpfd;
int curindex = 0;
int totalcount = 0;
int curread = 0;

int main()
{
	//int utmpfd;
	struct utmp* utbufp;

	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}

	while((utbufp = utmp_next()) != (struct utmp*)NULL)
		show_info(utbufp);

	close(utmpfd);
	return 0;
}

int utmp_reload()
{
	memset(buf,0,sizeof(buf));
	return read(utmpfd,buf,sizeof(buf));
}

struct utmp* utmp_next()
{
	if(curindex == 0)
	{
		int readbytes = utmp_reload();
		curread = (int)(readbytes / sizeof(struct utmp));
	}
	if(curindex > (curread - 1))
	{
		printf("%s\n","index out of range");
		return NULL;
	}

	totalcount ++;
	curindex = totalcount % UTMP_ARRAY_SIZE;
	return (buf + curindex);
}

void show_info(struct utmp* utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	char* cp;
	time_t time = (time_t)utbufp->ut_time;
	cp = ctime(&time);
	printf("%12.12s", cp+4);
	printf(" ");
#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

