/*
 * Just for practice
 * reference: http://blog.chinaunix.net/uid-22663647-id-1771829.html 
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 32

#define P(x) sem_wait(&x)
#define V(x) sem_post(&x)

int in = 0;
int out = 0;

int buff[BUFFER_SIZE] = { 0 };

sem_t empty_sem;
sem_t full_sem;
pthread_mutex_t mutex;

void print()
{
    int i;
    for (i = 0; i < BUFFER_SIZE; i++)
        printf("%d ", buff[i]);
    printf("\n");
}

void *producer()
{
    while(1)
    {
        sleep(1);

        P(empty_sem);
        pthread_mutex_lock(&mutex);

        in = in % BUFFER_SIZE;
        printf("(+)produce a product. buffer: ");

        buff[in] = 1;
        print();
        in++;
        
        pthread_mutex_unlock(&mutex);
        V(full_sem);
    }
}

void *consumer()
{
    while (1)
    {
        sleep(2);
        P(full_sem);
        pthread_mutex_lock(&mutex);

        out = out % BUFFER_SIZE;
        printf("(-)consume a product. buffer: ");
        
        buff[out] = 0;
        print();
        ++out;

        pthread_mutex_unlock(&mutex);
        V(empty_sem);
    }
}

void sem_mutex_init()
{
    sem_init(&empty_sem, 0, BUFFER_SIZE);
    sem_init(&full_sem, 0, 0);

    pthread_mutex_init(&mutex, NULL);
}

int main(int argc, char** argv)
{
    pthread_t t1;
    pthread_t t2;

    sem_mutex_init();

    int ret = pthread_create(&t1, NULL, producer, NULL);
    if (ret != 0)
    {
        printf("producer creation failed!\n");
        exit(1);
    }

    ret = pthread_create(&t2, NULL, consumer, NULL);
    if (ret != 0)
    {
        printf("consumer creation failed!\n");
        exit(1);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
