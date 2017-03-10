
#ifndef _CIRCULAR_DLL_
#define _CIRCULAR_DLL_

typedef struct circular_dll_node_tag
{
    int data;
    struct circular_dll_node_tag *pprev;
    struct circular_dll_node_tag *pnext;
} circular_dll_node;
typedef circular_dll_node* pcircular_dll_node;

void circular_dll_test(void);

#endif

