#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct LNode {
    int data;
    struct LNode* next;
} LNode;

// 创建空节点（仅分配内存）
LNode* createEmptyNode() {
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->data = 0;
    node->next = NULL;
    return node;
}

// 初始化节点数据
LNode* initNode(int data) {
    LNode* node = createEmptyNode();
    node->data = data;
    return node;
}

// 头插法插入新节点
void insertHead(LNode** head, int data) {
    LNode* newNode = initNode(data);
    newNode->next = *head;
    *head = newNode;
}

// 尾插法插入新节点
void insertTail(LNode** head, int data) {
    LNode* newNode = initNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        LNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// 根据索引插入新节点
void insertAtIndex(LNode** head, int index, int data) {
    if (index < 0) {
        printf("无效的索引\n");
        return;
    }

    LNode* newNode = initNode(data);
    if (index == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    LNode* current = *head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("索引超出范围\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// 删除指定值的节点
void deleteByValue(LNode** head, int data) {
    LNode* current = *head;
    LNode* prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("未找到值 %d\n", data);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}

// 查找值为 data 的节点的索引
int findIndex(LNode* head, int data) {
    LNode* current = head;
    int index = 0;

    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

// 链表逆置
void reverseList(LNode** head) {
    LNode* prev = NULL;
    LNode* current = *head;
    LNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

// 打印链表中的元素
void displayList(LNode* head) {
    LNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 释放链表所占用的内存
void freeList(LNode* head) {
    LNode* current = head;
    while (current != NULL) {
        LNode* temp = current;
        current = current->next;
        free(temp);
    }
}


int main() {
    LNode* head = NULL;

    // 头插法创建链表
    insertHead(&head, 10);
    insertHead(&head, 20);
    insertHead(&head, 30);
    printf("链表（头插法创建）: ");
    displayList(head);

    // 尾插法创建链表
    insertTail(&head, 40);
    insertTail(&head, 50);
    printf("链表（尾插法创建）: ");
    displayList(head);

    // 插入节点
    insertAtIndex(&head, 2, 25);
    printf("链表（插入 25 在索引 2）: ");
    displayList(head);

    // 删除节点
    deleteByValue(&head, 10);
    printf("链表（删除值为 10 的节点）: ");
    displayList(head);

    // 查找节点
    int index = findIndex(head, 40);
    printf("查找值为 40 的节点索引: %d\n", index);

    // 逆置链表
    reverseList(&head);
    printf("链表（逆置后）: ");
    displayList(head);

    // 释放链表内存
    freeList(head);
    return 0;
}
