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
    nodeList->next;
    return nodeList;
}



int main(){

}

