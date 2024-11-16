#include <stdio.h>
#define N 5  // 迷宫的大小

// 迷宫的结构
int maze[N][N] = {
    {1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1}
};

// 坐标结构体
typedef struct {
    int x, y;
} Point;

// 判断当前位置是否合法
int isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1;
}

// 栈的操作
typedef struct {
    Point stack[N*N];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Point p) {
    s->stack[++(s->top)] = p;
}

Point pop(Stack* s) {
    return s->stack[(s->top)--];
}

// 使用栈求解迷宫
void solveMaze() {
    Stack s;
    initStack(&s);
    Point start = {0, 0}, end = {4, 4};
    push(&s, start);
    maze[start.x][start.y] = 2;  // 标记已访问
    
    while (!isEmpty(&s)) {
        Point current = pop(&s);
        if (current.x == end.x && current.y == end.y) {
            printf("找到了出口！\n");
            return;
        }
        
        // 向四个方向尝试
        if (isValid(current.x + 1, current.y)) {  // 下
            push(&s, (Point){current.x + 1, current.y});
            maze[current.x + 1][current.y] = 2;  // 标记已访问
        }
        if (isValid(current.x, current.y + 1)) {  // 右
            push(&s, (Point){current.x, current.y + 1});
            maze[current.x][current.y + 1] = 2;
        }
        if (isValid(current.x - 1, current.y)) {  // 上
            push(&s, (Point){current.x - 1, current.y});
            maze[current.x - 1][current.y] = 2;
        }
        if (isValid(current.x, current.y - 1)) {  // 左
            push(&s, (Point){current.x, current.y - 1});
            maze[current.x][current.y - 1] = 2;
        }
    }
    printf("未找到出口。\n");
}

int main() {
    solveMaze();
    return 0;
}
