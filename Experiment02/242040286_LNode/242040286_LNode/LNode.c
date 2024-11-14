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

// 任意位置插入
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
// 删除
LinkList removeNode(LinkList head, int position)
{
    if (head == NULL)
    {
        printf("链表为空\n");
        return head;
    }
    if (position == 0)
    {
        LinkList temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    LinkList current = head;
    for (int i = 0; i < position - 1 && current != NULL; i++)
    {
        current = current->next;
    }
    if (current == NULL || current->next == NULL)
    {
        printf("删除位置超出链表长度\n");
        return head;
    }
    LinkList temp = current->next;
    current->next = current->next->next;
    free(temp);
    return head;
}
// 查找
LinkList findNode(LinkList head, int item)
{
    LinkList current = head;
    while (current != NULL)
    {
        if (current->data == item)
        {
            return current;
        }
        current = current->next;
    }
    printf("未找到该元素\n");
    return NULL;
}

// 逆置
LinkList reverseList(LinkList head)
{
    LinkList previous = NULL, current = head, next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}
// 打印
void printList(LinkList head)
{
    LinkList current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void main()
{
    LinkList head = NULL;
    //头插法
    head = headInsertList(head,3);
    head = headInsertList(head,1);
    head = headInsertList(head,1);
    printf("头插法：");
    printList(head);

    //尾插法
    head = tailInsertList(head,2);
    head = tailInsertList(head,4);
    printf("尾插法：");
    printList(head);

    //任意位置插入
    head = insertNode(head, 1, 0);
    printf("任意位置插入：");
    printList(head);

    // 删除
    head = removeNode(head, 1);
    printf("删除位置为1的元素：");
    printList(head);
    
    //查找
    LinkList node = findNode(head, 1);
    if (node!= NULL)
        printf("找到元素：%d\n", node->data);
    else
        printf("未找到元素\n");

    //逆置
    head = reverseList(head);
    printf("逆置：");
    printList(head);
    
}
