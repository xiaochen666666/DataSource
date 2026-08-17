#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTEX_NUM 100  // 最大顶点数

//1. 图的邻接矩阵表示
typedef char VertexType;    // 顶点数据类型
typedef int EdgeType;       // 边权值类型

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];          // 顶点表
    EdgeType edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
    int vexnum, arcnum;                      // 当前顶点数和边数
} MGraph;

//2. 图的邻接表表示
typedef struct ArcNode {
    int adjvex;             // 该弧所指向的顶点位置
    struct ArcNode *nextarc; // 指向下一条弧的指针
    EdgeType info;          // 网的边权值
} ArcNode;

typedef struct VNode {
    VertexType data;        // 顶点信息
    ArcNode *firstarc;      // 指向第一条依附该顶点的弧
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;       // 邻接表
    int vexnum, arcnum;     // 图的顶点数和弧数
} ALGraph;

// 队列结构（用于BFS）
typedef struct {
    int data[MAX_VERTEX_NUM];
    int front, rear;
} Queue;

// 队列操作
void InitQueue(Queue *Q) {
    Q->front = Q->rear = 0;
}

bool QueueEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

bool EnQueue(Queue *Q, int e) {
    if ((Q->rear + 1) % MAX_VERTEX_NUM == Q->front)
        return false;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX_VERTEX_NUM;
    return true;
}

bool DeQueue(Queue *Q, int *e) {
    if (QueueEmpty(Q))
        return false;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX_VERTEX_NUM;
    return true;
}

//3. 邻接矩阵的基本操作
void CreateMGraph(MGraph *G) {
	int i,j,k; 
    printf("输入顶点数和边数: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    
    printf("输入顶点信息: ");
    for (i = 0; i < G->vexnum; i++)
        scanf(" %c", &G->vexs[i]);
    
    // 初始化邻接矩阵
    for (i = 0; i < G->vexnum; i++)
        for (j = 0; j < G->vexnum; j++)
            G->edges[i][j] = 0;
    
    printf("输入边(vi,vj)及其权值:\n");
    for (k = 0; k < G->arcnum; k++) {
        int i, j, w;
        scanf("%d %d %d", &i, &j, &w);
        G->edges[i][j] = w;
        G->edges[j][i] = w; // 无向图
    }
}

bool Adjacent(MGraph G, int x, int y) {
    return G.edges[x][y] != 0;
}

void Neighbors(MGraph G, int x) {
	int y;
    printf("顶点%c的邻接顶点: ", G.vexs[x]);
    for (y = 0; y < G.vexnum; y++)
        if (G.edges[x][y] != 0)
            printf("%c ", G.vexs[y]);
    printf("\n");
}

void InsertVertex(MGraph *G, VertexType x) {
	int i;
    if (G->vexnum >= MAX_VERTEX_NUM) {
        printf("图已满，无法插入新顶点\n");
        return;
    }
    G->vexs[G->vexnum] = x;
    for (i = 0; i <= G->vexnum; i++) {
        G->edges[G->vexnum][i] = 0;
        G->edges[i][G->vexnum] = 0;
    }
    G->vexnum++;
}

void DeleteVertex(MGraph *G, int x) {
	int i,j;
    if (x < 0 || x >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    // 统计要删除的边数
    int count = 0;
    for (i = 0; i < G->vexnum; i++)
        if (G->edges[x][i] != 0) count++;
    
    // 删除顶点x
    for (i = x; i < G->vexnum - 1; i++)
        G->vexs[i] = G->vexs[i + 1];
    
    // 删除与x相关的边
    for (i = 0; i < G->vexnum; i++)
        for (j = x; j < G->vexnum - 1; j++)
            G->edges[i][j] = G->edges[i][j + 1];
    
    for (i = 0; i < G->vexnum; i++)
        for (j = x; j < G->vexnum - 1; j++)
            G->edges[j][i] = G->edges[j + 1][i];
    
    G->vexnum--;
    G->arcnum -= count;
}

void AddEdge(MGraph *G, int x, int y, EdgeType w) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    if (G->edges[x][y] == 0) {
        G->edges[x][y] = w;
        G->edges[y][x] = w; // 无向图
        G->arcnum++;
    }
}

void RemoveEdge(MGraph *G, int x, int y) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    if (G->edges[x][y] != 0) {
        G->edges[x][y] = 0;
        G->edges[y][x] = 0; // 无向图
        G->arcnum--;
    }
}

int FirstNeighbor(MGraph G, int x) {
	int y;
    if (x < 0 || x >= G.vexnum) return -1;
    for (y = 0; y < G.vexnum; y++)
        if (G.edges[x][y] != 0)
            return y;
    return -1;
}

int NextNeighbor(MGraph G, int x, int y) {
	int z;
    if (x < 0 || x >= G.vexnum || y < 0 || y >= G.vexnum) return -1;
    for (z = y + 1; z < G.vexnum; z++)
        if (G.edges[x][z] != 0)
            return z;
    return -1;
}

