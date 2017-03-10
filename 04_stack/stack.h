
#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack_tag
{
    int data;
    int size;
    struct stack_tag* pnext;
} stack;

typedef stack* pstack;

void stack_test(void);

#endif
