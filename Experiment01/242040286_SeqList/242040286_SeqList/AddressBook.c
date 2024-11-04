#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100
#define ABTITLE "\n==�ֻ�ͨѶ¼=="
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
    "����ͨѶ¼",
    "�����ϵ��",
    "ɾ����ϵ��",
    "������ϵ��",
    "��ʾ��ϵ��",
    "�˳�ϵͳ"
};

int menuArrayLength = sizeof(menuArray) / sizeof(menuArray[0]);

// ������뻺����
void clearScanf() {
    while (getchar() != '\n');
}


PABList initABList() {
    PABList PL = malloc(sizeof(ABList));
    if (PL) {
        PL->length = 0;
        printf("ͨѶ¼��ʼ���ɹ�!\n");
    }
    return PL;
}


void displayABList(PABList PL) {
    for (int i = 0; i < PL->length; i++) {
        printf("��ţ�%d ������%s | �绰��%s\n", i + 1, PL->ab[i].name, PL->ab[i].phone);
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
    printf("�������Ӧ��Ų���: ");
}


void createAB(PABList* PL) {
    if (*PL == NULL) {
        *PL = initABList();
    }
    else {
        printf("ͨѶ¼�ѽ���\n");
    }
}
void addAB(PABList* PL) {
    if (*PL == NULL) {
        printf("���Ƚ���ͨѶ¼\n");
        return;
    }
    AddressBook ab = { 0 };
    printf("��������ϵ�˵������͵绰: ");
    scanf_s("%s %s", ab.name, (unsigned)sizeof(ab.name), ab.phone, (unsigned)sizeof(ab.phone));
    clearScanf();
    if ((*PL)->length < MAXLEN) {
        (*PL)->ab[(*PL)->length++] = ab;
        printf("��ӳɹ�\n");
    }
    else {
        printf("ͨѶ¼����\n");
    }
}
void deleteAB(PABList* PL) {
    if (*PL == NULL) {
        printf("���Ƚ���ͨѶ¼\n");
        return;
    }
    AddressBook ab = { 0 };
    printf("������ɾ������ϵ������: ");
    scanf_s("%s", ab.name, (unsigned)sizeof(ab.name));
    clearScanf();
    for (int i = 0; i < (*PL)->length; i++) {
        if (strcmp((*PL)->ab[i].name, ab.name) == 0) {
            (*PL)->ab[(*PL)->length--] = ab;
            printf("ɾ���ɹ���\n");
        }
        else {
            printf("δ�ҵ�����ϵ�ˣ�\n");
        }
    }
}
void findAB(PABList* PL) {
    if (*PL == NULL) {
        printf("���Ƚ���ͨѶ¼\n");
        return;
    }
    printf("��������ҵ���ϵ������: ");
    AddressBook cab;
    scanf_s("%s", &cab.name, (unsigned)sizeof(cab.name));
    clearScanf();
    printf("%d", (*PL)->length);
    for (int i = 0; i < (*PL)->length; i++) {
        if (strcmp((*PL)->ab[i].name, cab.name) == 0) {
            printf("���ҳɹ�������ϵ����Ϣ����\n���%d |  ������%s | �绰��%s\n", i + 1, (*PL)->ab[i].name, (*PL)->ab[i].phone);
        }
        else {
            printf("δ�ҵ�����ϵ�ˣ�\n");
        }
    }
}

void displayAB(PABList* PL) {
    if (*PL == NULL || (*PL)->length == 0) {
        printf("ͨѶ¼Ϊ��\n");
    }
    else {
        displayList(*PL);
    }
}

void exitSystem(PABList* PL) {
    printf("ϵͳ�˳�\n");
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
        (c >= 1 && c <= menuArrayLength) ? menuFunctions[c - 1](&PL) : printf("��Чѡ��������\n");
    } while (c != menuArrayLength);
    exitSystem(PL);
}
//void main() {
//    menu();
//}
