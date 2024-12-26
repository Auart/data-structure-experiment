#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct car {
    char num[10];
    char name[10];
} Car;

typedef struct {
    Car data[MAX_SIZE];
    int n;   /* 栈容量 */
    int top; /* 顺序栈 */
} Stack;

typedef struct {
    Car data[MAX_SIZE];
    int n;   /* 队列容量 */
    int num; /* 队列中车辆数量 */
    int front, rear; /* 循环队列 */
} Queue;

Stack *SCar;  /* 车站内车辆栈 */
Queue *QCar;  /* 通道内车辆队列 */

void carmenu(void);

void InitStack(Stack *S) {
    S->top = -1;
    S->n = MAX_SIZE;
}

void InitQueue(Queue *Q) {
    Q->front = Q->rear = Q->num = 0;
    Q->n = MAX_SIZE;
}

int Push(Stack *S, Car x) { /* 入栈操作 */
    if (S->top == S->n - 1)
        return -1;
    S->top++;
    S->data[S->top] = x;
    return 0;
}

int Pop(Stack *S, Car *px) { /* 出栈操作 */
    if (S->top == -1)
        return -1;
    *px = S->data[S->top];
    S->top--;
    return 0;
}

int InsertQueue(Queue *Q, Car x) { /* 入队 */
    if (((Q->rear + 1) % Q->n) == Q->front) /* 队列已满 */
        return -1;
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % Q->n;
    Q->num++;
    return 0;
}

int DeleteQueue(Queue *Q, Car *x) { /* 出队 */
    if (Q->front == Q->rear) /* 队列为空 */
        return -1;
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % Q->n;
    Q->num--;
    return 0;
}

void ShowCar(void) { /* 显示车站和通道车辆信息 */
    int i, front, rear;
    if (SCar->top == -1) {
        printf("\n\nThe carpark is empty!\n");
        getchar();
        carmenu();
    }
    printf("\n\nThe Current Cars Are:\n---car's number--------driver's name\n");
    for (i = 0; i <= SCar->top; i++) {
        printf("     %-13s", SCar->data[i].num);
        printf("%18s\n", SCar->data[i].name);
    }
    if (QCar->front != QCar->rear) {
        front = QCar->front;
        rear = QCar->rear;
        printf("\nTong Dao Information:\n---car's number------driver's name\n");
        while (front != rear) {
            printf("     %-13s", QCar->data[front].num);
            printf("%18s\n", QCar->data[front].name);
            front = (front + 1) % QCar->n;
        }
    }
    getchar();
    carmenu();
}

void InitCarpark(void) { /* 初始化车站车辆 */
    char num[10], name[10];
    Car pcar;
    printf("\n\nInput car's information (end with '##'):\n");
    while (1) {
        scanf("%s", num);  // 输入车牌号
        if (strcmp(num, "##") == 0) break;  // 当输入'##'时退出循环
        scanf("%s", name);  // 输入司机名字
        strcpy(pcar.num, num);
        strcpy(pcar.name, name);
        if (Push(SCar, pcar) == -1) {  // 如果车场已满，转入通道
            printf("\nche zhan yi man!che liang yi jin ru tong dao!\n");
            if (InsertQueue(QCar, pcar) == -1)
                printf("\nInsert Tong Dao Failed!\n");
            break;
        }
    }
    printf("\nCars Enter Success!\n");  // 提示信息
    getchar();  // 读取并忽略缓冲区中的换行符
    carmenu();  // 返回主菜单
}


void InsertCar(void) { /* 新车入站 */
    char num[10], name[10];
    Car pcar;
    printf("\n\nPlease input car's information:\n");
    scanf("%s%s", num, name);
    strcpy(pcar.num, num);
    strcpy(pcar.name, name);
    if (Push(SCar, pcar) == -1) {
        printf("\nche zhan yi man!che liang yi jin ru tong dao!\n");
        if (InsertQueue(QCar, pcar) == -1)
            printf("\nInsert Tong Dao Failed!\n");
    }
    carmenu();
}

void ExitCar(void) { /* 车辆出站 */
    int i, position = -1;
    Car x;
    Stack *S;
    char num[10];
    if (SCar->top == -1) {
        printf("\n\nThe carpark is empty!\n");
        getchar();
        carmenu();
    }
    printf("\n\nPlease input car's number:\n");
    scanf("%s", num);
    for (i = 0; i <= SCar->top; i++) {
        if (strcmp(SCar->data[i].num, num) == 0) {
            position = i;
            break;
        }
    }
    if (position == -1) {
        printf("Car not found!\n");
        getchar();
        carmenu();
    }
    if ((S = (Stack *)malloc(sizeof(Stack))) == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    InitStack(S);
    for (i = SCar->top; i > position; i--) {
        Pop(SCar, &x);
        Push(S, x);
    }
    Pop(SCar, &x);
    while (S->top != -1) {
        Pop(S, &x);
        Push(SCar, x);
    }
    free(S);
    if (QCar->front != QCar->rear) {
        DeleteQueue(QCar, &x);
        Push(SCar, x);
    }
    printf("\nExit Success!\n");
    getchar();
    carmenu();
}

void SetCar(void) { /* 设置车站容量 */
    int n;
    printf("\n\nThe current parameter of carpark's maxnum is: %d\n", SCar->n);
    printf("Please input the carpark's max size (<= %d):\n", MAX_SIZE);
    while (1) {
        scanf("%d", &n);
        if (n >= SCar->top + 1 && n <= MAX_SIZE) {
            SCar->n = n;
            printf("\nModify Success!\n");
            break;
        } else {
            printf("\nError! che zhan che liang yi chao guo ci shu!\n");
        }
    }
    getchar();
    carmenu();
}

void carmenu(void) { /* 菜单显示 */
    char ch;
	printf("\n姓名：张金鑫  学号：242040286  班级：计升247\n");
    printf("\n-----------------Menu-----------------\n");
    printf("1. Init carpark\n2. Car enter\n3. Car exit\n4. Show information\n5. Set carpark size\n0. Exit\n");
    printf("--------------------------------------\n");
    printf("Please choose (0-5): ");
    scanf(" %c", &ch);
    switch (ch) {
        case '0': 
            free(SCar);
            free(QCar);
            exit(0);
        case '1': InitCarpark(); break;
        case '2': InsertCar(); break;
        case '3': ExitCar(); break;
        case '4': ShowCar(); break;
        case '5': SetCar(); break;
        default: 
            printf("Invalid choice! Try again.\n");
            carmenu();
    }
}

int main(void) {
    if ((SCar = (Stack *)malloc(sizeof(Stack))) == NULL) {
        printf("Memory allocation failed for SCar!\n");
        return 1;
    }
    if ((QCar = (Queue *)malloc(sizeof(Queue))) == NULL) {
        printf("Memory allocation failed for QCar!\n");
        free(SCar);
        return 1;
    }
    InitStack(SCar);
    InitQueue(QCar);
    carmenu();
    return 0;
}
