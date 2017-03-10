
#include "stdafx.h"

#include <stdlib.h>
#include <assert.h>

#include "./queue.h"

/*���г�ʼ��*/
pqueue_node queue_init(void)
{
    pqueue_node rear = NULL;
    rear = (pqueue_node)malloc(sizeof(queue_node));
    assert(NULL != rear);

    rear->prev = NULL;
    rear->next = NULL;

    return rear;
}

/*Ѱ�Ҷ��е��ײ�*/
pqueue_node queue_front(pqueue_node rear)
{
    pqueue_node front = NULL;
    pqueue_node current = rear;

    while (current != NULL)
    {
        front = current;
        current = current->next;
    }
    return front;
}

/*Ѱ�Ҷ��е�β��*/
pqueue_node queue_rear(pqueue_node front)
{
    pqueue_node rear = NULL;
    pqueue_node current = front;
    while (current != NULL)
    {
        rear = current;
        current = current->prev;
    }
    return rear;
}

/*���*/
pqueue_node queue_enqueue(pqueue_node front, int data)
{
    pqueue_node new_node = NULL;
    pqueue_node rear = NULL;
    new_node = (pqueue_node)malloc(sizeof(queue_node));
    assert(NULL != new_node);

    new_node->data = data;

    rear = queue_rear(front);

    new_node->next = rear;
    rear->prev = new_node;
    new_node->prev = NULL;

    printf("enqueue item  data %d\r\n",  data);

    return new_node;
}

/*����*/
int queue_dequeue(pqueue_node rear)
{
    int data = 0;

    pqueue_node front = queue_front(rear);
    pqueue_node new_front = front->prev;

    if (front == rear)
    {
        printf("queue is empty\r\n");
        return 0;
    }
    data = front->prev->data;
    new_front->next = NULL;

    free(front);
    printf("dequeue data %d\r\n", data);
    return data;
}

/*���д�ӡ*/
void queue_print(pqueue_node rear)
{
    int index = 0;
    pqueue_node current = rear;
    pqueue_node front = queue_front(rear);

    printf("----------print begin...----------\r\n");
    if (rear == front)
    {
        printf("queue is empty\r\n");
    }
    else
    {
        while (current != front)
        {
            printf("queue item %d data %d\r\n", ++index, current->data);
            current = current->next;
        }
    }
    printf("----------print end...----------\r\n");
    return;
}
void queue_test(void)
{
    int i = 0;
    int dequeue_data = 0;
    pqueue_node front = queue_init();
    pqueue_node rear = NULL;
    for (i = 1; i < 2; i++)
    {
        rear = queue_enqueue(front, i);
    }
    rear = queue_enqueue(front, 99);
    rear = queue_enqueue(front, 88);
    rear = queue_enqueue(front, 22);
    queue_print(rear);

    for (i = 1; i < 2; i++)
    {
        dequeue_data = queue_dequeue(rear);
        queue_print(rear);
    }

    /*�������֮ǰҪ�����ҵ�front*/
    front = queue_front(rear);
    rear = queue_enqueue(front, 45);
    queue_print(rear);

    return;
}
