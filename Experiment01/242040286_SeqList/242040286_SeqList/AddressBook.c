#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100
#define ABTITLE "\n==手机通讯录=="
typedef struct {
    char name[20];
    char phone[15];
} AddressBook;
typedef struct {
    AddressBook ab[MAXLEN];
    int length;
} ABList, * PABList;
void clearScanf();
PABList initABList();
void displayMenuUI(const char* title, char** menuArr, int arrLength);
void displayABList(PABList PL);
void freeABList(PABList* PL);
void createAB(PABList* PL);
void addAB(PABList* PL);
void deleteAB(PABList* PL);
void findAB(PABList* PL);
void displayAB(PABList* PL);
void exitSystem(PABList* PL);
void menu();

char* menuArray[] = {
    "建立通讯录",
    "添加联系人",
    "删除联系人",
    "查找联系人",
    "显示联系人",
    "退出系统"
};

int menuArrayLength = sizeof(menuArray) / sizeof(menuArray[0]);

// 清空输入缓冲区
void clearScanf() {
    while (getchar() != '\n');
}


PABList initABList() {
    PABList PL = malloc(sizeof(ABList));
    if (PL) {
        PL->length = 0;
        printf("通讯录初始化成功!\n");
    }
    return PL;
}


void displayABList(PABList PL) {
    for (int i = 0; i < PL->length; i++) {
        printf("序号：%d 姓名：%s | 电话：%s\n", i + 1, PL->ab[i].name, PL->ab[i].phone);
    }
}


void freeABList(PABList* PL) {
    if (PL && *PL) {
        free(*PL);
        *PL = NULL;
    }
}

void displayMenuUI(const char* title, char** menuArr, int arrLength) {
    printf("%s\n", title);
    for (int i = 0; i < arrLength; i++) {
        printf("%d. %s\n", i + 1, menuArr[i]);
    }
    printf("请输入对应序号操作: ");
}


void createAB(PABList* PL) {
    if (*PL == NULL) {
        *PL = initABList();
    }
    else {
        printf("通讯录已建立\n");
    }
}
void addAB(PABList* PL) {
    if (*PL == NULL) {
        printf("请先建立通讯录\n");
        return;
    }
    AddressBook ab = { 0 };
    printf("请输入联系人的姓名和电话: ");
    scanf_s("%s %s", ab.name, (unsigned)sizeof(ab.name), ab.phone, (unsigned)sizeof(ab.phone));
    clearScanf();
    if ((*PL)->length < MAXLEN) {
        (*PL)->ab[(*PL)->length++] = ab;
        printf("添加成功\n");
    }
    else {
        printf("通讯录已满\n");
    }
}
void deleteAB(PABList* PL) {
    if (*PL == NULL) {
        printf("请先建立通讯录\n");
        return;
    }
    AddressBook ab = { 0 };
    printf("请输入删除的联系人姓名: ");
    scanf_s("%s", ab.name, (unsigned)sizeof(ab.name));
    clearScanf();
    for (int i = 0; i < (*PL)->length; i++) {
        if (strcmp((*PL)->ab[i].name, ab.name) == 0) {
            (*PL)->ab[(*PL)->length--] = ab;
            printf("删除成功！\n");
        }
        else {
            printf("未找到该联系人！\n");
        }
    }
}
void findAB(PABList* PL) {
    if (*PL == NULL) {
        printf("请先建立通讯录\n");
        return;
    }
    printf("请输入查找的联系人姓名: ");
    AddressBook cab;
    scanf_s("%s", &cab.name, (unsigned)sizeof(cab.name));
    clearScanf();
    printf("%d", (*PL)->length);
    for (int i = 0; i < (*PL)->length; i++) {
        if (strcmp((*PL)->ab[i].name, cab.name) == 0) {
            printf("查找成功！该联系人信息如下\n序号%d |  姓名：%s | 电话：%s\n", i + 1, (*PL)->ab[i].name, (*PL)->ab[i].phone);
        }
        else {
            printf("未找到该联系人！\n");
        }
    }
}

void displayAB(PABList* PL) {
    if (*PL == NULL || (*PL)->length == 0) {
        printf("通讯录为空\n");
    }
    else {
        displayList(*PL);
    }
}

void exitSystem(PABList* PL) {
    printf("系统退出\n");
    freeABList(PL);
    exit(0);
}
void (*menuFunctions[])(PABList*) = { createAB, addAB, deleteAB,findAB,displayAB,exitSystem };

void menu() {
    PABList PL = NULL;
    int c;
    do {
        displayMenuUI(ABTITLE, menuArray, menuArrayLength);
        scanf_s("%d", &c);
        clearScanf();
        (c >= 1 && c <= menuArrayLength) ? menuFunctions[c - 1](&PL) : printf("无效选择，请重试\n");
    } while (c != menuArrayLength);
    exitSystem(PL);
}
//void main() {
//    menu();
//}
