#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SUBSLEN 10
#define BUFLEN 1024

int getarg(char* src, char* patten)
{
	int err;
	regex_t re;
	size_t len;
	regmatch_t subs[SUBSLEN];
	char matched[BUFLEN];

	err = regcomp(&re,patten,REG_EXTENDED);
	if(err)
	{
		printf("error: regcomp: %d\n", err);
		return 0;
	}
	printf("patten %s\n", patten);

	err = regexec(&re, src, (size_t)SUBSLEN, subs, 0);
	if(err == REG_NOMATCH)
	{
		printf("no match...\n");
		regfree(&re);
		return 0;
	}
	else if(err)
	{
		printf("other error\n");
		return 0;
	}

	for(int i=0;i<re.re_nsub;i++)
	{
		len = subs[i].rm_eo - subs[i].rm_so;
		if(i==0)
		{
			printf("begin: %d, len = %d ",subs[i].rm_so,len);	
		}
		else
		{
			printf("subexpression %d begin: %d, len = %d ",i,subs[i].rm_so,len);
		}

		memcpy(matched,src + subs[i].rm_so, len);
		printf("match %s\n",matched);
	}

	return 0;
}

int main(int ac, char* av[])
{
	int linecount = 0;
	char* filename;
	if(ac == 2)
	{
		filename = av[1];
		linecount = 1;
	}
	else if(ac == 3)
	{
		char* linenum = av[1];
		linenum ++ ;
		int strl = strlen(linenum);
		for(int count = 0;count < strl;count++)
		{
			printf("sss %c %d\n",linenum[count], linenum[count]-48);
			linecount += (linenum[count]-48)*pow(10,strl-1-count);
			printf("linenum %c\n",linenum[count]);
		}
		filename = av[2];
	}

	printf("linecount is %d\n",linecount);
	
	int fd;
	printf("before open");
	if(fd = open(filename, O_RDONLY) == -1)
	{
		printf("open file failed\n");
		return 0;
	}
	printf("before lseek");
	int re = (int)lseek(fd,0,SEEK_END);

	printf("seek error %d",re);
	char cur;
    printf("sss %d",22);	
	while(lseek(fd,-1,SEEK_CUR)!=-1 && linecount > 0)
	{
		printf("%s","sdfgg");
		if(read(fd,&cur,1) == 1)
		{
			printf("cur  %s %d\n",&cur, linecount);
			if(cur == '\n')
				linecount --;
		}
	}
	lseek(fd,1,SEEK_CUR);
	while(read(fd,&cur,1) > 0)
		printf("%s",&cur);

	return 0;
}
