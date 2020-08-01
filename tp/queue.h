#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
 
typedef struct queue *queue_t;
 
int queue_create(queue_t *q);
queue_t queue_create();
 
int queue_is_empty(queue_t q);
int queue_isempty(queue_t q);
 
void* queue_push(queue_t q, unsigned int bytes);
 
void* queue_pop(queue_t q);
 
void queue_destroy(queue_t q);
 
#endif	//QUEUE_H_INCLUDED
