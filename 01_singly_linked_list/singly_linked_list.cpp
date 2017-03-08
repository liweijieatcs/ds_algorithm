
#include "stdafx.h"

#include <stdlib.h>
#include "singly_linked_list.h"

/*initialize the singly_linked_list*/
psll_node sll_init(void)
{
    psll_node head = NULL;
    if ((head = (psll_node)malloc(sizeof(sll_node))) == NULL)
    {
        printf("malloc error!\r\n");
        return NULL;
    }

    head->pnext = NULL;
    printf("init list head add is %p\r\n", head);

    return head;
}

/*find the tail of singly_linked_list*/
psll_node sll_find_tail(psll_node head)
{
    psll_node tail = head;
    psll_node current = head;
    while (current != NULL)
    {
        tail = current;
        current = current->pnext;
    }
    return tail;
}

/*add new node to the tail*/
psll_node sll_append(psll_node head, int data)
{
    psll_node new_node = NULL;
    psll_node tail = NULL;

    if ((new_node = (psll_node)malloc(sizeof(sll_node))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    new_node->data = data;
    new_node->pnext = NULL;

    /*find the list tail*/
    tail = sll_find_tail(head);

    tail->pnext = new_node;

    return head;
}

/*print the list node's value*/
void sll_print(psll_node head)
{
    int index = 0;
    psll_node current = head;

    printf("----------print begin...----------\r\n");
    while (current != NULL)
    {
        printf("list item %2d data is %2d, add is %p\r\n", ++index, current->data, current);
        current = current->pnext;
    }
    printf("----------print end...----------\r\n");
    return;
}

/*destory the list*/
void sll_destory(psll_node head)
{
    psll_node current = NULL;

    printf("\r\nbegin destory list...\r\n");

    while (head != NULL)
    {
        current = head->pnext;
        printf("free node add %p, data is %2d\r\n",head, head->data);
        free(head);
        head = current;
    }

    return;
}

/*traverse the list and count the node*/
int sll_length(psll_node head)
{
    int length = 0;
    psll_node current = head;

    while (current != NULL)
    {
        current = current->pnext;
        length++;
    }

    return length;
}

/*ͨdelete the node in the list by position*/
psll_node sll_delete_by_pos(psll_node head, int pos)
{
    psll_node prev = head;
    psll_node current = head->pnext;
    psll_node next = head;
    int item_index = 0;
    int list_length = sll_length(head);

    if ((head == NULL) || (head->pnext == NULL))
    {
        printf("list is empty!\r\n");
        return head;
    }

    if (pos == 0)
    {
        printf("do not remove head!\r\n");
        return head;
    }

    if (pos > list_length)
    {
        printf("pos is out of range list pos:%d, list_length:%d!\r\n", pos, list_length);
        return head;
    }

    while (current != NULL)
    {
        item_index++;
        if (item_index == pos)
        {
            next = current->pnext;
            prev->pnext = next;
            printf("delete item %d, data is %d\r\n", pos, current->data);
            printf("free node add %p, data is %2d\r\n",current, current->data);
            free(current);
            break;
        }
        prev = current;
        current = current->pnext;
    }
    return head;
}

psll_node sll_insert_by_pos(psll_node head, int pos, int data)
{
    psll_node current = head;
    psll_node tail = NULL;
    psll_node new_node = NULL;
    int item_index = 0;
    int list_length = sll_length(head);

    if ((new_node = (psll_node)malloc(sizeof(sll_node))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    new_node->data = data;

    if (pos >= list_length)
    {
        new_node->pnext = NULL;
        tail = sll_find_tail(head);
        tail->pnext = new_node;
        printf("add new node after tail(item %d), data is %d\r\n", list_length, data);
        return head;
    }

    while (current != NULL)
    {
        if (item_index == pos)
        {
            new_node->pnext = current->pnext;
            current->pnext = new_node;
            printf("add new node after item %d, data is %d\r\n", pos, data);
            break;
        }
        item_index++;
        current = current->pnext;
    }

    return head;
}

int sll_find_value_by_pos(psll_node head, int pos)
{
    int data = 0;
    int item_index = 0;
    int list_length = sll_length(head);
    psll_node tail = sll_find_tail(head);
    psll_node current = head;

    if (pos > list_length)
    {
        printf("pos is out of range list pos:%d, list_length:%d!\r\n", pos, list_length);
        return data;
    }

    while (current != NULL)
    {
        if (item_index == pos)
        {
            data = current->data;
            break;
        }
        item_index++;
        current = current->pnext;
    }

    return data;
}

psll_node sll_reverse_use_loop(psll_node head)
{
    psll_node prev = NULL;
    psll_node next = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    if (head->pnext == NULL)
    {
        return head;
    }

    while (head != NULL)
    {
        next = head->pnext;
        head->pnext = prev;
        prev = head;
        head = next;
    }

    return prev;
}

psll_node sll_reverse_use_recursion(psll_node head)
{
    psll_node new_head = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    if (head->pnext == NULL)
    {
        return head;
    }

    new_head = sll_reverse_use_recursion(head->pnext);
    head->pnext->pnext = head;
    head->pnext = NULL;

    return new_head;
}

void sll_test(void)
{
    int i = 0;
    int value = 0;

    psll_node head = sll_init();

    for (i = 1; i < 19; i++)
    {
        head = sll_append(head, i);
    }
    sll_print(head);

    sll_delete_by_pos(head, 3);
    sll_print(head);

    sll_insert_by_pos(head, 3, 45);
    sll_print(head);

    sll_insert_by_pos(head, 0, 98);
    sll_print(head);

    head = sll_reverse_use_loop(head);
    sll_print(head);

    head = sll_reverse_use_recursion(head);
    sll_print(head);

    sll_destory(head);

    return;
}
