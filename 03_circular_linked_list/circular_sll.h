
#ifndef _CIRCULAR_SLL_
#define _CIRCULAR_SLL_

typedef struct circular_sll_node_tag
{
    int data;
    struct circular_sll_node_tag *pnext;
} circular_sll_node;
typedef circular_sll_node* pcircular_sll_node;

void circular_sll_test(void);

#endif
