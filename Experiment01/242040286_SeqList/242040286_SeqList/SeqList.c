#include "stdio.h";
#include "stdlib.h";
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
void deleteList(PseqList PL, int item) {

	if (PL->length < MAXLEN) {
		PL->data[PL->length--] = item;
	}
	else {
		printf("顺序表已为空！");
	}
}
void findListByIndex(PseqList PL,int index) {
	findlist(PL, PL->data[index]);
}
void findListByItem(PseqList PL,int item) {
	findlist(PL, item);
}
void findlist(PseqList PL, void *element) {
	if (!PL == NULL || !(PL->length) <= 1) {
		for (int i; i < PL->length; i++) {
			PL->data[i] == element ? printf("元素已找到！") : printf("元素未找到！");
		}
	}
}
void sortList(PseqList PL , SortType type) {
	if (!PL == NULL || !(PL->length) <= 1) {
		int sortTypeInt =((type == ASC) ? 1 : -1);
		for (int i = 0; i < PL->length - 1; i++) {
			for (int j = 0; j < PL->length - i - 1; j++) {
				if (sortTypeInt * (PL->data[j]) < sortTypeInt * (PL->data[j+1]) ) {
					int temp = PL->data[j];
					PL->data[j] = PL->data[j + 1];
					PL->data[j + 1] = temp;
				}
			}
		}
	}
}


void main() {

}