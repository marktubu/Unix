#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>

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
	int linecount = 1;
	char* filename;
	if(ac == 2)
	{
		filename = av[1];
	}
	else if(ac == 3)
	{
		char* linenum = "begineerrttyyyytendsssssss";
		char patten[] = "begin(.*?)end";
		linecount = getarg(linenum,patten);
		filename = av[2];
	}

	return 0;
}
