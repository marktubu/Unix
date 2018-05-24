#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int myglobal;
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

void * thread_function(void* arg)
{
	int i,j;
	for(i=0;i<20;i++)
	{
		pthread_mutex_lock(&mymutex);
		j = myglobal;
		j=j+1;
		printf(".");
		fflush(stdout);
		sleep(1);
		myglobal = j;
		pthread_mutex_unlock(&mymutex);
	}
	return NULL;
}

int main(void)
{
	pthread_t mythread;
	int i;
	if(pthread_create(&mythread, NULL, thread_function, NULL))
	{
		printf("error creating thread");
		exit(1);
	}

	for(i=0;i<20;i++)
	{
		pthread_mutex_lock(&mymutex);
		myglobal = myglobal + 1;
		pthread_mutex_unlock(&mymutex);
		printf("o");
		fflush(stdout);
		sleep(1);
	}

	if(pthread_join(mythread, NULL))
	{
		printf("error join thread");
		exit(1);
	}
	
	printf("\n myglobal equals %d\n",myglobal);
	return 0;
}
