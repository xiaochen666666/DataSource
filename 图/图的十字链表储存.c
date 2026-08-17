#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTEX_NUM 100  // 最大顶点数

typedef char VertexType;    // 顶点数据类型
typedef int EdgeType;       // 边权值类型

// 十字链表表示
typedef struct ArcNode {
    int tailvex;            // 弧尾顶点位置
    int headvex;            // 弧头顶点位置
    struct ArcNode *hlink;  // 指向下一个相同弧头的弧
    struct ArcNode *tlink;  // 指向下一个相同弧尾的弧
    EdgeType info;          // 弧的权值
} ArcNode;

typedef struct VexNode {
    VertexType data;        // 顶点信息
    ArcNode *firstin;       // 指向以该顶点为弧头的第一条弧
    ArcNode *firstout;      // 指向以该顶点为弧尾的第一条弧
} VexNode;

typedef struct {
    VexNode xlist[MAX_VERTEX_NUM]; // 顶点表
    int vexnum, arcnum;            // 图的顶点数和弧数
} OLGraph;

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

// 查找顶点位置
int LocateVex(OLGraph G, VertexType v) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (G.xlist[i].data == v) {
            return i;
        }
    }
    return -1;
}

// 创建十字链表图
void CreateOLGraph(OLGraph *G) {
    int i, k;
    printf("输入顶点数和边数: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    
    printf("输入顶点信息: ");
    for (i = 0; i < G->vexnum; i++) {
        scanf(" %c", &G->xlist[i].data);
        G->xlist[i].firstin = NULL;
        G->xlist[i].firstout = NULL;
    }
    
    printf("输入边(vi,vj)及其权值:\n");
    for (k = 0; k < G->arcnum; k++) {
        VertexType v1, v2;
        int w;
        scanf(" %c %c %d", &v1, &v2, &w);
        
        int i = LocateVex(*G, v1);
        int j = LocateVex(*G, v2);
        
        if (i == -1 || j == -1) {
            printf("顶点不存在!\n");
            k--;
            continue;
        }
        
        // 创建新的弧节点
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->tailvex = i;
        p->headvex = j;
        p->info = w;
        
        // 插入到弧尾顶点的出弧链表中
        p->tlink = G->xlist[i].firstout;
        G->xlist[i].firstout = p;
        
        // 插入到弧头顶点的入弧链表中
        p->hlink = G->xlist[j].firstin;
        G->xlist[j].firstin = p;
    }
}

// 判断边是否存在
bool Adjacent(OLGraph G, int x, int y) {
    ArcNode *p = G.xlist[x].firstout;
    while (p != NULL) {
        if (p->headvex == y) {
            return true;
        }
        p = p->tlink;
    }
    return false;
}

// 获取顶点x的所有邻接顶点
void Neighbors(OLGraph G, int x) {
    printf("顶点%c的邻接顶点: ", G.xlist[x].data);
    
    // 出边邻接点（从x出发的边指向的顶点）
    ArcNode *p = G.xlist[x].firstout;
    while (p != NULL) {
        printf("%c ", G.xlist[p->headvex].data);
        p = p->tlink;
    }
    
    // 入边邻接点（指向x的边的起始顶点）
    p = G.xlist[x].firstin;
    while (p != NULL) {
        printf("%c ", G.xlist[p->tailvex].data);
        p = p->hlink;
    }
    printf("\n");
}

// 插入新顶点
void InsertVertex(OLGraph *G, VertexType x) {
    if (G->vexnum >= MAX_VERTEX_NUM) {
        printf("图已满，无法插入新顶点\n");
        return;
    }
    G->xlist[G->vexnum].data = x;
    G->xlist[G->vexnum].firstin = NULL;
    G->xlist[G->vexnum].firstout = NULL;
    G->vexnum++;
}

// 删除顶点
void DeleteVertex(OLGraph *G, int x) {
    if (x < 0 || x >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    // 删除所有以x为弧尾的弧
    ArcNode *p = G->xlist[x].firstout;
    while (p != NULL) {
        ArcNode *temp = p;
        p = p->tlink;
        
        // 从弧头顶点的入弧链表中删除该弧
        ArcNode *q = G->xlist[temp->headvex].firstin;
        ArcNode *prev = NULL;
        while (q != NULL) {
            if (q == temp) {
                if (prev == NULL) {
                    G->xlist[temp->headvex].firstin = q->hlink;
                } else {
                    prev->hlink = q->hlink;
                }
                free(q);
                G->arcnum--;
                break;
            }
            prev = q;
            q = q->hlink;
        }
    }
    
    // 删除所有以x为弧头的弧
    p = G->xlist[x].firstin;
    while (p != NULL) {
        ArcNode *temp = p;
        p = p->hlink;
        
        // 从弧尾顶点的出弧链表中删除该弧
        ArcNode *q = G->xlist[temp->tailvex].firstout;
        ArcNode *prev = NULL;
        while (q != NULL) {
            if (q == temp) {
                if (prev == NULL) {
                    G->xlist[temp->tailvex].firstout = q->tlink;
                } else {
                    prev->tlink = q->tlink;
                }
                free(q);
                G->arcnum--;
                break;
            }
            prev = q;
            q = q->tlink;
        }
    }
    
    // 移动顶点表中的顶点
    for (int i = x; i < G->vexnum - 1; i++) {
        G->xlist[i] = G->xlist[i + 1];
    }
    G->vexnum--;
    
    // 更新所有弧中的顶点索引
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *arc = G->xlist[i].firstout;
        while (arc != NULL) {
            if (arc->tailvex > x) arc->tailvex--;
            if (arc->headvex > x) arc->headvex--;
            arc = arc->tlink;
        }
    }
}

// 添加边
void AddEdge(OLGraph *G, int x, int y, EdgeType w) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    if (Adjacent(*G, x, y)) {
        printf("边已存在\n");
        return;
    }
    
    // 创建新的弧节点
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->tailvex = x;
    p->headvex = y;
    p->info = w;
    
    // 插入到弧尾顶点的出弧链表中
    p->tlink = G->xlist[x].firstout;
    G->xlist[x].firstout = p;
    
    // 插入到弧头顶点的入弧链表中
    p->hlink = G->xlist[y].firstin;
    G->xlist[y].firstin = p;
    
    G->arcnum++;
}

