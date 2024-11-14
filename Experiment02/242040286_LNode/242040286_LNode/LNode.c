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

// 尾插法
LinkList tailInsertList(LinkList head, int item)
{
    LinkList nodeList = malloc(sizeof(LNode));
    if (!nodeList)
        return NULL;
    nodeList->data = item;
    nodeList->next = NULL;
    if (head == NULL)
    {
        return nodeList;
    }

    LinkList current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = nodeList;
    return head;
}

// 任意插入
LinkList insertNode(LinkList head, int position, int item)
{
    LinkList nodeList = malloc(sizeof(LNode));
    LinkList->data = item;
    if (position == 0)
    {
        nodeList->next = head;
        return nodeList;
    }

    LinkList current = head;
    for (int i = 0; i < position - 1 && current != NULL; i++)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("插入位置超出链表长度\n");
        free(nodeList);
        return head;
    }
    nodeList->next = current->next;
    current->next = nodeList;
    return head;
}



int main()
{
}
