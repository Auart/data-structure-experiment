#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100
typedef enum 
{
	ASC,DESC
} SortType;

typedef struct {
	int data[MAXLEN];
	int length;
} SeqList ,*PseqList;

PseqList initList() {
	PseqList PL = malloc(sizeof(SeqList));
	if (PL)
		PL->length = 0;
	return PL;
}
void addList(PseqList PL, int item) {
	if (PL->length < MAXLEN) {
		PL->data[PL->length++] = item;
	}
	else {
		printf("顺序表已达到最大存储范围");
	}
}
int deleteList(PseqList PL, int item) {

	if (PL->length < MAXLEN) {
		PL->data[PL->length--] = item;
		return 1;
	}
	else {
		printf("顺序表已为空！");
		return -1;
	}
}
int findlist(PseqList PL, int element) {
	if (PL == NULL || (PL->length) <= 1) {
		return;
	}

	for (int i = 0; i < PL->length; i++) {
		if (PL->data[i] == element) {
			//printf("元素已找到！");
			return i;
		}
	
	}
	return -1;
}
void findListByIndex(PseqList PL,int index) {
	findlist(PL, PL->data[index]);
}
void findListByItem(PseqList PL,int item) {
	findlist(PL, item);
}




void sortList(PseqList PL , SortType type) {
	if (!PL == NULL || !(PL->length) <= 1) {
		int sortTypeInt =((type == ASC) ? 1 : -1);
		for (int i = 0; i < PL->length - 1; i++) {
			for (int j = 0; j < PL->length - i - 1; j++) {
				if (sortTypeInt * (PL->data[j]) > sortTypeInt * (PL->data[j + 1])) {
					int temp = PL->data[j];
					PL->data[j] = PL->data[j + 1];
					PL->data[j + 1] = temp;
				}
			}
		}
	}
}
PseqList mergeList(PseqList P1, PseqList P2) {
	PseqList mergedList = initList();
	if (!mergedList) {
		return NULL;
	}


	for (int i = 0; i < P1->length; i++) {
		addList(mergedList, P1->data[i]);
	}

	
	for (int i = 0; i < P2->length; i++) {
		
			if (findlist(mergedList, P2->data[i]) == -1) { 
				addList(mergedList, P2->data[i]);
			}
		
		
	}

	return mergedList;
}

void displayList(PseqList PL) {
	for (int i=0; i < PL->length; i++) {
		printf("序号%d data=%d\n", i + 1, PL->data[i]);
	}
}

void main() {
	PseqList A = initList();
	addList(A, 2);
	addList(A, 3); 
	addList(A, 1);
	//displayList(A);
	PseqList B = initList();
	addList(B, 1);
	addList(B, 2);
	addList(B, 4);
	//sortList(A, ASC);
	displayList(A);
	
	PseqList merged = mergeList(A, B);
	printf("合并后的顺序表:\n");
	displayList(merged);

	
	free(A);
	free(B);
	free(merged);

}