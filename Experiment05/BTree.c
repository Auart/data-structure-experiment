#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
typedef struct BNode {
    char data;           // 存储数据
    struct BNode* lchild; // 左子树
    struct BNode* rchild; // 右子树
} BNode, *BTree;

// 根据先序序列创建二叉树
BTree CreateBinTree() {
    char ch;
    BTree t;
    ch = getchar();  // 获取字符输入

    if (ch == '#') {  // 如果输入是'#'，则该结点为空
        t = NULL;
    } else {
        t = (BTree)malloc(sizeof(BNode));  // 创建结点空间
        t->data = ch;  // 赋值给当前结点
        t->lchild = CreateBinTree();  // 递归创建左子树
        t->rchild = CreateBinTree();  // 递归创建右子树
    }

    return t;
}

// 访问结点数据的函数
void Visit(char data) {
    printf("%c ", data);  // 打印结点的数据
}

// 先序遍历
void Preorder(BTree t) {
    if (t) {
        Visit(t->data);       // 访问根节点
        Preorder(t->lchild);  // 遍历左子树
        Preorder(t->rchild);  // 遍历右子树
    }
}

int main() {
    BTree root;
    printf("请输入先序序列（#代表空节点）: ");
    root = CreateBinTree();  // 创建二叉树

    printf("\n先序遍历结果: ");
    Preorder(root);  // 输出先序遍历的结果
    printf("\n");

    return 0;
}
