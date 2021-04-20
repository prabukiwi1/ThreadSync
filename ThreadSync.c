#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
int c=0;
pthread_t t1,t2;
sem_t mutex;
FILE *ptr;
char sentence[1000];
void *start()
{
	sem_wait(&mutex);
	ptr=fopen("ac.txt","w");
	printf("Enter the contents into the file\n");
	fgets(sentence,sizeof(sentence),stdin);
	fprintf(ptr,"%s",sentence);
	fclose(ptr);
	sleep(6);
	c++;
	printf("Thread %d is exiting..\n",c);
	sem_post(&mutex);
}
void main()
{
	sem_init(&mutex,0,1);
	pthread_create(&t1,NULL,start,NULL);
	pthread_create(&t2,NULL,start,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