// 删除边
void RemoveEdge(OLGraph *G, int x, int y) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    // 从x的出弧链表中删除
    ArcNode *p = G->xlist[x].firstout;
    ArcNode *prev = NULL;
    while (p != NULL) {
        if (p->headvex == y) {
            if (prev == NULL) {
                G->xlist[x].firstout = p->tlink;
            } else {
                prev->tlink = p->tlink;
            }
            break;
        }
        prev = p;
        p = p->tlink;
    }
    
    // 从y的入弧链表中删除
    p = G->xlist[y].firstin;
    prev = NULL;
    while (p != NULL) {
        if (p->tailvex == x) {
            if (prev == NULL) {
                G->xlist[y].firstin = p->hlink;
            } else {
                prev->hlink = p->hlink;
            }
            free(p);
            G->arcnum--;
            return;
        }
        prev = p;
        p = p->hlink;
    }
    
    printf("边不存在\n");
}

// 获取第一个邻接顶点（出边）
int FirstNeighbor(OLGraph G, int x) {
    if (x < 0 || x >= G.vexnum) return -1;
    if (G.xlist[x].firstout != NULL) {
        return G.xlist[x].firstout->headvex;
    }
    return -1;
}

// 获取下一个邻接顶点（出边）
int NextNeighbor(OLGraph G, int x, int y) {
    if (x < 0 || x >= G.vexnum || y < 0 || y >= G.vexnum) return -1;
    
    ArcNode *p = G.xlist[x].firstout;
    while (p != NULL) {
        if (p->headvex == y && p->tlink != NULL) {
            return p->tlink->headvex;
        }
        p = p->tlink;
    }
    return -1;
}

