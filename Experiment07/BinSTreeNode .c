#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXS 30

typedef struct BinSTreeNode *BinStree;
struct BinSTreeNode {
    char Data[MAXS + 1];
    int cnt;
    BinStree lchild;
    BinStree rchild;
};

// 插入节点到二叉排序树的函数
BinStree Insert(BinStree T, char *Name) {
    int cmp;
    if (!T) {
        T = (BinStree)malloc(sizeof(struct BinSTreeNode));
        strcpy(T->Data, Name);
        T->cnt = 1;
        T->lchild = T->rchild = NULL;
    } else {
        cmp = strcmp(Name, T->Data);
        if (cmp < 0) {
            T->lchild = Insert(T->lchild, Name);
        } else if (cmp > 0) {
            T->rchild = Insert(T->rchild, Name);
        } else {
            T->cnt++;
        }
    }
    return T;
}

// 中序遍历二叉排序树并输出每个节点的字符串及出现频率的函数
void Output(BinStree T, int N) {
    if (!T) return;
    Output(T->lchild, N);
    printf("%s %.4f%%\n", T->Data, (double)T->cnt / (double)N * 100.0);
    Output(T->rchild, N);
}

// 释放二叉树的函数
void FreeTree(BinStree T) {
    if (!T) return;
    FreeTree(T->lchild);
    FreeTree(T->rchild);
    free(T);
}

int main() {
    int num, i;
    char Name[MAXS + 1];
    BinStree T = NULL;

    // 正确读取输入的整数数量
    scanf("%d", &num);
    getchar();  // 消耗换行符
    for (i = 0; i < num; i++) {
        fgets(Name, MAXS + 1, stdin);
        Name[strcspn(Name, "\n")] = '\0';
        if (strlen(Name) == 0) continue;  // 忽略空行
        T = Insert(T, Name);
    }

    Output(T, num);

    // 释放内存
    FreeTree(T);

    return 0;
}
