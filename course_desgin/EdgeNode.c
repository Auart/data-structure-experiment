#include <stdio.h>
#include <stdlib.h>

typedef struct EdgeNode {
    int endvex;                                 /*相邻顶点在顶点表中的下标*/
    int weight;                                 /*边的权值*/
    struct EdgeNode *nextedge;                  /*链字段*/
} EdgeNode, *EdgeList;

typedef struct {
    int vertex;                                 /*顶点*/
    EdgeList edgelist;                          /*边表头指针*/
} VexNode;                                      /*顶点表中的结点*/

typedef struct {
    int vexnum;                                 /*顶点数*/
    int arcnum;                                 /*边数*/
    VexNode *vexs;                              /*顶点表*/
} GraphList;

void FindInDegree(GraphList *G, int *indegree);
int Toposort(GraphList *G, int *ptopo);
int CriticalPath(GraphList *G);
void InitGraph(GraphList *G);
void TopoSortMenu(void);
void CriticalMenu(void);
void TopoCriticalMenu(void);

void FindInDegree(GraphList *G, int *indegree) {
    int i;
    EdgeList p;
    for(i = 0; i < G->vexnum; i++)
        indegree[i] = 0;
    for(i = 0; i < G->vexnum; i++) {
        p = G->vexs[i].edgelist;
        while(p) {
            ++indegree[p->endvex];
            p = p->nextedge; 
        }
    }
}

int Toposort(GraphList *G, int *ptopo) {
    EdgeList p;
    int i, j, k, nodeno = 0, top = -1;
    int *indegree = (int*)malloc(sizeof(int) * G->vexnum);
    if (indegree == NULL) {
        printf("Memory allocation failed for indegree array.\n");
        return 0;
    }
    FindInDegree(G, indegree);  /*indegree 数组赋初值*/
    
    /*将入度为零的顶点入栈*/
    for(i = 0; i < G->vexnum; i++) {
        if(indegree[i] == 0) {
            indegree[i] = top;
            top = i;
        }
    }

    while(top != -1) {
        j = top;
        top = indegree[top];  /*取栈顶元素并退栈*/
        ptopo[nodeno++] = j;  /*将该顶点输出到拓扑序列中*/
        p = G->vexs[j].edgelist;  /*取该元素边表中的第一个边结点*/
        while(p) {
            k = p->endvex;
            indegree[k]--;  /*删除以该顶点为起点的边*/
            if(indegree[k] == 0) {
                indegree[k] = top;  /*将新入度为零的顶点入栈*/
                top = k;
            }
            p = p->nextedge;
        }
    }
    
    free(indegree);
    if(nodeno < G->vexnum)  /*AOV网中存在回路*/
        return 0;
    else
        return 1;
}

