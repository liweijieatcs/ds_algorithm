#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct treeNode
{
	int data;
	struct treeNode *left;
	struct treeNode *right;
}treeNode;

treeNode* FindMin(treeNode* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if(node->left)
    {
		node = FindMin(node->left);
    }
    
	return node;
}

treeNode* FindMax(treeNode* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if(node->right)
    {
        node = FindMax(node->right);
    }
	return node;
}

treeNode* Insert(treeNode* node, int data)
{
    if (node == NULL)
    {
        treeNode* root = NULL;
        root = (treeNode*)malloc(sizeof(treeNode));
        if(root == NULL)
        {
            printf("malloc error\r\n");
            return NULL;
        }
        root->data = data;
        root->left = NULL;
        root->right = NULL;

        return root;
    }

    if (data > (node->data))
    {
        /* insert right node and the node as the new right node */
        node->right = Insert(node->right, data);
    }
    else if(data < (node->data))
    {
		node->left = Insert(node->left, data);
    }
    /*else there is nothing to do as data is already in the tree*/
    return node;
}

treeNode* Delete(treeNode* node, int data)
{
    treeNode* temp = NULL;

    if (node == NULL)
    {
        printf("element nod found\r\n");
    }
    else if(data < (node->data))
    {
        node->left = Delete(node->left, data);
    }
    else if(data > (node->data))
    {
        node->right = Delete(node->right, data);
    }
    else
    {
        /* Now We can delete this node and replace with either minimum element
           in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
			temp = FindMin(node->right);
            node->data = temp->data;
            /* As we replaced it with some other node, we have to delete that node */
            node->right = Delete(node->right, temp->data);
        }
        else
        {
            /* If there is only one or zero children then we can directly
               remove it from the tree and connect its parent to its child */
            temp = node;
            if(node->left == NULL)
            {
                node = node->right;
            }
            else if(node->right == NULL)
            {
                node = node->left;
            }
            /* temp is longer required */
            free(temp);
        }
    }
    return node;
}

treeNode* Find(treeNode* node, int data)
{
    if (node == NULL)
    {
		return NULL;
    }

    if (data > node->data)
    {
        /* Search in the right sub tree. */
        return Find(node->right, data);
    }
    else if (data < node->data)
    {
        /* Search in the left sub tree. */
        return Find(node->left, data);
    }
    else
    {
        /* node is not found */
		return node;
    }
}

void PrintInorder(treeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    PrintInorder(node->left);
    printf("%d ", node->data);
    PrintInorder(node->right);
}

void PrintPreorder(treeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d ", node->data);
    PrintPreorder(node->left);
    PrintPreorder(node->right);
}

void PrintPosorder(treeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    PrintPosorder(node->left);
    PrintPosorder(node->right);
    printf("%d ", node->data);
}

void test_tree_by_linked_list(void)
{
	treeNode* root = NULL;
    //root = Insert(root, 5);
    root = Insert(root, 5);
    root = Insert(root, -1);
    root = Insert(root, 3);
    root = Insert(root, -14);
    root = Insert(root, 8);
    root = Insert(root, 10);
    root = Insert(root, 9);
    root = Insert(root, 6);
    PrintInorder(root);
	printf("\n");
	PrintPreorder(root);
	printf("\n");
	PrintPosorder(root);
    printf("\n");
	printf("delete item 5\r\n");
    root = Delete(root,5);
	PrintInorder(root);
	printf("\n");
	printf("delete item -1\r\n");
    root = Delete(root,-1);
    PrintInorder(root);
    printf("\n");
    treeNode * temp;
    temp = FindMin(root);
    printf("Minimum element is %d\n",temp->data);
    temp = FindMax(root);
    printf("Maximum element is %d\n",temp->data);
    temp = Find(root, 8);
    if(temp == NULL)
    {
            printf("Element 8 not found\n");
    }
    else
    {
            printf("Element 8 Found\n");
    }
    temp = Find(root, 2);
    if(temp == NULL)
    {
            printf("Element 2 not found\n");
    }
    else
    {
            printf("Element 6 Found\n");
    }
}