EdgeType Get_edge_value(MGraph G, int x, int y) {
    if (x < 0 || x >= G.vexnum || y < 0 || y >= G.vexnum) return INT_MAX;
    return G.edges[x][y];
}

void Set_edge_value(MGraph *G, int x, int y, EdgeType v) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) return;
    G->edges[x][y] = v;
    G->edges[y][x] = v; // 无向图
}

// 邻接表的基本操作
void CreateALGraph(ALGraph *G) {
	int i,k;
    printf("输入顶点数和边数: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    
    printf("输入顶点信息: ");
    for (i = 0; i < G->vexnum; i++) {
        scanf(" %c", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }
    
    printf("输入边(vi,vj)及其权值:\n");
    for (k = 0; k < G->arcnum; k++) {
        int i, j, w;
        scanf("%d %d %d", &i, &j, &w);
        
        // 添加边i->j
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = w;
        p->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = p;
        
        // 无向图，添加边j->i
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = i;
        p->info = w;
        p->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = p;
    }
}

// 图的遍历
bool visited[MAX_VERTEX_NUM]; // 访问标记数组

void visit(VertexType v) {
    printf("%c ", v);
}

// 广度优先搜索（邻接矩阵）
void BFS_M(MGraph G, int v) {
    Queue Q;
    InitQueue(&Q);
    visit(G.vexs[v]);
    visited[v] = true;
    EnQueue(&Q, v);
    
    while (!QueueEmpty(&Q)) {
        int u,w;
        DeQueue(&Q, &u);
        for (w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
            if (!visited[w]) {
                visit(G.vexs[w]);
                visited[w] = true;
                EnQueue(&Q, w);
            }
        }
    }
}

void BFSTraverse_M(MGraph G) {
	int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            BFS_M(G, i);
}

// 深度优先搜索（邻接矩阵）
void DFS_M(MGraph G, int v) {
	int w;
    visit(G.vexs[v]);
    visited[v] = true;
    for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
        if (!visited[w])
            DFS_M(G, w);
}

void DFSTraverse_M(MGraph G) {
	int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS_M(G, i);
}

// 广度优先搜索（邻接表）
void BFS_AL(ALGraph G, int v) {
    Queue Q;
    InitQueue(&Q);
    visit(G.vertices[v].data);
    visited[v] = true;
    EnQueue(&Q, v);
    
    while (!QueueEmpty(&Q)) {
        int u;
        DeQueue(&Q, &u);
        ArcNode *p = G.vertices[u].firstarc;
        while (p != NULL) {
            int w = p->adjvex;
            if (!visited[w]) {
                visit(G.vertices[w].data);
                visited[w] = true;
                EnQueue(&Q, w);
            }
            p = p->nextarc;
        }
    }
}

void BFSTraverse_AL(ALGraph G) {
	int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            BFS_AL(G, i);
}

// 深度优先搜索（邻接表）
void DFS_AL(ALGraph G, int v) {
    visit(G.vertices[v].data);
    visited[v] = true;
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL) {
        int w = p->adjvex;
        if (!visited[w])
            DFS_AL(G, w);
        p = p->nextarc;
    }
}

void DFSTraverse_AL(ALGraph G) {
	int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS_AL(G, i);
}

/*非递归实现图的遍历 
// 图的遍历 - 非递归实现
bool visited[MAX_VERTEX_NUM]; // 访问标记数组

void visit(VertexType v) {
    printf("%c ", v);
}

// 栈结构（用于DFS非递归）
typedef struct {
    int data[MAX_VERTEX_NUM];
    int top;
} Stack;

void InitStack(Stack *S) {
    S->top = -1;
}

bool StackEmpty(Stack *S) {
    return S->top == -1;
}

bool Push(Stack *S, int e) {
    if (S->top >= MAX_VERTEX_NUM - 1)
        return false;
    S->data[++S->top] = e;
    return true;
}

bool Pop(Stack *S, int *e) {
    if (StackEmpty(S))
        return false;
    *e = S->data[S->top--];
    return true;
}

bool GetTop(Stack *S, int *e) {
    if (StackEmpty(S))
        return false;
    *e = S->data[S->top];
    return true;
}

// 广度优先搜索（邻接矩阵）- 非递归
void BFS_M(MGraph G, int v) {
    Queue Q;
    InitQueue(&Q);
    visit(G.vexs[v]);
    visited[v] = true;
    EnQueue(&Q, v);
    
    while (!QueueEmpty(&Q)) {
        int u, w;
        DeQueue(&Q, &u);
        for (w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
            if (!visited[w]) {
                visit(G.vexs[w]);
                visited[w] = true;
                EnQueue(&Q, w);
            }
        }
    }
}

void BFSTraverse_M(MGraph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            BFS_M(G, i);
}

// 深度优先搜索（邻接矩阵）- 非递归
void DFS_M_NonRecursive(MGraph G, int v) {
    Stack S;
    InitStack(&S);
    Push(&S, v);
    visited[v] = true;
    
    while (!StackEmpty(&S)) {
        int u, w;
        Pop(&S, &u);
        visit(G.vexs[u]);
        
        // 将所有未访问的邻接点入栈（注意顺序，为了与递归顺序一致，需要逆序入栈）
        int neighbors[MAX_VERTEX_NUM];
        int count = 0;
        
        // 先收集所有邻接点
        for (w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
            if (!visited[w]) {
                neighbors[count++] = w;
                visited[w] = true; // 标记为已访问，避免重复入栈
            }
        }
        
        // 逆序入栈，保证先访问第一个邻接点
        for (int i = count - 1; i >= 0; i--) {
            Push(&S, neighbors[i]);
        }
    }
}

// 深度优先搜索（邻接矩阵）- 非递归（另一种实现方式）
void DFS_M_NonRecursive2(MGraph G, int v) {
    Stack S;
    InitStack(&S);
    Push(&S, v);
    
    while (!StackEmpty(&S)) {
        int u, w;
        Pop(&S, &u);
        
        if (!visited[u]) {
            visit(G.vexs[u]);
            visited[u] = true;
            
            // 将未访问的邻接点逆序入栈
            for (w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
                if (!visited[w]) {
                    Push(&S, w);
                }
            }
        }
    }
}

void DFSTraverse_M_NonRecursive(MGraph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS_M_NonRecursive(G, i);
}

// 广度优先搜索（邻接表）- 非递归
void BFS_AL(ALGraph G, int v) {
    Queue Q;
    InitQueue(&Q);
    visit(G.vertices[v].data);
    visited[v] = true;
    EnQueue(&Q, v);
    
    while (!QueueEmpty(&Q)) {
        int u;
        DeQueue(&Q, &u);
        ArcNode *p = G.vertices[u].firstarc;
        while (p != NULL) {
            int w = p->adjvex;
            if (!visited[w]) {
                visit(G.vertices[w].data);
                visited[w] = true;
                EnQueue(&Q, w);
            }
            p = p->nextarc;
        }
    }
}

void BFSTraverse_AL(ALGraph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            BFS_AL(G, i);
}

// 深度优先搜索（邻接表）- 非递归
void DFS_AL_NonRecursive(ALGraph G, int v) {
    Stack S;
    InitStack(&S);
    Push(&S, v);
    visited[v] = true;
    
    while (!StackEmpty(&S)) {
        int u;
        Pop(&S, &u);
        visit(G.vertices[u].data);
        
        // 将所有未访问的邻接点逆序入栈
        ArcNode *p = G.vertices[u].firstarc;
        Stack tempStack;
        InitStack(&tempStack);
        
        // 先收集所有邻接点到临时栈（实现逆序）
        while (p != NULL) {
            if (!visited[p->adjvex]) {
                Push(&tempStack, p->adjvex);
                visited[p->adjvex] = true;
            }
            p = p->nextarc;
        }
        
        // 从临时栈弹出并压入主栈（实现正序）
        while (!StackEmpty(&tempStack)) {
            int w;
            Pop(&tempStack, &w);
            Push(&S, w);
        }
    }
}

// 深度优先搜索（邻接表）- 非递归（更简洁的实现）
void DFS_AL_NonRecursive2(ALGraph G, int v) {
    Stack S;
    InitStack(&S);
    Push(&S, v);
    
    while (!StackEmpty(&S)) {
        int u;
        Pop(&S, &u);
        
        if (!visited[u]) {
            visit(G.vertices[u].data);
            visited[u] = true;
            
            // 将邻接点逆序入栈
            ArcNode *p = G.vertices[u].firstarc;
            while (p != NULL) {
                if (!visited[p->adjvex]) {
                    Push(&S, p->adjvex);
                }
                p = p->nextarc;
            }
        }
    }
}

void DFSTraverse_AL_NonRecursive(ALGraph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS_AL_NonRecursive(G, i);
}

// 统一的非递归遍历接口
void GraphTraverse_NonRecursive(MGraph MG, ALGraph ALG) {
    printf("\n=== 非递归遍历 ===\n");
    
    printf("\n邻接矩阵图的广度优先遍历（非递归）:\n");
    BFSTraverse_M(MG);
    
    printf("\n邻接矩阵图的深度优先遍历（非递归）:\n");
    DFSTraverse_M_NonRecursive(MG);
    
    printf("\n邻接表图的广度优先遍历（非递归）:\n");
    BFSTraverse_AL(ALG);
    
    printf("\n邻接表图的深度优先遍历（非递归）:\n");
    DFSTraverse_AL_NonRecursive(ALG);
}

*/
int main() {
    MGraph MG;
    ALGraph ALG;
    
    printf("创建邻接矩阵图:\n");
    CreateMGraph(&MG);
    
    printf("\n邻接矩阵图的广度优先遍历:\n");
    BFSTraverse_M(MG);
    
    printf("\n邻接矩阵图的深度优先遍历:\n");
    DFSTraverse_M(MG);
    
    printf("\n\n创建邻接表图:\n");
    CreateALGraph(&ALG);
    
    printf("\n邻接表图的广度优先遍历:\n");
    BFSTraverse_AL(ALG);
    
    printf("\n邻接表图的深度优先遍历:\n");
    DFSTraverse_AL(ALG);
    
    return 0;
}
