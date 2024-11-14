#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新节点
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// 插入节点到递增链表
void addToSorted(Node** head, int data) {
    Node* fresh = newNode(data);
    if (*head == NULL || (*head)->data >= data) {
        fresh->next = *head;
        *head = fresh;
    } else {
        Node* curr = *head;
        while (curr->next != NULL && curr->next->data < data) {
            curr = curr->next;
        }
        fresh->next = curr->next;
        curr->next = fresh;
    }
}

// 合并两个链表
Node* combineLists(Node* list1, Node* list2) {
    Node* result = NULL;
    while (list1 != NULL) {
        addToSorted(&result, list1->data);
        list1 = list1->next;
    }
    while (list2 != NULL) {
        addToSorted(&result, list2->data);
        list2 = list2->next;
    }
    return result;
}

// 获取交集
Node* findIntersection(Node* list1, Node* list2) {
    Node* result = NULL;
    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            list1 = list1->next;
        } else if (list1->data > list2->data) {
            list2 = list2->next;
        } else {
            addToSorted(&result, list1->data);
            list1 = list1->next;
            list2 = list2->next;
        }
    }
    return result;
}

// 计算差集
Node* findDifference(Node* list1, Node* list2) {
    Node* result = NULL;
    while (list1 != NULL) {
        Node* temp = list2;
        int found = 0;
        while (temp != NULL) {
            if (list1->data == temp->data) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            addToSorted(&result, list1->data);
        }
        list1 = list1->next;
    }
    return result;
}

// 按基准值拆分
void splitByPivot(Node** head, int x) {
    Node* less = NULL;
    Node* moreOrEqual = NULL;
    Node* current = *head;

    while (current != NULL) {
        if (current->data < x) {
            addToSorted(&less, current->data);
        } else {
            addToSorted(&moreOrEqual, current->data);
        }
        current = current->next;
    }

    if (less == NULL) {
        *head = moreOrEqual;
    } else {
        *head = less;
        Node* temp = less;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = moreOrEqual;
    }
}

// 打印链表
void displayList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// 释放链表内存
void freeNodes(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* a = NULL;
    Node* b = NULL;

    // 插入数据到集合 1 和集合 2
    addToSorted(&a, 1);
    addToSorted(&a, 3);
    addToSorted(&a, 5);
    addToSorted(&a, 7);
    addToSorted(&b, 3);
    addToSorted(&b, 4);
    addToSorted(&b, 7);
    addToSorted(&b, 8);

    printf("集合 a: ");
    displayList(a);
    printf("集合 b: ");
    displayList(b);

    // 求并集
    Node* unionSet = combineLists(a, b);
    printf("并集: ");
    displayList(unionSet);

    // 求交集
    Node* intersectionSet = findIntersection(a, b);
    printf("交集: ");
    displayList(intersectionSet);

    // 求差集 (集合 a - 集合 b)
    Node* differenceSet = findDifference(a, b);
    printf("差集 (集合 1 - 集合 2): ");
    displayList(differenceSet);

    // 基准值分割集合 a
    printf("基准值分割集合 a (基准值为 5): ");
    splitByPivot(&a, 5);
    displayList(a);

    // 释放链表内存
    freeNodes(a);
    freeNodes(b);
    freeNodes(unionSet);
    freeNodes(intersectionSet);
    freeNodes(differenceSet);

    return 0;
}
