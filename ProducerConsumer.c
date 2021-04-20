#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t empty,full;
pthread_t tidp[100],tidc[100];
int buffer[100];
int c;
void init()
{
sem_init(&empty,0,100);
sem_init(&full,0,0);
c=0;
}
void insert(int item)
{
buffer[++c]=item;
}
int take()
{
return(buffer[c--]);
}
void *producer()
{
int item;
item=rand()%30;
sem_wait(&empty);
printf("Produced data=%d\n",item);
insert(item);
sem_post(&full);
}
void *consumer()
{
int item;
sem_wait(&full);
item=take();
printf("Consumed data=%d\n",item);
sem_post(&empty);
}

void main()
{
init();
int n1,n2,i;
printf("Enter the number of items to be produced\n");
scanf("%d",&n1);
printf("Enter the number of items to be consumed\n");
scanf("%d",&n2);
for(i=0;i<n1;i++)
pthread_create(&tidp[i],NULL,producer,NULL);
for(i=0;i<n2;i++)
pthread_create(&tidc[i],NULL,consumer,NULL);
for(i=0;i<n1;i++)
pthread_join(tidp[i],NULL);
for(i=0;i<n2;i++)
pthread_join(tidc[i],NULL);
sleep(1);
exit(0);
}
