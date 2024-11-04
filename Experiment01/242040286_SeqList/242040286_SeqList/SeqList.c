#include "stdio.h";
#include "stdlib.h";
#define MAXLEN 100

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



void main() {

}