
#include "stdafx.h"

#include <stdlib.h>
#include "circular_sll.h"

/*双链表初始化*/
pcircular_sll_node circular_sll_init(void)
{
    pcircular_sll_node head = NULL;
    if ((head = (pcircular_sll_node)malloc(sizeof(circular_sll_node))) == NULL)
    {
        printf("malloc error!\r\n");
        return NULL;
    }

    head->pnext = head;
    printf("init list head add is %p\r\n", head);

    return head;
}

/*找到双链表的尾部*/
pcircular_sll_node circular_sll_find_tail(pcircular_sll_node head)
{
    pcircular_sll_node current = head->pnext;
    pcircular_sll_node tail = head;

    while (current != head)
    {
        tail = current;
        current = current->pnext;
    }

    return tail;
}

/*在双链表的尾部增加节点*/
pcircular_sll_node circular_sll_append(pcircular_sll_node head, int data)
{
    pcircular_sll_node node = NULL;
    pcircular_sll_node tail = head;

    if (NULL == head)
    {
        head = circular_sll_init();
    }

    if ((node = (pcircular_sll_node)malloc(sizeof(circular_sll_node))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    tail = circular_sll_find_tail(head);

    node->data = data;
    node->pnext = head;

    tail->pnext = node;

    return head;
}

/*在双链表中通过节点为止找到节点指针*/
pcircular_sll_node circular_sll_find_node_by_pos(pcircular_sll_node head, int pos)
{
    int node_index = 1;
    pcircular_sll_node current = head->pnext;
    pcircular_sll_node pos_node = head;

    while (current != head)
    {
        if (node_index == pos)
        {
            pos_node = current;
            break;
        }
        node_index++;
        current = current->pnext;
    }

    return current;
}

/*计算双链表的长度*/
int circular_sll_length(pcircular_sll_node head)
{
    int node_index = 0;
    pcircular_sll_node current = head->pnext;
    while (current != head)
    {
        node_index++;
        current = current->pnext;
    }

    return node_index;
}

/*在双链表的pos位置后插入新的节点*/
pcircular_sll_node circular_sll_insert_by_pos(pcircular_sll_node head, int pos, int data)
{
    int length = circular_sll_length(head);
    pcircular_sll_node pos_node = NULL;
    pcircular_sll_node new_node = NULL;

    if (pos >= length)
    {
        printf("insert %d after node %d\r\n", data, length);
        circular_sll_append(head, data);
    }
    else
    {
        if (0 == pos)
        {
            printf("insert %d after head\r\n", data);
        }
        else
        {
            printf("insert %d after node %d\r\n", data, pos);
        }

        pos_node = circular_sll_find_node_by_pos(head, pos);

        if ((new_node = (pcircular_sll_node)malloc(sizeof(circular_sll_node))) == NULL)
        {
            printf("malloc error\r\n");
            return NULL;
        }
        new_node->data = data;

        new_node->pnext = pos_node->pnext;
        pos_node->pnext = new_node;
    }

    return head;
}

/*通过位置删除双链表中的节点*/
pcircular_sll_node circular_sll_delete_by_pos(pcircular_sll_node head, int pos)
{
    int node_index = 0;
    int length = circular_sll_length(head);
    pcircular_sll_node current = head->pnext;
    pcircular_sll_node prev = head;

    if (pos > length)
    {
        printf("pos is out of range list pos:%d, list_length:%d\r\n", pos, length);
        return head;
    }

    while (current != head)
    {
        if (node_index == pos)
        {
            break;
        }
        node_index++;
        prev = current;
        current = current->pnext;
    }

    prev->pnext = current->pnext;
    printf("delete %d after node %d\r\n", current->data, pos);
    free(current);

    return head;
}

/*打印双链表*/
void circular_sll_print(pcircular_sll_node head)
{
    int node_index = 1;
    pcircular_sll_node current = head->pnext;

    printf("----------print begin...----------\r\n");
    while (current != head)
    {
        printf("circular_sll node %d, data %d\r\n", node_index, current->data);
        node_index++;
        current = current->pnext;
    }
    printf("----------print end...------------\r\n");

    return;
}

/*双链表的销毁*/
void circular_sll_destory(pcircular_sll_node head)
{
    int node_index = 1;
    pcircular_sll_node current = head->pnext;
    pcircular_sll_node next = head;

    while (current != head)
    {
        printf("free circular_sll node %d, data %d\r\n", node_index++, current->data);
        next = current->pnext;
        free(current);
        current = next;
    }
    printf("free circular_sll node %d, free head\r\n", node_index++);
    free(head);

    return;
}

void circular_sll_test(void)
{
    int i = 0;
    pcircular_sll_node head = NULL;

    head = circular_sll_init();

    for (i = 0; i < 5; i++)
    {
        circular_sll_append(head, i);
    }
    circular_sll_print(head);

    circular_sll_insert_by_pos(head, 3, 89);
    circular_sll_print(head);

    circular_sll_insert_by_pos(head, 99, 89);
    circular_sll_print(head);

    circular_sll_insert_by_pos(head, 0, 100);
    circular_sll_print(head);

    circular_sll_delete_by_pos(head, 2);
    circular_sll_print(head);

    circular_sll_delete_by_pos(head, 0);
    circular_sll_print(head);

    circular_sll_delete_by_pos(head, 5);
    circular_sll_print(head);

    circular_sll_delete_by_pos(head, 100);
    circular_sll_print(head);

    circular_sll_destory(head);

    return;
}

