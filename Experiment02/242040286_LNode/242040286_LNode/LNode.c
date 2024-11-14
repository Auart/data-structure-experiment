#include <stdio.h>
#include <malloc.h>
#define  DataType int;

typedef struct LNode{
    DataType Data;
    struct LNode *next;
} LNode ,*LinkList;

//初始化单链表
LinkList initList(){
   LinkList H;
   H=malloc(sizeof(LNode));
   if(H){
    H->next=NULL;
   }
   return H;
}




int main(){
    
    return 0;
}2