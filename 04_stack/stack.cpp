
#include "stdafx.h"

#include <stdlib.h>
#include "stack.h"

pstack stack_init(void)
{
    pstack top = NULL;
    if ((top = (pstack)malloc(sizeof(stack))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    top->size = 0;
    top->pnext = NULL;
    return top;
}

pstack stack_find_top(pstack stk)
{
    pstack tail = stk;
    pstack top = NULL;
    while (tail != NULL)
    {
        top = tail;
        tail = tail->pnext;
    }
    return top;
}

pstack stack_push(pstack stk, int data)
{
    pstack new_node = NULL;
    pstack top = NULL;

    if (stk->size >= 10)
    {
        printf("stack overflow, do not push size %d\r\n", stk->size);
        return stk;
    }
    else
    {
        printf("stack push data %d, size %d\r\n", data, ++(stk->size));
    }

    if ((new_node = (pstack)malloc(sizeof(stack))) == NULL)
    {
        printf("malloc error\r\n");
        return NULL;
    }
    new_node->data = data;
    new_node->pnext = NULL;

    top = stack_find_top(stk);
    top->pnext = new_node;

    return stk;
}

int stack_pop(pstack stk)
{
    pstack current = stk;
    pstack prev = stk;
    int size = 0;
    int data = 0;

    if (stk->size == 0)
    {
        printf("stack underflow, do not pop\r\n");
        return data;
    }

    while (current != NULL)
    {
        if (size == (stk->size - 1))
        {
            break;
        }
        size++;
        current = current->pnext;
    }
    data = current->pnext->data;
    printf("stack pop data %d, size %d\r\n", data, stk->size--);
    current->pnext = NULL;

    free(current->pnext);

    return data;
}

void stack_print(pstack stk)
{
    int stack_index = 0;
    pstack tail = stk->pnext;

    if (tail == NULL)
    {
        printf("stack is empty\r\n");
    }

    while (tail != NULL)
    {
        printf("stack print item %d data %d\r\n", ++stack_index, tail->data);
        tail = tail->pnext;
    }
}

void stack_test(void)
{
    int pop_data = 0;
    int stack_index = 0;
    pstack stack_head = NULL;
    stack_head = stack_init();

    for (stack_index = 1; stack_index < 20; stack_index++)
    {
        stack_push(stack_head, stack_index);
    }
    stack_print(stack_head);

    pop_data = stack_pop(stack_head);
    pop_data = stack_pop(stack_head);
    pop_data = stack_pop(stack_head);
    pop_data = stack_pop(stack_head);

    stack_print(stack_head);

    return;
}