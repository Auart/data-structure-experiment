#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;

// 节点类型定义
typedef enum { ATOM, LIST } NodeType;

// 广义表节点定义
typedef struct GLNode {
    NodeType type;
    union {
        ElementType atom;            // 原子节点
        struct GLNode *subList;      // 子表节点
    };
    struct GLNode *next;             // 指向下一个节点
} GLNode, *GList;

// 创建广义表
GList createGList(char *str, int *pos) {
    if (str[*pos] == '\0') return NULL;

    GList head = NULL, tail = NULL;
    while (str[*pos] != '\0' && str[*pos] != ')') {
        if (str[*pos] == '(') {
            (*pos)++;
            GList newNode = (GList)malloc(sizeof(GLNode));
            newNode->type = LIST;
            newNode->subList = createGList(str, pos);
            newNode->next = NULL;

            if (head == NULL)
                head = tail = newNode;
            else {
                tail->next = newNode;
                tail = newNode;
            }
        } else if (str[*pos] != ',' && str[*pos] != ' ') {
            GList newNode = (GList)malloc(sizeof(GLNode));
            newNode->type = ATOM;
            newNode->atom = str[*pos];
            newNode->next = NULL;

            if (head == NULL)
                head = tail = newNode;
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        (*pos)++;
    }

    if (str[*pos] == ')') (*pos)++; // 跳过右括号
    return head;
}

// 计算广义表深度
int calculateDepth(GList glist) {
    if (glist == NULL) return 1;

    int maxDepth = 0;
    for (GList p = glist; p != NULL; p = p->next) {
        if (p->type == LIST) {
            int subDepth = calculateDepth(p->subList);
            if (subDepth > maxDepth)
                maxDepth = subDepth;
        }
    }
    return maxDepth + 1;
}

// 打印广义表
void printGList(GList glist) {
    if (glist == NULL) return;

    printf("(");
    for (GList p = glist; p != NULL; p = p->next) {
        if (p->type == ATOM)
            printf("%c", p->atom);
        else
            printGList(p->subList);
        if (p->next != NULL)
            printf(",");
    }
    printf(")");
}

int main() {
    char input[] = "(a,(b,c),(e,f,(g)))";
    int pos = 0;

    printf("输入的广义表：%s\n", input);

    // 创建广义表
    GList glist = createGList(input, &pos);

    // 打印广义表
    printf("广义表的结构：");
    printGList(glist);
    printf("\n");

    // 计算深度
    int depth = calculateDepth(glist);
    printf("广义表的深度：%d\n", depth);

    return 0;
}
