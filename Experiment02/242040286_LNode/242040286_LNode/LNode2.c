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
// 打印
void printList(ListList head) {
    LNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
// 并集
ListList unionSet(ListList list1, ListList list2) {
    ListList result = NULL;
    LNode* p1 = list1;
    LNode* p2 = list2;
    LNode* last = NULL;

    while (p1 != NULL && p2 != NULL) {
        int value;
        if (p1->data < p2->data) {
            value = p1->data;
            p1 = p1->next;
        } else if (p1->data > p2->data) {
            value = p2->data;
            p2 = p2->next;
        } else {
            value = p1->data;
            p1 = p1->next;
            p2 = p2->next;
        }
        LNode* newNode = createNode(value);
        if (last == NULL) result = newNode;
        else last->next = newNode;
        last = newNode;
    }

    while (p1 != NULL) {
        LNode* newNode = createNode(p1->data);
        if (last == NULL) result = newNode;
        else last->next = newNode;
        last = newNode;
        p1 = p1->next;
    }

    while (p2 != NULL) {
        LNode* newNode = createNode(p2->data);
        if (last == NULL) result = newNode;
        else last->next = newNode;
        last = newNode;
        p2 = p2->next;
    }
    
    return result;
}
// 交集
ListList intersectionSet(ListList list1, ListList list2) {
    ListList result = NULL;
    LNode* last = NULL;
    
    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            list1 = list1->next;
        } else if (list1->data > list2->data) {
            list2 = list2->next;
        } else {
            LNode* newNode = createNode(list1->data);
            if (last == NULL) result = newNode;
            else last->next = newNode;
            last = newNode;
            list1 = list1->next;
            list2 = list2->next;
        }
    }
    return result;
}
// 差集
ListList differenceSet(ListList list1, ListList list2) {
    ListList result = NULL;
    LNode* last = NULL;

    while (list1 != NULL) {
        while (list2 != NULL && list2->data < list1->data) {
            list2 = list2->next;
        }
        
        if (list2 == NULL || list1->data < list2->data) {
            LNode* newNode = createNode(list1->data);
            if (last == NULL) result = newNode;
            else last->next = newNode;
            last = newNode;
        }
        list1 = list1->next;
    }
    return result;
}

