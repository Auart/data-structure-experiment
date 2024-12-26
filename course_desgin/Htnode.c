#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 20
#define M 100
typedef int DataType;
typedef struct{
    char ch;
    DataType weight;
    int lchild, rchild, parent;
} Htnode;

typedef struct {
    char *code;
    char leaf;
    int length;
} CodeType;

void Visit(DataType data){
    printf("%d ", data);
}

void selectSort(Htnode huftree[], int end, int *s1, int *s2){
    int i;
    *s1 = *s2 = -1;
    for(i = 1; i <= end; i++){
        if (*s1 == -1 && huftree[i].parent == -1){
            *s1 = i;
            continue;
        }
        if (huftree[i].weight < huftree[*s1].weight
        && huftree[i].parent == -1){
            *s1 = i;
        }
    }
    for (i = 1; i <= end; i++){
        if (*s2 == -1 && huftree[i].parent == -1 && i != *s1){
            *s2 = i;
            continue;
        }
        if (huftree[i].weight < huftree[*s2].weight
        && huftree[i].parent == -1 && i != *s1){
            *s2 = i;
            continue;
        }
        if (i != *s1 && huftree[i].weight <= huftree[*s2].weight
        && huftree[i].parent == -1){
            *s2 = i;
        }
    }
}

void Hufcoding(Htnode huftree[], CodeType cd[], int w[], int n) {
    int i, k, s1, s2, m, f, c, sum;
    char temp[N]; // 用数组替代未初始化的指针
    m = 2 * n - 1;

    for (i = 1; i <= n; i++) {
        huftree[i].weight = w[i - 1];
        huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
        huftree[i].ch = getchar();
    }

    for (i = n + 1; i <= m; i++) {
        huftree[i].weight = -1;
        huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
    }

    for (i = 1; i <= n - 1; i++) {
        selectSort(huftree, n + i - 1, &s1, &s2);
        sum = huftree[s1].weight + huftree[s2].weight;
        huftree[n + i].weight = sum;
        huftree[s1].parent = huftree[s2].parent = n + i;
        huftree[n + i].lchild = s1;
        huftree[n + i].rchild = s2;
    }

    for (i = 1; i <= n; i++) {
        c = 0;
        for (k = i, f = huftree[i].parent; f != -1; k = f, f = huftree[f].parent) {
            if (huftree[f].lchild == k) {
                temp[c++] = '0';
            } else {
                temp[c++] = '1';
            }
        }
        cd[i].code = (char *)malloc(c + 1);
        cd[i].code[c] = '\0';
        c--;
        k = 0;
        while (c >= 0) {
            cd[i].code[k++] = temp[c--];
        }
        cd[i].leaf = huftree[i].ch;
        cd[i].length = k;
    }
}



void Hufdecode(Htnode huftree[], int n, char *encoded){
    int i = 0;
    int node = 2 * n - 1;
    printf("解答结果\n");

    while(encoded[i] != '\0'){
        if (encoded[i] == '0'){
            node = huftree[node].lchild;
        }else if(encoded[i] == '1'){
            node = huftree[node].rchild;
        }
        i++;

        if (huftree[node].lchild == -1 && huftree[node].rchild == -1){
            printf("%c", huftree[node].ch);
            node = 2 * n - 1;
        }
    }
    printf("\n");
}

void displayMenu() {
    printf("姓名：张金鑫  学号：242040286  班级：计升247\n");
    printf("请选择操作\n");
    printf("1.哈夫曼编码\n");
    printf("2.哈夫曼解码\n");
    printf("0.退出\n");
    printf("------------------------\n");
}

void huffmanEncoding() {
    Htnode huftree[M];
    CodeType cd[M];
    int w[M];
    int n, i;
    printf("------------------------\n");
    printf("请输入叶子结点的个数: \n");
    scanf("%d", &n);
    printf("请输入叶子节点的权值: \n");
    for (i = 0; i < n; i++){
        scanf("%d", &w[i]);
    }
    getchar();
    printf("请输入叶子结点的值: \n");
    Hufcoding(huftree, cd, w, n);
    printf("%-6s%-10s%-4s\n", "叶子", "叶子编码", "编码长度");
    for (i = 1; i <= n; i++){
        printf("%-6c%-10s%-4d\n", cd[i].leaf, cd[i].code, cd[i].length);
    }
    printf("------------------------\n");
}

void huffmanDecoding(){
    Htnode huftree[M];
    CodeType cd[M];
    int w[M];
    int n, i;
    char encoded[N];

    printf("请输入叶子结点的个数：\n");
    scanf("%d", &n);
    printf("请输入叶子结点的权值：\n");
    for (i = 0; i < n; i++){
        scanf("%d", &w[i]);
    }
    getchar();
    printf("请输入叶子结点的值：\n");
    Hufcoding(huftree, cd, w, n);
    printf("请输入需要解码的哈夫曼编码: \n");
    scanf("%s", encoded);
    Hufdecode(huftree, n, encoded);
}

int main() {
    int choice;
    while (1) {
        displayMenu();
        printf("请输入您的选择: \n");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                huffmanEncoding();
                break;
            case 2:
                huffmanDecoding();
                break;
            case 0:
                printf("退出程序\n");
                return 0;
            default:
                printf("无效输入，请重新选择\n");
        }
    }
    return 0;
}