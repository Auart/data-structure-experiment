#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
typedef struct BNode {
    char data;           // 存储数据
    struct BNode* lchild; // 左子树
    struct BNode* rchild; // 右子树
} BNode, *BTree;
// 计算二叉树的结点数
int CountTree(BTree t) {
    if (t == NULL) {
        return 0;
    }
    return CountTree(t->lchild) + CountTree(t->rchild) + 1;  // 左右子树结点数加1
}

// 计算二叉树的叶子结点数
int CountLeaf(BTree t) {
    if (t == NULL) {
        return 0;
    }
    if (t->lchild == NULL && t->rchild == NULL) {
        return 1;  // 是叶子结点
    }
    return CountLeaf(t->lchild) + CountLeaf(t->rchild);  // 递归计算左、右子树的叶子结点数
}

// 计算二叉树的高度
int Height(BTree t) {
    if (t == NULL) {
        return 0;
    }
    int hl = Height(t->lchild);  // 计算左子树的高度
    int hr = Height(t->rchild);  // 计算右子树的高度
    return (hl > hr) ? hl + 1 : hr + 1;  // 返回较大高度 + 1
}

// 计算每层结点数
void Levcount(BTree t, int level, int num[]) {
    if (t) {
        num[level]++;  // 当前层结点数加1
        Levcount(t->lchild, level + 1, num);  // 递归遍历左子树
        Levcount(t->rchild, level + 1, num);  // 递归遍历右子树
    }
}

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

// 中序遍历
void Inorder(BTree t) {
    if (t) {
        Inorder(t->lchild);   // 遍历左子树
        Visit(t->data);       // 访问根节点
        Inorder(t->rchild);   // 遍历右子树
    }
}

// 后序遍历
void Postorder(BTree t) {
    if (t) {
        Postorder(t->lchild); // 遍历左子树
        Postorder(t->rchild); // 遍历右子树
        Visit(t->data);       // 访问根节点
    }
}


int main() {
    BTree root;
    int num[100] = {0};  // 用于记录每层的结点数
    int treeHeight;

    printf("请输入先序序列（#代表空节点）: ");
    root = CreateBinTree();  // 创建二叉树

    printf("\n先序遍历结果: ");
    Preorder(root);  // 输出先序遍历的结果
    printf("\n");

    printf("中序遍历: ");
    Inorder(root);
    printf("\n");

    printf("后序遍历: ");
    Postorder(root);
    printf("\n");

    printf("\n二叉树的结点数: %d\n", CountTree(root));
    printf("二叉树的叶子结点数: %d\n", CountLeaf(root));

    treeHeight = Height(root);
    printf("二叉树的高度: %d\n", treeHeight);

    Levcount(root, 0, num);
    printf("每层结点数: ");
    for (int i = 0; i < treeHeight; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");


    return 0;
}
