#include <stdio.h>
#define N 5  

// 队列操作
typedef struct {
    int arr[N];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

int isFull(Queue* q) {
    return (q->rear + 1) % N == q->front;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, int value) {
    if (!isFull(q)) {
        q->arr[q->rear] = value;
        q->rear = (q->rear + 1) % N;
    }
}

int dequeue(Queue* q) {
    if (!isEmpty(q)) {
        int value = q->arr[q->front];
        q->front = (q->front + 1) % N;
        return value;
    }
    return -1;
}

// 循环移位
void rotateArray(int arr[], int shift) {
    Queue q;
    initQueue(&q);
    
    // 将数组元素入队
    for (int i = 0; i < N; i++) {
        enqueue(&q, arr[i]);
    }

    // 出队并重新入队实现移位
    for (int i = 0; i < shift; i++) {
        int front = dequeue(&q);
        enqueue(&q, front);
    }

    // 取出队列中的元素，更新数组
    for (int i = 0; i < N; i++) {
        arr[i] = dequeue(&q);
    }
}

// 打印数组
void printArray(int arr[]) {
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[N] = {1, 2, 3, 4, 5};
    int shift = 2;  // 设置移位步数

    printf("原始数组: ");
    printArray(arr);

    rotateArray(arr, shift);

    printf("移位后的数组: ");
    printArray(arr);

    return 0;
}
