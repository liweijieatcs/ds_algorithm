
#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queue_node_tag
{
    int data;
    struct queue_node_tag *prev;
    struct queue_node_tag *next;
} queue_node;

typedef queue_node* pqueue_node;

void queue_test(void);

#endif

