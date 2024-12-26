#include "stdio.h"
#include "stdlib.h"

#define MaxVerNum 30
#define INF 9999 // 表示无穷大，用于没有边的情况

typedef char VertexType;
typedef int EdgeType;

// 邻接矩阵存储图
typedef struct {
    VertexType vexs[MaxVerNum];
    EdgeType edges[MaxVerNum][MaxVerNum];
    int n, e; // 顶点数和边数
} MGraph;

// 初始化邻接矩阵
void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    printf("请输入顶点数和边数：\n");
    scanf("%d %d", &G->n, &G->e);
    printf("请输入顶点信息：\n");
    for (i = 0; i < G->n; i++) {
        scanf(" %c", &G->vexs[i]); // 输入顶点信息
    }
    // 初始化邻接矩阵
    for (i = 0; i < G->n; i++) {
        for (j = 0; j < G->n; j++) {
            G->edges[i][j] = INF; // 初始化为无穷大
        }
    }
    printf("请输入边<Vi,Vj>及权值：\n");
    for (k = 0; k < G->e; k++) {
        scanf("%d %d %d", &i, &j, &w);
        G->edges[i][j] = w;
        G->edges[j][i] = w; // 无向图对称
    }
}

// Prim 算法实现最小生成树
void Prim(MGraph G) {
    int minCost[MaxVerNum]; // 每个顶点加入生成树的最小代价
    int closest[MaxVerNum]; // 每个顶点的最近邻顶点
    int inTree[MaxVerNum] = {0}; // 标记顶点是否已在生成树中

    // 初始化
    for (int i = 0; i < G.n; i++) {
        minCost[i] = G.edges[0][i];
        closest[i] = 0; // 初始全部从顶点 0 引出
    }
    inTree[0] = 1; // 将第一个顶点加入生成树

    printf("最小生成树的边如下：\n");
    int totalWeight = 0;
    for (int i = 1; i < G.n; i++) {
        // 找到代价最小的边
        int min = INF, k = -1;
        for (int j = 0; j < G.n; j++) {
            if (!inTree[j] && minCost[j] < min) {
                min = minCost[j];
                k = j;
            }
        }

        // 输出选中的边
        printf("(%c, %c) 权值: %d\n", G.vexs[closest[k]], G.vexs[k], min);
        totalWeight += min;

        // 将顶点 k 加入生成树
        inTree[k] = 1;

        // 更新其他顶点的最小代价
        for (int j = 0; j < G.n; j++) {
            if (!inTree[j] && G.edges[k][j] < minCost[j]) {
                minCost[j] = G.edges[k][j];
                closest[j] = k;
            }
        }
    }
    printf("最小生成树的总权值为: %d\n", totalWeight);
}

int main() {
    MGraph G;
    CreateMGraph(&G);
    printf("\n使用 Prim 算法求解最小生成树：\n");
    Prim(G);
    return 0;
}