// 获取边权值
EdgeType Get_edge_value(OLGraph G, int x, int y) {
    if (x < 0 || x >= G.vexnum || y < 0 || y >= G.vexnum) return INT_MAX;
    
    ArcNode *p = G.xlist[x].firstout;
    while (p != NULL) {
        if (p->headvex == y) {
            return p->info;
        }
        p = p->tlink;
    }
    return INT_MAX;
}

// 设置边权值
void Set_edge_value(OLGraph *G, int x, int y, EdgeType v) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) return;
    
    ArcNode *p = G->xlist[x].firstout;
    while (p != NULL) {
        if (p->headvex == y) {
            p->info = v;
            return;
        }
        p = p->tlink;
    }
}

// 图的遍历
bool visited[MAX_VERTEX_NUM];

void visit(VertexType v) {
    printf("%c ", v);
}

// 广度优先搜索
void BFS_OL(OLGraph G, int v) {
    Queue Q;
    InitQueue(&Q);
    visit(G.xlist[v].data);
    visited[v] = true;
    EnQueue(&Q, v);
    
    while (!QueueEmpty(&Q)) {
        int u;
        DeQueue(&Q, &u);
        
        // 遍历所有出边邻接点
        ArcNode *p = G.xlist[u].firstout;
        while (p != NULL) {
            int w = p->headvex;
            if (!visited[w]) {
                visit(G.xlist[w].data);
                visited[w] = true;
                EnQueue(&Q, w);
            }
            p = p->tlink;
        }
    }
}

void BFSTraverse_OL(OLGraph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])
            BFS_OL(G, i);
}

// 深度优先搜索
void DFS_OL(OLGraph G, int v) {
    visit(G.xlist[v].data);
    visited[v] = true;
    
    ArcNode *p = G.xlist[v].firstout;
    while (p != NULL) {
        int w = p->headvex;
        if (!visited[w])
            DFS_OL(G, w);
        p = p->tlink;
    }
}

void DFSTraverse_OL(OLGraph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS_OL(G, i);
}

// 打印十字链表结构
void PrintOLGraph(OLGraph G) {
    printf("\n十字链表结构:\n");
    for (int i = 0; i < G.vexnum; i++) {
        printf("顶点%c: ", G.xlist[i].data);
        
        printf("出边-> ");
        ArcNode *p = G.xlist[i].firstout;
        while (p != NULL) {
            printf("%c(%d) ", G.xlist[p->headvex].data, p->info);
            p = p->tlink;
        }
        
        printf(" | 入边-> ");
        p = G.xlist[i].firstin;
        while (p != NULL) {
            printf("%c(%d) ", G.xlist[p->tailvex].data, p->info);
            p = p->hlink;
        }
        printf("\n");
    }
}

int main() {
    OLGraph OLG;
    
    printf("创建十字链表图:\n");
    CreateOLGraph(&OLG);
    
    PrintOLGraph(OLG);
    
    printf("\n十字链表图的广度优先遍历:\n");
    BFSTraverse_OL(OLG);
    
    printf("\n十字链表图的深度优先遍历:\n");
    DFSTraverse_OL(OLG);
    
    // 测试基本操作
    printf("\n\n测试基本操作:\n");
    if (Adjacent(OLG, 0, 1)) {
        printf("顶点0和1相邻\n");
    }
    
    Neighbors(OLG, 0);
    
    printf("添加新边(0,2)权值为5:\n");
    AddEdge(&OLG, 0, 2, 5);
    PrintOLGraph(OLG);
    
    printf("删除边(0,1):\n");
    RemoveEdge(&OLG, 0, 1);
    PrintOLGraph(OLG);
    
    return 0;
}
