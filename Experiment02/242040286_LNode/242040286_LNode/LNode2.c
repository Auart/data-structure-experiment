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
// 尾插法
ListList createTailInsert(ListList head, int value) {
    LNode* newNode = createNode(value);
    if (head == NULL) return newNode;
    
    LNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

