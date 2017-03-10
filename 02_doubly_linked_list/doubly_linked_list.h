#ifndef _DOUBLY_LINKED_LIST_
#define _DOUBLY_LINKED_LIST_

typedef struct dll_node_tag
{
    int data;
    struct dll_node_tag *pprev;
    struct dll_node_tag *pnext;
} dll_node;
typedef dll_node *pdll_node;

void dll_test(void);

#endif

