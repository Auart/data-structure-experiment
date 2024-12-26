#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxsize 100

typedef struct {
    char name[30];
    char key[5];
    double phoneNumber;
} DataType;

typedef struct {
    DataType elem[maxsize];
    int length;
} HashTable;

typedef HashTable* PHashTable;

// 初始化哈希表
PHashTable InitHashTable() {
    PHashTable ht = (PHashTable)malloc(sizeof(HashTable));
    ht->length = 0;
    for (int i = 0; i < maxsize; i++) {
        ht->elem[i].phoneNumber = -1; // 用 -1 表示空
        strcpy(ht->elem[i].name, "null");
        strcpy(ht->elem[i].key, "null");
    }
    return ht;
}

// 哈希函数
int HashFun(char *key, int m) {
    int d = 0;
    for (int i = 0; i < strlen(key); i++) {
        if (key[i] >= 'a' && key[i] <= 'z') 
            d += key[i] - 'a' + 1;
        else if (key[i] >= 'A' && key[i] <= 'Z') 
            d += key[i] - 'A' + 1;
    }
    return d % m;
}

// 插入元素
void HashInsert(HashTable *ht, DataType x) {
    int d = HashFun(x.key, maxsize);
    int start = d;
    while (ht->elem[d].phoneNumber != -1) { // 线性探测解决冲突
        d = (d + 1) % maxsize;
        if (d == start) { // 回到初始位置表示表已满
            printf("Hash table overflow!\n");
            return;
        }
    }
    ht->elem[d] = x;
    ht->length++;
}

// 查找元素
int HashSearch(HashTable *ht, char *key, int *count) {
    int d = HashFun(key, maxsize);
    int start = d;
    *count = 0;
    while (strcmp(ht->elem[d].key, "null") != 0) {
        (*count)++;
        if (strcmp(ht->elem[d].key, key) == 0)
            return d;
        d = (d + 1) % maxsize;
        if (d == start) break; // 回到初始位置，查找失败
    }
    return -1;
}

// 提取姓名首字母
void getNameCaptital(char *key, char *nameCaps) {
    char temp[30];
    strcpy(temp, key);
    char *token = strtok(temp, " ");
    int i = 0;
    while (token != NULL) {
        nameCaps[i++] = token[0];
        token = strtok(NULL, " ");
    }
    nameCaps[i] = '\0';
}

// 打印哈希表
void PrintHashTable(HashTable HT) {
    printf("Hash表为：\n");
    printf("下标\t姓名首字母\t姓名\t电话号码\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < maxsize; i++) {
        if (HT.elem[i].phoneNumber != -1) {
            printf("%d\t%s\t%s\t%.0lf\n", i, HT.elem[i].key, HT.elem[i].name, HT.elem[i].phoneNumber);
        }
    }
    printf("\n");
}

int main() {
    int n, count;
    DataType x;
    char nameCaps[5];
    PHashTable ht = InitHashTable();

    printf("输入待散列用户个数n (要求 n <= %d):\n", maxsize);
    scanf("%d", &n);
    while (n > maxsize) {
        printf("重输n值：");
        scanf("%d", &n);
    }

    printf("输入%d个用户姓名及电话号码：\n", n);
    getchar();
    for (int i = 0; i < n; i++) {
        printf("输入第%d/%d个用户姓名: ", i + 1, n);
        fgets(x.name, sizeof(x.name), stdin);
        x.name[strcspn(x.name, "\n")] = '\0';

        printf("输入第%d/%d个用户电话号码: ", i + 1, n);
        scanf("%lf", &x.phoneNumber);
        getchar();

        getNameCaptital(x.name, nameCaps);
        strcpy(x.key, nameCaps);
        HashInsert(ht, x);
    }

    PrintHashTable(*ht);

    while (1) {
        printf("输入一个待查找用户姓名拼音的首字母 (#结束查找): ");
        fgets(x.key, sizeof(x.key), stdin);
        x.key[strcspn(x.key, "\n")] = '\0';

        if (strcmp(x.key, "#") == 0) break;

        int pos = HashSearch(ht, x.key, &count);
        if (pos != -1) {
            printf("查找成功: %s 的电话号码为 %.0lf，下标值为 %d\n", ht->elem[pos].name, ht->elem[pos].phoneNumber, pos);
        } else {
            printf("查找失败！\n");
        }
        printf("比较次数为 %d！\n", count);
    }

    free(ht);
    return 0;
}
