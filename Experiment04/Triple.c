#include <stdio.h>
#define MAXSIZE 100

typedef int DataType;

typedef struct {
    int i, j; 
    DataType v; 
} triple;

typedef struct {
    triple data[MAXSIZE];
    int rows, cols, nums; 
} tripletable;

// 生成稀疏矩阵三元组
void createTriplet(tripletable *t, int rows, int cols, int nums, triple elements[]) {
    t->rows = rows;
    t->cols = cols;
    t->nums = nums;
    for (int k = 0; k < nums; k++) {
        t->data[k] = elements[k];
    }
}

// 转置稀疏矩阵
void transposeTriplet(tripletable *t, tripletable *result) {
    result->rows = t->cols;
    result->cols = t->rows;
    result->nums = t->nums;

    int count[MAXSIZE] = {0};
    int position[MAXSIZE] = {0};

    for (int k = 0; k < t->nums; k++) {
        count[t->data[k].j]++;
    }

    position[0] = 0;
    for (int i = 1; i < t->cols; i++) {
        position[i] = position[i - 1] + count[i - 1];
    }

    for (int k = 0; k < t->nums; k++) {
        int col = t->data[k].j;
        int pos = position[col]++;
        result->data[pos].i = t->data[k].j;
        result->data[pos].j = t->data[k].i;
        result->data[pos].v = t->data[k].v;
    }
}

// 矩阵相加
void addTriplet(tripletable *a, tripletable *b, tripletable *result) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("无法相加，矩阵维度不同。\n");
        return;
    }

    result->rows = a->rows;
    result->cols = a->cols;
    result->nums = 0;

    int i = 0, j = 0;
    while (i < a->nums && j < b->nums) {
        if (a->data[i].i < b->data[j].i || 
           (a->data[i].i == b->data[j].i && a->data[i].j < b->data[j].j)) {
            result->data[result->nums++] = a->data[i++];
        } else if (a->data[i].i > b->data[j].i || 
                  (a->data[i].i == b->data[j].i && a->data[i].j > b->data[j].j)) {
            result->data[result->nums++] = b->data[j++];
        } else {
            result->data[result->nums] = a->data[i];
            result->data[result->nums++].v = a->data[i++].v + b->data[j++].v;
        }
    }

    while (i < a->nums) {
        result->data[result->nums++] = a->data[i++];
    }
    while (j < b->nums) {
        result->data[result->nums++] = b->data[j++];
    }
}

// 打印三元组表
void printTriplet(tripletable *t) {
    printf("行 列 值\n");
    for (int k = 0; k < t->nums; k++) {
        printf("%d  %d  %d\n", t->data[k].i, t->data[k].j, t->data[k].v);
    }
}

int main() {
    tripletable a, b, at, c;

    // 输入矩阵A
    triple elementsA[] = { {0, 0, 1}, {0, 2, 3}, {1,1, 1}, {2, 2, 1},{3, 2, 1},{3, 3, 1} };
    createTriplet(&a, 4, 4, 6, elementsA);

    // 输入矩阵B
    triple elementsB[] = {{0, 0, 3}, {1, 1, 4}, {2, 2, 1},{3,3,2}};
    createTriplet(&b, 4, 4, 4, elementsB);

    // 转置矩阵
    transposeTriplet(&a, &at);

    // 矩阵相加
    addTriplet(&a, &b, &c);

   
    printf("矩阵A的三元组：\n");
    printTriplet(&a);
    printf("\n矩阵A的转置三元组：\n");
    printTriplet(&at);
    printf("\n矩阵A + B的三元组：\n");
    printTriplet(&c);

    return 0;
}
