
#ifndef _SINGLY_LINKED_LIST_
#define _SINGLY_LINKED_LIST_

typedef struct sll_node_tag
{
    int data;
    struct sll_node_tag* pnext;
} sll_node;
typedef sll_node* psll_node;

void sll_test(void);

#endif
