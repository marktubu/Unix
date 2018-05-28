#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>

struct arg_set{
	char* fname;
	int count;
};

struct arg_set* mailbox;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag = PTHREAD_COND_INITIALIZER;

void * count_words(void* arg)
{
	struct arg_set* m_arg = arg;
	FILE* fp;
	int c, prevc = '\0';
	if((fp = fopen(m_arg->fname, "r"))!= NULL)
	{
		while((c=getc(fp))!=EOF)
		{
			if(!isalnum(c) && isalnum(prevc))
				m_arg->count ++;
			prevc = c;
		}
		fclose(fp);
	}
	else
		perror(m_arg->fname);
	printf("count : waiting to get lock\n");
	pthread_mutex_lock(&lock);
	if(mailbox!=NULL)
		pthread_cond_wait(&flag,&lock);
	mailbox = m_arg;
	pthread_cond_signal(&flag);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(int ac, char* av[])
{
	pthread_t t1,t2;
	struct arg_set arg1, arg2;
	int reports_in = 0;
	int total_words = 0;
	if(ac != 3)
	{
		printf("usage: %s file1 file2 \n", av[0]);
		exit(1);
	}
	pthread_mutex_lock(&lock);
	arg1.fname = av[1];
	arg1.count = 0;
	pthread_create(&t1,NULL,count_words,(void*)&arg1);
	
	arg2.fname = av[2];
	arg2.count = 0;
	pthread_create(&t2,NULL,count_words,(void*)&arg2);

	while(reports_in < 2)
	{
		printf("main: waiting for flag to go up\n");
		pthread_cond_wait(&flag, &lock);
		printf("main: wow! flag was raised, i have the lock\n");
		total_words += mailbox->count;
		if(mailbox == &arg1)
			pthread_join(t1,NULL);
		if(mailbox == &arg2)
			pthread_join(t2,NULL);
		mailbox = NULL;
		pthread_cond_signal(&flag);
		reports_in ++;
	}

	printf("%7d : total words \n", total_words);

	return 0;
}

