#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

int mailbox = 0;
int total = 0;

void* threadfunc(void *arg)
{
	int count =*((int*) arg);
	printf("count %d\n",count);
	pthread_mutex_lock(&mutex);
	if(mailbox != 0)
		pthread_cond_wait(&cond, &mutex);
	mailbox = 1;
	total += count;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		perror("arg count != 3");
		exit(1);
	}
	
	int count1 = (int) (*argv[1]);
	int count2 = (int) (*argv[2]);
	
	pthread_cond_init(&cond, NULL);
	pthread_t t1,t2;
	pthread_create(&t1, NULL, threadfunc, (void*)&count1);
	pthread_create(&t2, NULL, threadfunc, (void*)&count2);

	pthread_mutex_lock(&mutex);
	int time = 0;
	while(time < 2)
	{
		pthread_cond_wait(&cond, &mutex);
		mailbox = 0;
		pthread_cond_signal(&cond);
		time ++;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_cond_destroy(&cond);
	printf("total votes is %d\n", total);

	return 0;	
}

