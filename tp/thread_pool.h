#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "queue.h"
#include <pthread.h>

struct thread_pool {
    // size of thread pool: thread number
    unsigned int pool_size;
    // threads
    pthread_t *threads;
    queue_t tasks;
    pthread_mutex_t lock;
    pthread_cond_t task_ready;
};

typedef struct thread_pool* thread_pool_t;

extern int thread_pool_create(unsigned int size, thread_pool_t *pool);

void thread_pool_add_task(thread_pool_t pool, void* (*routine)(void *args), void *args);

void thread_pool_destroy(thread_pool_t pool);

#endif
