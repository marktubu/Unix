#include<stdio.h>
#include<pthread.h>
#include<ctype.h>
#include<stdlib.h>

int total_words;

void* wordcount(void*);

int main(int argc, char* argv[])
{
	pthread_t t1,t2;

	if(argc!=3)
	{
		printf("usage: %s file1 file2\n",argv[0]);
		exit(1);
	}
	printf("argv[0] is %s", argv[0]);

	total_words = 0;
	pthread_create(&t1, NULL, wordcount, (void*)argv[1]);
	pthread_create(&t2, NULL, wordcount, (void*)argv[2]);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("%5d: total words \n", total_words);
	return 0;
}

void* wordcount(void* m)
{
	char* filename = (char*) m;
	FILE* fp;
	int c,prevc = '\0';

	if((fp = fopen(filename,"r"))!=NULL)
	{
		while((c=getc(fp))!=EOF)
		{
			if(!isalnum(c) && isalnum(prevc))
				total_words ++;
			prevc = c;
		}
		fclose(fp);
	}
	else
		perror(filename);

	return NULL;
}

