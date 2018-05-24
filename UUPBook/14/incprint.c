#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 5

int counter = 0;

void * printcount(void*);

int main()
{
	pthread_t t;
	pthread_create(&t,NULL,printcount,NULL);
	for(int i=0;i<NUM;i++)
	{
		printf("count is %d in main thread\n",counter);
		sleep(1);
	}

	pthread_join(t,NULL);
}

void * printcount(void* m)
{
	char* cp = (char*) m;
	int i;
	for(i=0;i<NUM;i++)
	{
		counter ++;
		printf("count is %d\n",counter);
		sleep(1);
	}

	return NULL;
}

