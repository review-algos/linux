/*
 * Just for practice
 * reference: https://docs.oracle.com/cd/E19455-01/806-5257/sync-31/index.html
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#define BUFFER_SIZE 32

int in = 0;
int out = 0;
int count = 0;

int buff[BUFFER_SIZE] = { 0 };

pthread_cond_t not_full;
pthread_cond_t not_empty;
pthread_mutex_t mutex;

void print()
{
    int i;
    for (i = 0; i < BUFFER_SIZE; i++)
        printf("%d ", buff[i]);
    printf("\n");
}

void cond_mutex_init()
{
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
}

void *producer()
{
    while(1)
    {
        sleep(1);

        pthread_mutex_lock(&mutex);

        //assert(count < BUFFER_SIZE);

        while (count >= BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        in = in % BUFFER_SIZE;
        printf("(+)produce a product. buffer: ");

        buff[in] = 1;
        print();
        in++;   count++;

        pthread_cond_signal(&not_empty); 

        pthread_mutex_unlock(&mutex);
    }
}

void *consumer()
{
    while (1)
    {
        sleep(2);
        pthread_mutex_lock(&mutex);

        while (count <= 0)
            pthread_cond_wait(&not_empty, &mutex);

        //assert(count > 0);

        out = out % BUFFER_SIZE;
        printf("(-)consume a product. buffer: ");
        
        buff[out] = 0;
        print();
        ++out;  count--;

        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;

    cond_mutex_init();

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
