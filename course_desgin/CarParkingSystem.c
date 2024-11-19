
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_SIZE 20

typedef struct car
{
    char num[10];
    char name[10];
} Car;

typedef struct
{
    Car data[MAX_SIZE];
    int n;
    int top;
} Stack;

typedef struct
{
    Car data[MAX_SIZE];
    int n;
    int num;
    int front, rear;
} Queue;

Stack *SCar;
Queue *QCar;

void carmenu(void);
void InitStack(Stack *S)
{
    S->top = -1;
    S->n = MAX_SIZE;
}

void InitQueue(Queue *Q)
{
    Q->front = Q->rear = Q->num = 0;
    Q->n = MAX_SIZE;
}

int Push(Stack *S, Car x)
{
    if (S->top == S->n - 1)
    {
        return (-1);
    }
    S->top++;
    S->data[S->top] = x;
    return (0);
}

int Pop(Stack *S, Car *px)
{
    if (S->top == -1)
    {
        return (-1);
    }
    S->top--;
    *px = S->data[S->top + 1];
    return (0);
}

int InsertQueue(Queue *Q, Car x)
{
    if (((Q->rear + 1) % Q->n) == Q->rear)
    {
        return (-1);
    }
    Q->num++;
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % Q->n;
    return (0);
}

int DeleteQueue(Queue *Q, Car *x)
{
    if (Q->front == Q->rear)
    {
        return (-1);
    }
    Q->num--;
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % Q->n;
    return (0);
}

void ShowCar(void)
{
    int i, front, rear;
    if (SCar->top == -1)
    {
        printf("\nThe carpark is empty!\n");
        getchar();
        return;
    }
    printf("\nThe Current Car Are: \n "
           "---car's number-----driver's name\n");

    for (int i = 0; i < SCar->top + 1; i++)
    {
        printf("%-13s", SCar->data[i].num);
        printf("%18s\n", SCar->data[i].name);
    }

    if (QCar->rear != QCar->front)
    {
        front = QCar->front;
        rear = QCar->rear;
        printf("\nTong Dao Information:\n---car's number-----driver's name");
        while (front != rear)
        {
            printf("%-13s\n", QCar->data[front].num);
            printf("%18s\n", QCar->data[front].name);
            front = (front + 1) % QCar->n;
        }
    }
    getchar();
    carmenu();
}

void InitCarpark(void)
{
    char num[8], *pnum, name[10], *pname;
    Car pcar;
    pnum = num;
    pname = name;
    printf("\n\n input car's information (end of '# #') : \n");
    scanf("%s%s", pnum, pname);
    while (strcmp(pnum, "#") != 0)
    {
        strcpy(pcar.num, pnum);
        strcpy(pcar.name, pname);
        if (Push(SCar, pcar) == -1)
        {
            printf("\nche zhan yi man! che liang yi jin ru tong dao!\n");
            getchar();
            if (InsertQueue(QCar, pcar) == -1)
            {
                printf("\n Insert Tong Dao Failed!\n");
            }
            break;
        }
        scanf("%s%s", pnum, pname);
    }
    carmenu();
}

void InsertCar(void)
{
    char num[10], *pnum, name[10], *pname;
    Car pcar;
    pnum = num;
    pname = name;
    printf("\n\n Please input car's inforation: \n");
    scanf("%s%s", pnum, pname);
    strcpy(pcar.num, pnum);
    strcpy(pcar.name, pname);
    if (Push(SCar, pcar) == -1)
    {
        printf("\nche zhan yi man! che liang yi jin ru tong dao!\n");
        getchar();
        if (InsertQueue(QCar, pcar) == -1)
        {
            printf("\n Insert Tong Dao Failed!\n");
        }
    }
    carmenu();
}

void ExitCar(void)
{
    int i, position, flag = 0;
    Car x;
    Stack *S;
    char num[10], *pnum;
    pnum = num;
    if (SCar->top == -1)
    {
        printf("\n\n The carpark is empty!\n");
        getchar();
        carmenu();
    }
    printf("\n\n Please input car's number: \n");
    scanf("%s", pnum);
    for (i = 0; i < SCar->top + 1; i++)
    {
        if (strcmp(SCar->data[i].num, pnum) == 0)
        {
            flag = 1;
            position = i;
        }
    }
    if (flag == 0)
    {
        printf("car not found!");
        getchar();
        carmenu();
    }
    if ((S = (Stack *)malloc(sizeof(Stack))) == NULL)
    {
        printf("Failed!");
        exit(1);
    }
    InitStack(S);
    for (i = SCar->top; i > position; i--)
    {
        Pop(SCar, &x);
        Push(S, x);
    }
    Pop(SCar, &x);
    while (S->top != -1)
    {
        Pop(S, &x);
        Push(SCar, x);
    }
    if (QCar->rear != QCar->front)
    {
        DeleteQueue(QCar, &x);
        Push(SCar, x);
        printf("\n Exit Success!\n");
        getchar();
        carmenu();
    }
}

void SetCar(void)
{
    int n, flag = 1;
    printf("\n\n The current paramenter of carpark's maxnum is: %d\n", SCar->n);
    printf("\n\n Please input the carpark's maxsize car number: (<=%d) \n", MAX_SIZE);
    do
    {
        scanf("%d", &n);
        if (n < SCar->top + 1)
        {
            flag = 0;
            n = SCar->n;
            break;
        }
    } while (n < 0 || n > MAX_SIZE);
    SCar->n = n;
    if (flag != 0)
    {
        printf("\n Modify Success!\n");
    }
    else
    {
        printf("\n Eroor! che zhan che liang yi chao guo ci shu! \n");
    }
    getchar();
    carmenu();
}

void carmenu(void)
{
    char ch;
    printf("\n姓名:张金鑫 学号:242040286 班级:计升247班\n");
    printf("\n----------------menu----------------\n");
    printf(
        "\n 1.init carpark"
        "\n 2.car enter "
        "\n 3.car exit"
        "\n 4.show information"
        "\n 5.set"
        "\n 0.exit \n");
    printf("\n----------------menu----------------\n");
    printf("\n Please Choose: (1-5)  ");
    ch = getchar();
    switch (ch - '0')
    {
    case 0:
        exit(0);
        break;
    case 1:
        InitCarpark();
        break;
    case 2:
        ExitCar();
        break;
    case 3:
        ShowCar();
        break;
    case 4:
        SetCar();
        break;
    default:
        ShowCar();
    }
}

int main(void)
{
    if ((SCar = (Stack *)malloc(sizeof(Stack))) == NULL)
    {
        printf("Failed!");
        exit(1);
    }
    if ((QCar = (Queue *)malloc(sizeof(Queue))) == NULL)
    {
        printf("Failed!");
        exit(1);
    }
    InitStack(SCar);
    InitQueue(QCar);

    carmenu();
    exit(0);
}