int CriticalPath(GraphList *G) {
    int i, j, k, sum = 0;
    EdgeList p;
    int *ee = (int*)malloc(sizeof(int) * G->vexnum);
    int *le = (int*)malloc(sizeof(int) * G->vexnum);
    int *l = (int*)malloc(sizeof(int) * G->vexnum);
    int *e = (int*)malloc(sizeof(int) * G->vexnum);
    int *topo = (int*)malloc(sizeof(int) * G->vexnum);

    if(Toposort(G, topo) == 0) {
        printf("The AOE network has a cycle!\n");
        free(ee);
        free(le);
        free(l);
        free(e);
        free(topo);
        return 0;
    }

    /*初始化 ee 数组为 0 */
    for(i = 0; i < G->vexnum; i++) 
        ee[i] = 0;
    
    /*计算事件最早发生时间*/
    for(k = 0; k < G->vexnum; k++) {
        i = topo[k];
        p = G->vexs[i].edgelist;
        while(p != NULL) {
            j = p->endvex;
            if(ee[i] + p->weight > ee[j])
                ee[j] = ee[i] + p->weight;
            p = p->nextedge;
        }
    }

    sum = ee[G->vexnum - 1];  /*工程的最短完成时间*/

    /*初始化 le 数组为最大值*/
    for(i = 0; i < G->vexnum; i++) 
        le[i] = sum;

    /*计算事件允许的最迟发生时间*/
    for(k = G->vexnum - 2; k >= 0; k--) {
        i = topo[k];
        p = G->vexs[i].edgelist;
        while(p != NULL) {
            j = p->endvex;
            if((le[j] - p->weight) < le[i])
                le[i] = le[j] - p->weight;
            p = p->nextedge;
        }
    }
	printf("\n姓名：张金鑫  学号：242040286  班级：计升247\n");
    printf("\nThe Critical Path:\n");
    printf("|Active |Early | Late |  L-E | IsCritical  \n");

    /*计算活动ak的最早开始时间e(k)和最晚开始时间l(k)*/
    int kIndex = 0;
    for(i = 0; i < G->vexnum; i++) {
        p = G->vexs[i].edgelist;
        while(p != NULL) {
            j = p->endvex;
            e[kIndex] = ee[i];
            l[kIndex] = le[j] - p->weight;
            printf("| <%d,%d> | %4d | %4d | %4d | ", i, j, e[kIndex], l[kIndex], l[kIndex] - e[kIndex]);
            if(e[kIndex] == l[kIndex]) 
                printf("Critical");
            printf("\n");
            kIndex++;
            p = p->nextedge;
        }
    }

    printf("\nThe shortest time is: %d\n", sum);

    free(ee);
    free(le);
    free(l);
    free(e);
    free(topo);

    return 1;
}

void InitGraph(GraphList *G) {
    int i, vexnum, arcnum, weight = 0;
    int v1, v2;
    EdgeList p;

    printf("Please input the vertexnum and the arcnum-->Form: (x,y) \n");
    scanf("%d,%d", &vexnum, &arcnum);
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    G->vexs = (VexNode*)malloc(sizeof(VexNode) * vexnum);

    for(i = 0; i < vexnum; i++) {
        G->vexs[i].vertex = i + 1;
        G->vexs[i].edgelist = NULL;
    }

    for(i = 0; i < arcnum; i++) {
        printf("Please input The %d Edge (For Example: 1,2,10)\n", i + 1);
        scanf("%d,%d,%d", &v1, &v2, &weight);
        if(v1 > G->vexnum || v2 > G->vexnum) {
            printf("The Node You Have Just Input Is Not In The Vexs!\n");
            exit(0);
        }
        p = (EdgeList)malloc(sizeof(EdgeNode));
        p->endvex = v2;
        p->weight = weight;
        p->nextedge = G->vexs[v1].edgelist;
        G->vexs[v1].edgelist = p;
    }
}

void TopoSortMenu(void) {
    int *ptopo;
    int i;
    GraphList *Graph = (GraphList*)malloc(sizeof(GraphList));
    InitGraph(Graph);
    ptopo = (int*)malloc(sizeof(int) * Graph->vexnum);

    if (Toposort(Graph, ptopo) != 0) {
        printf("\nTopSort Result:\n");
        for(i = 0; i < Graph->vexnum - 1; i++) 
            printf("v%d-->", ptopo[i]);
        printf("v%d\n", ptopo[i]);
    } else {
        printf("The AOV network has a cycle!\n");
    }

    free(ptopo);
    free(Graph);
}

void CriticalMenu(void) {
    GraphList *Graph = (GraphList*)malloc(sizeof(GraphList));
    InitGraph(Graph);
    CriticalPath(Graph);
    free(Graph);
}

void TopoCriticalMenu(void) {
    int choice;
    do {
		printf("姓名：张金鑫  学号：242040286  班级：计升247\n");
        printf("1. Topological Sort\n");
        printf("2. Critical Path\n");
        printf("3. Exit\n");
        printf("Please input your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                TopoSortMenu();
                break;
            case 2:
                CriticalMenu();
                break;
            case 3:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
}

int main(void) {
    TopoCriticalMenu();
    return 0;
}
