#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define UTMP_ARRAY_SIZE 16

void show_info(struct utmp*);
int utmp_next(int, struct utmp*, int);

int main()
{
	int utmpfd;
	struct utmp buf[UTMP_ARRAY_SIZE];
	int buflen = sizeof(buf);

	//if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	if((utmpfd = open("utmp", O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	printf("utmp file %s\n",UTMP_FILE);	
	while(utmp_next(utmpfd, buf, buflen) > 0)
	{
		for(int i=0;i<UTMP_ARRAY_SIZE;i++)
		{
			struct utmp* u =(struct utmp*) (buf+i);
			if(u!=NULL)
				show_info(u);
		}
	}
	close(utmpfd);
	return 0;
}

int utmp_next(int utmpfd, struct utmp* buf, int buflen)
{
	memset(buf,0,buflen);
	return read(utmpfd, buf, buflen);
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
