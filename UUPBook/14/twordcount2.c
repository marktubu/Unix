#include<stdio.h>
#include<pthread.h>
#include<ctype.h>
#include<stdlib.h>

int total_words;

void* wordcount(void*);

struct arg
{
	char* filename;
	int count;
};

int main(int argc, char* argv[])
{
	pthread_t t1,t2;
	struct arg arg1,arg2;
	if(argc!=3)
	{
		printf("usage: %s file1 file2\n",argv[0]);
		exit(1);
	}
	
	arg1.filename = argv[1];
	arg1.count = 0;
	arg2.filename = argv[2];
	arg2.count = 0;

	total_words = 0;
	pthread_create(&t1, NULL, wordcount, (void*)&arg1);
	pthread_create(&t2, NULL, wordcount, (void*)&arg2);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("file1 word count is %d\n",arg1.count);
	printf("file2 word count is %d\n",arg2.count);
	printf("%5d: total words \n", arg1.count + arg2.count);
	return 0;
}

void* wordcount(void* m)
{
	struct arg* a = (struct arg*) m;
	char* filename = (char*) a->filename;
	FILE* fp;
	int c,prevc = '\0';

	if((fp = fopen(filename,"r"))!=NULL)
	{
		while((c=getc(fp))!=EOF)
		{
			if(!isalnum(c) && isalnum(prevc))
				a->count ++;
			prevc = c;
		}
		fclose(fp);
	}
	else
		perror(filename);

	return NULL;
}

