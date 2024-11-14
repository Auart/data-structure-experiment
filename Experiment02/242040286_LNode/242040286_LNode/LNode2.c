#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;              
    struct LNode *next;    
} LNode, *ListList;

// 创建
LNode* createNode(int data) {
    LNode* newNode = malloc(sizeof(LNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

