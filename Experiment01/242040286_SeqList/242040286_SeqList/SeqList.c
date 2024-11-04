#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

typedef enum {
    ASC, DESC
} SortType;

typedef struct {
    int data[MAXLEN];
    int length;
} SeqList, * PseqList;


PseqList initList() {
    PseqList PL = malloc(sizeof(SeqList));
    if (PL) {
        PL->length = 0;
    }
    return PL;
}


void addList(PseqList PL, int item) {
    if (PL->length < MAXLEN) {
        PL->data[PL->length++] = item;
    }
    else {
        printf("˳����Ѵﵽ���洢��Χ\n");
    }
}


int deleteList(PseqList PL, int item) {
    for (int i = 0; i < PL->length; i++) {
        if (PL->data[i] == item) {
            // �ҵ�Ԫ�أ�����ɾ��
            for (int j = i; j < PL->length - 1; j++) {
                PL->data[j] = PL->data[j + 1];
            }
            PL->length--;
            return 1;
        }
    }
    printf("Ԫ��δ�ҵ�\n");
    return -1;
}


int findList(PseqList PL, int element) {
    if (PL == NULL || PL->length == 0) {
        return -1;
    }

    for (int i = 0; i < PL->length; i++) {
        if (PL->data[i] == element) {
            return i;
        }
    }
    return -1;
}

// ����
void sortList(PseqList PL, SortType type) {
    if (PL == NULL || PL->length <= 1) {
        return;
    }

    for (int i = 0; i < PL->length - 1; i++) {
        for (int j = 0; j < PL->length - i - 1; j++) {
            if ((type == ASC && PL->data[j] > PL->data[j + 1]) ||
                (type == DESC && PL->data[j] < PL->data[j + 1])) {
                int temp = PL->data[j];
                PL->data[j] = PL->data[j + 1];
                PL->data[j + 1] = temp;
            }
        }
    }
}

// �ϲ�
PseqList mergeList(PseqList P1, PseqList P2) {
    PseqList mergedList = initList();
    if (!mergedList) {
        return NULL;
    }

    for (int i = 0; i < P1->length; i++) {
        addList(mergedList, P1->data[i]);
    }

    for (int i = 0; i < P2->length; i++) {
        if (findList(mergedList, P2->data[i]) == -1) {
            addList(mergedList, P2->data[i]);
        }
    }

    return mergedList;
}


void displayList(PseqList PL) {
    for (int i = 0; i < PL->length; i++) {
        printf("data[%d] = %d\n", i, PL->data[i]);
    }
}


int main() {
    PseqList A = initList();
    addList(A, 2);
    addList(A, 3);
    addList(A, 1);
    printf("A��˳���:\n");
    displayList(A);
   
    PseqList B = initList();
    addList(B, 1);
    addList(B, 2);
    addList(B, 4);
    printf("B��˳���:\n");
    displayList(B);
    
    printf("A����������˳���:\n");
    sortList(A, ASC);
    displayList(A);
    printf("A����������˳���:\n");
    sortList(A, DESC);
    displayList(A);
    printf("B����������˳���:\n");
    sortList(B, ASC);
    displayList(B);
    printf("B��������˳���:\n");
    sortList(B, DESC);
    displayList(B);


    PseqList merged = mergeList(A, B);
    printf("�ϲ����˳���:\n");
    displayList(merged);
    printf("�ϲ����˳�����������:\n");
    sortList(merged, ASC);
    displayList(merged);
    printf("�ϲ����˳���������:\n");
    sortList(merged, DESC);
    displayList(merged);
    free(A);
    free(B);
    free(merged);

    return 0;
}
