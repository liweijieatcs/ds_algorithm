#include "stdafx.h"

#include <stdlib.h>
#include "circular_dll.h"

/*Ë«Á´±í³õÊ¼»¯*/
pcircular_dll_node circular_dll_init(void)
{
    pcircular_dll_node head = NULL;
    if ((head = (pcircular_dll_node)malloc(sizeof(pcircular_dll_node))) == NULL)
    {
        printf("malloc error!\r\n");
        return NULL;
    }

    head->pnext = head;
    head->pprev = head;
    printf("init list head add is %p\r\n", head);

    return head;
}

pcircular_dll_node circular_dll_append(pcircular_dll_node head, int data)
{
    pcircular_dll_node tail = head->pprev;
    pcircular_dll_node new_node = NULL;

    if((new_node = (pcircular_dll_node)malloc(sizeof(circular_dll_node))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    new_node->data = data;

    tail->pnext = new_node;
    new_node->pprev = tail;

    new_node->pnext = head;
    head->pprev = new_node;

    return head;
}

int circular_dll_length(pcircular_dll_node head)
{
    int node_index = 0;
    pcircular_dll_node current = head->pnext;
    while (current != head)
    {
        node_index++;
        current = current->pnext;
    }
    return node_index;
}

void circular_dll_print_forwards(pcircular_dll_node head)
{
    int node_index = 1;
    pcircular_dll_node current = head->pnext;

    printf("----------circular dll forwards print begin...----------\r\n");
    while (current != head)
    {
        printf("circular_dll node %d data %d\r\n", node_index++, current->data);
        current = current->pnext;
    }
    printf("----------circular dll forwards print end...------------\r\n");

    return;
}

void circular_dll_print_backwards(pcircular_dll_node head)
{
    int node_index = circular_dll_length(head) - 1;
    pcircular_dll_node current = head->pprev;

    printf("----------circular dll backwards print begin...----------\r\n");
    while (current != head)
    {
        printf("circular_dll node %d data %d\r\n", node_index--, current->data);
        current = current->pprev;
    }
    printf("----------circular dll backwards print end...------------\r\n");

    return;
}

pcircular_dll_node circular_dll_insert_by_pos(pcircular_dll_node head, int pos, int data)
{
    int node_index = 1;
    pcircular_dll_node current = head->pnext;
    pcircular_dll_node new_node = NULL;

    while (current != head)
    {
        if (node_index == pos)
        {
            printf("insert %d after node %d\r\n", data, pos);
            break;
        }
        else if (pos >= circular_dll_length(head))
        {
            printf("insert %d after tail\r\n", data);
            current = head->pprev;
            break;
        }
        node_index++;
        current = current->pnext;
    }

    if ((new_node = (pcircular_dll_node)malloc(sizeof(circular_dll_node))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }

    new_node->data = data;

    new_node->pnext = current->pnext;
    current->pnext->pprev = new_node;

    current->pnext = new_node;
    new_node->pprev = current;

    return head;
}

pcircular_dll_node circular_dll_delete_by_pos(pcircular_dll_node head, int pos)
{
    int node_index = 1;
    pcircular_dll_node current = head->pnext;
    pcircular_dll_node prev = head;
    pcircular_dll_node new_node = NULL;

    if (pos > circular_dll_length(head))
    {
        printf("pos is out of range list pos:%d, list_length:%d\r\n", pos, circular_dll_length(head));
        return head;
    }

    if (pos == 0)
    {
        printf("do not remove head\r\n");
        return head;
    }

    while (current != head)
    {
        if (node_index == pos)
        {
            break;
        }
        node_index++;
        current = current->pnext;
    }

    prev = current->pprev;

    prev->pnext = current->pnext;
    current->pnext->pprev = prev;

    printf("delete pos %d node %d,\r\n", pos, current->data);
    free(current);

    return head;
}

void circular_dll_test(void)
{
    int i = 0;
    pcircular_dll_node head = circular_dll_init();

    for (i = 0; i < 5; i++)
    {
        head = circular_dll_append(head, i);
    }
    circular_dll_print_forwards(head);

    head = circular_dll_insert_by_pos(head, 0, 89);
    circular_dll_print_forwards(head);

    head = circular_dll_insert_by_pos(head, 99, 100);
    circular_dll_print_forwards(head);
    circular_dll_print_backwards(head);

    head = circular_dll_delete_by_pos(head, 0);
    circular_dll_print_forwards(head);

    head = circular_dll_delete_by_pos(head, 1);
    circular_dll_print_forwards(head);

    head = circular_dll_delete_by_pos(head, 9);
    circular_dll_print_forwards(head);

    return;
}

