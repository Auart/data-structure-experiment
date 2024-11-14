#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct LNode
{
    int data;           // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;

// 头插法
LinkList headInsertList(LinkList head, int item)
{
    LinkList nodeList = malloc(sizeof(LNode));
    if (!nodeList)
        return NULL;
    nodeList->data = item;
    nodeList->head;
    return nodeList;
}

//尾插法
LinkList tailInsertList(LinkList head, int item){
    LinkList nodeList = malloc(sizeof(LNode));
    if (!nodeList)
        return NULL;
    nodeList->data = item;
    nodeList->next = NULL;
    if(head == NULL){
        return nodeList;
    } 

    LinkList current = head;
    while(current->next!=NULL){
        current = current->next;
    }

    current->next = nodeList;
    return head;
}


int main(){

}

