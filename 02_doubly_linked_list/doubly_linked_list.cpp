
#include "stdafx.h"

#include <stdlib.h>
#include <assert.h>
#include "doubly_linked_list.h"

/*初始化双链表*/
pdll_node dll_init(void)
{
    pdll_node head = NULL;
    head = (pdll_node)malloc(sizeof(dll_node));
    assert(NULL != head);

    head->pprev = NULL;
    head->pnext = NULL;

    return head;
}

/*寻找双链表的尾节点*/
pdll_node dll_find_tail(pdll_node head)
{
    pdll_node tail = NULL;
    pdll_node current = head;
    while (current != NULL)
    {
        tail = current;
        current = current->pnext;
    }
    return tail;
}

/*寻找双链表的头节点*/
pdll_node dll_find_head(pdll_node tail)
{
    pdll_node head = NULL;
    pdll_node current = tail;
    while (current != NULL)
    {
        head = current;
        current = current->pprev;
    }
    return head;
}

/*在双链表的尾部增加节点*/
pdll_node dll_append(pdll_node head, int data)
{
    pdll_node new_node = NULL;
    pdll_node tail = NULL;
    new_node = (pdll_node)malloc(sizeof(dll_node));
    assert(NULL != head);

    tail = dll_find_tail(head);

    new_node->data = data;
    new_node->pnext = NULL;

    tail->pnext = new_node;
    new_node->pprev = tail;

    return head;
}

/*从头部到尾部顺序打印元素*/
void dll_print_forwards(pdll_node head)
{
    int index = 0;
    pdll_node current = head;

    printf("----------forwards print begin...----------\r\n");
    while (current != NULL)
    {
        if (current->pprev == NULL)
        {
            printf("list head, add is %p\r\n", current);
            current = current->pnext;
            continue;
        }
        printf("list item %2d data is %2d, add is %p\r\n", ++index, current->data, current);
        current = current->pnext;
    }
    printf("----------forwards print end...------------\r\n");

    return;
}

/*从尾部到头部逆序打印元素*/
void dll_print_backwards(pdll_node tail)
{
    int index = 0;
    pdll_node current = tail;

    printf("----------backwards print begin...----------\r\n");
    while (current != NULL)
    {
        if (current->pprev == NULL)
        {
            printf("list head, add is %p\r\n", current);
            break;
        }
        printf("list item %2d data is %2d, add is %p\r\n", ++index, current->data, current);
        current = current->pprev;
    }
    printf("----------backwards print end...------------\r\n");

    return;
}

/*销毁双链表*/
void dll_destory(pdll_node head)
{
    pdll_node current = NULL;

    printf("----------begin destory dll...----------\r\n");

    while (head != NULL)
    {
        if (head->pprev == NULL)
        {
            printf("free head node add %p\r\n", head);
        }
        else
        {
            printf("free node add %p, data is %2d\r\n", head, head->data);
        }
        current = head->pnext;
        free(head);
        head = current;
    }
    printf("----------end destory dll...------------\r\n");
    return;
}

/*计算链表的长度，包括头结点在内*/
int dll_length(pdll_node head)
{
    int length = 0;
    pdll_node current = head;

    while (current != NULL)
    {
        current = current->pnext;
        length++;
    }

    return length;
}

/*在双链表中通过指定位置删除节点*/
pdll_node dll_delete_by_pos(pdll_node head, int pos)
{
    pdll_node current = head;
    int item_index = 0;
    int list_length = dll_length(head);/*包括头结点*/

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
            if (pos == list_length)
            {
                current->pprev->pnext = NULL;
            }
            else
            {
                current->pprev->pnext = current->pnext;
                current->pnext->pprev = current->pprev;
            }
            printf("delete item %d, data is %d\r\n", pos, current->data);
            printf("free node add %p, data is %2d\r\n", current, current->data);
            free(current);
            break;
        }
        current = current->pnext;
    }
    return head;
}

/*在双链表中通过指定位置增加节点*/
pdll_node dll_insert_by_pos(pdll_node head, int pos, int data)
{
    pdll_node current = head;
    pdll_node tail = NULL;
    pdll_node new_node = NULL;
    int item_index = 0;
    int list_length = dll_length(head);

    if ((new_node = (pdll_node)malloc(sizeof(dll_node))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    new_node->data = data;

    if ((pos + 1) >= list_length)
    {
        tail = dll_find_tail(head);

        new_node->pnext = NULL;
        new_node->pprev = tail;
        tail->pnext = new_node;

        printf("add new node after tail(item %d), data is %d\r\n", list_length, data);
        return head;
    }

    while (current != NULL)
    {
        if (item_index == pos)
        {
            new_node->pnext = current->pnext;
            current->pnext->pprev = new_node;

            current->pnext = new_node;
            new_node->pprev = current;

            printf("add new node after item %d, data is %d\r\n", pos, data);
            break;
        }
        item_index++;
        current = current->pnext;
    }

    return head;
}

/*按照位置返回链表中的值*/
int dll_find_value_by_pos(pdll_node head, int pos)
{
    int data = 0;
    int item_index = 0;
    int list_length = dll_length(head);
    pdll_node tail = dll_find_tail(head);
    pdll_node current = head;

    if (pos > list_length)
    {
        printf("pos is out of range list pos:%d, list_length: %d (include head)\r\n", pos, list_length);
        return data;
    }

    while (current != NULL)
    {
        if (pos == 0)
        {
            printf("dll head\r\n");
            break;
        }
        if (item_index == pos)
        {
            data = current->data;
            printf("dll pos %d data %2d \r\n", pos, data);
            break;
        }
        item_index++;
        current = current->pnext;
    }
    return data;
}

/*双链表测试代码*/
void dll_test(void)
{
    int i = 0;
    int data = 0;
    pdll_node head = dll_init();
    pdll_node tail = NULL;

    for (i = 6; i < 10; i++)
    {
        head = dll_append(head, i);
    }
    dll_print_forwards(head);

    tail = dll_find_tail(head);
    dll_print_backwards(tail);

    head = dll_find_head(tail);
    dll_print_forwards(head);

    head = dll_delete_by_pos(head, 2);
    dll_print_forwards(head);

    head = dll_delete_by_pos(head, 4);
    dll_print_forwards(head);

    head = dll_insert_by_pos(head, 5, 90);
    dll_print_forwards(head);

    head = dll_insert_by_pos(head, 4, 23);
    dll_print_forwards(head);

    head = dll_insert_by_pos(head, 1, 56);
    dll_print_forwards(head);

    tail = dll_find_tail(head);
    dll_print_backwards(tail);

    head = dll_find_head(tail);
    dll_print_forwards(head);

    for (i = 0; i < 8; i++)
    {
        data = dll_find_value_by_pos(head, i);
    }

    dll_destory(head);
}
