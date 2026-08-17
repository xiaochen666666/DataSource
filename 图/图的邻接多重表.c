#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTEX_NUM 100  // 最大顶点数

typedef char VertexType;    // 顶点数据类型
typedef int EdgeType;       // 边权值类型

// 邻接多重表表示
typedef struct EdgeNode {
    int ivex, jvex;         // 该边依附的两个顶点位置
    struct EdgeNode *ilink; // 指向下一条依附于顶点ivex的边
    struct EdgeNode *jlink; // 指向下一条依附于顶点jvex的边
    EdgeType info;          // 边的权值
    bool mark;              // 标记位，用于遍历等操作
} EdgeNode;

typedef struct VexNode {
    VertexType data;        // 顶点信息
    EdgeNode *firstedge;    // 指向第一条依附该顶点的边
} VexNode;

typedef struct {
    VexNode adjmulist[MAX_VERTEX_NUM]; // 顶点表
    int vexnum, edgenum;               // 图的顶点数和边数
} AMLGraph;

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
int LocateVex(AMLGraph G, VertexType v) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (G.adjmulist[i].data == v) {
            return i;
        }
    }
    return -1;
}

// 创建邻接多重表图（无向图）
void CreateAMLGraph(AMLGraph *G) {
    int i, k;
    printf("输入顶点数和边数: ");
    scanf("%d %d", &G->vexnum, &G->edgenum);
    
    printf("输入顶点信息: ");
    for (i = 0; i < G->vexnum; i++) {
        scanf(" %c", &G->adjmulist[i].data);
        G->adjmulist[i].firstedge = NULL;
    }
    
    printf("输入边(vi,vj)及其权值:\n");
    for (k = 0; k < G->edgenum; k++) {
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
        
        if (i == j) {
            printf("不支持自环!\n");
            k--;
            continue;
        }
        
        // 创建新的边节点
        EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->ivex = i;
        p->jvex = j;
        p->info = w;
        p->mark = false;
        
        // 插入到顶点i的边链表中
        p->ilink = G->adjmulist[i].firstedge;
        G->adjmulist[i].firstedge = p;
        
        // 插入到顶点j的边链表中
        p->jlink = G->adjmulist[j].firstedge;
        G->adjmulist[j].firstedge = p;
    }
}

// 判断边是否存在
bool Adjacent(AMLGraph G, int x, int y) {
    EdgeNode *p = G.adjmulist[x].firstedge;
    while (p != NULL) {
        if ((p->ivex == x && p->jvex == y) || (p->ivex == y && p->jvex == x)) {
            return true;
        }
        if (p->ivex == x) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
    return false;
}

// 获取顶点x的所有邻接顶点
void Neighbors(AMLGraph G, int x) {
    printf("顶点%c的邻接顶点: ", G.adjmulist[x].data);
    
    EdgeNode *p = G.adjmulist[x].firstedge;
    while (p != NULL) {
        if (p->ivex == x) {
            printf("%c ", G.adjmulist[p->jvex].data);
            p = p->ilink;
        } else {
            printf("%c ", G.adjmulist[p->ivex].data);
            p = p->jlink;
        }
    }
    printf("\n");
}

// 插入新顶点
void InsertVertex(AMLGraph *G, VertexType x) {
    if (G->vexnum >= MAX_VERTEX_NUM) {
        printf("图已满，无法插入新顶点\n");
        return;
    }
    G->adjmulist[G->vexnum].data = x;
    G->adjmulist[G->vexnum].firstedge = NULL;
    G->vexnum++;
}

// 删除顶点
void DeleteVertex(AMLGraph *G, int x) {
    if (x < 0 || x >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    // 删除所有与顶点x相关的边
    EdgeNode *p = G->adjmulist[x].firstedge;
    while (p != NULL) {
        EdgeNode *temp = p;
        
        // 确定另一个顶点
        int other_vex = (p->ivex == x) ? p->jvex : p->ivex;
        
        // 从另一个顶点的边链表中删除这条边
        EdgeNode *q = G->adjmulist[other_vex].firstedge;
        EdgeNode *prev = NULL;
        while (q != NULL) {
            if (q == temp) {
                if (prev == NULL) {
                    if (q->ivex == other_vex) {
                        G->adjmulist[other_vex].firstedge = q->ilink;
                    } else {
                        G->adjmulist[other_vex].firstedge = q->jlink;
                    }
                } else {
                    if (prev->ivex == other_vex && q->ivex == other_vex) {
                        prev->ilink = (q->ivex == other_vex) ? q->ilink : q->jlink;
                    } else if (prev->jvex == other_vex && q->jvex == other_vex) {
                        prev->jlink = (q->ivex == other_vex) ? q->ilink : q->jlink;
                    }
                }
                break;
            }
            prev = q;
            if (q->ivex == other_vex) {
                q = q->ilink;
            } else {
                q = q->jlink;
            }
        }
        
        // 移动到下一条边
        if (temp->ivex == x) {
            p = temp->ilink;
        } else {
            p = temp->jlink;
        }
        free(temp);
        G->edgenum--;
    }
    
    // 移动顶点表中的顶点
    for (int i = x; i < G->vexnum - 1; i++) {
        G->adjmulist[i] = G->adjmulist[i + 1];
    }
    G->vexnum--;
    
    // 更新所有边中的顶点索引
    for (int i = 0; i < G->vexnum; i++) {
        EdgeNode *edge = G->adjmulist[i].firstedge;
        while (edge != NULL) {
            if (edge->ivex > x) edge->ivex--;
            if (edge->jvex > x) edge->jvex--;
            if (edge->ivex == i) {
                edge = edge->ilink;
            } else {
                edge = edge->jlink;
            }
        }
    }
}

// 添加边
void AddEdge(AMLGraph *G, int x, int y, EdgeType w) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    if (x == y) {
        printf("不支持自环\n");
        return;
    }
    
    if (Adjacent(*G, x, y)) {
        printf("边已存在\n");
        return;
    }
    
    // 创建新的边节点
    EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
    p->ivex = x;
    p->jvex = y;
    p->info = w;
    p->mark = false;
    
    // 插入到顶点x的边链表中
    p->ilink = G->adjmulist[x].firstedge;
    G->adjmulist[x].firstedge = p;
    
    // 插入到顶点y的边链表中
    p->jlink = G->adjmulist[y].firstedge;
    G->adjmulist[y].firstedge = p;
    
    G->edgenum++;
}

// 删除边
void RemoveEdge(AMLGraph *G, int x, int y) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) {
        printf("顶点不存在\n");
        return;
    }
    
    // 从顶点x的边链表中删除
    EdgeNode *p = G->adjmulist[x].firstedge;
    EdgeNode *prev_x = NULL;
    while (p != NULL) {
        if ((p->ivex == x && p->jvex == y) || (p->ivex == y && p->jvex == x)) {
            // 从x的链表中移除
            if (prev_x == NULL) {
                if (p->ivex == x) {
                    G->adjmulist[x].firstedge = p->ilink;
                } else {
                    G->adjmulist[x].firstedge = p->jlink;
                }
            } else {
                if (prev_x->ivex == x && p->ivex == x) {
                    prev_x->ilink = (p->ivex == x) ? p->ilink : p->jlink;
                } else if (prev_x->jvex == x && p->jvex == x) {
                    prev_x->jlink = (p->ivex == x) ? p->ilink : p->jlink;
                }
            }
            break;
        }
        prev_x = p;
        if (p->ivex == x) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
    
    // 从顶点y的边链表中删除
    p = G->adjmulist[y].firstedge;
    EdgeNode *prev_y = NULL;
    while (p != NULL) {
        if ((p->ivex == x && p->jvex == y) || (p->ivex == y && p->jvex == x)) {
            // 从y的链表中移除
            if (prev_y == NULL) {
                if (p->ivex == y) {
                    G->adjmulist[y].firstedge = p->ilink;
                } else {
                    G->adjmulist[y].firstedge = p->jlink;
                }
            } else {
                if (prev_y->ivex == y && p->ivex == y) {
                    prev_y->ilink = (p->ivex == y) ? p->ilink : p->jlink;
                } else if (prev_y->jvex == y && p->jvex == y) {
                    prev_y->jlink = (p->ivex == y) ? p->ilink : p->jlink;
                }
            }
            free(p);
            G->edgenum--;
            return;
        }
        prev_y = p;
        if (p->ivex == y) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
    
    printf("边不存在\n");
}

// 获取第一个邻接顶点
int FirstNeighbor(AMLGraph G, int x) {
    if (x < 0 || x >= G.vexnum) return -1;
    if (G.adjmulist[x].firstedge != NULL) {
        if (G.adjmulist[x].firstedge->ivex == x) {
            return G.adjmulist[x].firstedge->jvex;
        } else {
            return G.adjmulist[x].firstedge->ivex;
        }
    }
    return -1;
}

// 获取下一个邻接顶点
int NextNeighbor(AMLGraph G, int x, int y) {
    if (x < 0 || x >= G.vexnum || y < 0 || y >= G.vexnum) return -1;
    
    EdgeNode *p = G.adjmulist[x].firstedge;
    while (p != NULL) {
        int current_other = (p->ivex == x) ? p->jvex : p->ivex;
        
        if (current_other == y) {
            // 找到当前边，找下一条边
            EdgeNode *next;
            if (p->ivex == x) {
                next = p->ilink;
            } else {
                next = p->jlink;
            }
            
            if (next != NULL) {
                return (next->ivex == x) ? next->jvex : next->ivex;
            } else {
                return -1;
            }
        }
        
        if (p->ivex == x) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
    return -1;
}

// 获取边权值
EdgeType Get_edge_value(AMLGraph G, int x, int y) {
    if (x < 0 || x >= G.vexnum || y < 0 || y >= G.vexnum) return INT_MAX;
    
    EdgeNode *p = G.adjmulist[x].firstedge;
    while (p != NULL) {
        if ((p->ivex == x && p->jvex == y) || (p->ivex == y && p->jvex == x)) {
            return p->info;
        }
        if (p->ivex == x) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
    return INT_MAX;
}

// 设置边权值
void Set_edge_value(AMLGraph *G, int x, int y, EdgeType v) {
    if (x < 0 || x >= G->vexnum || y < 0 || y >= G->vexnum) return;
    
    EdgeNode *p = G->adjmulist[x].firstedge;
    while (p != NULL) {
        if ((p->ivex == x && p->jvex == y) || (p->ivex == y && p->jvex == x)) {
            p->info = v;
            return;
        }
        if (p->ivex == x) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
}

// 图的遍历
bool visited[MAX_VERTEX_NUM];

void visit(VertexType v) {
    printf("%c ", v);
}

// 重置所有边的标记位
void ResetEdgeMarks(AMLGraph *G) {
    for (int i = 0; i < G->vexnum; i++) {
        EdgeNode *p = G->adjmulist[i].firstedge;
        while (p != NULL) {
            p->mark = false;
            if (p->ivex == i) {
                p = p->ilink;
            } else {
                p = p->jlink;
            }
        }
    }
}

// 广度优先搜索
void BFS_AML(AMLGraph G, int v) {
    Queue Q;
    InitQueue(&Q);
    visit(G.adjmulist[v].data);
    visited[v] = true;
    EnQueue(&Q, v);
    
    while (!QueueEmpty(&Q)) {
        int u;
        DeQueue(&Q, &u);
        
        EdgeNode *p = G.adjmulist[u].firstedge;
        while (p != NULL) {
            int w = (p->ivex == u) ? p->jvex : p->ivex;
            if (!visited[w]) {
                visit(G.adjmulist[w].data);
                visited[w] = true;
                EnQueue(&Q, w);
            }
            if (p->ivex == u) {
                p = p->ilink;
            } else {
                p = p->jlink;
            }
        }
    }
}

void BFSTraverse_AML(AMLGraph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])
            BFS_AML(G, i);
}

// 深度优先搜索
void DFS_AML(AMLGraph G, int v) {
    visit(G.adjmulist[v].data);
    visited[v] = true;
    
    EdgeNode *p = G.adjmulist[v].firstedge;
    while (p != NULL) {
        int w = (p->ivex == v) ? p->jvex : p->ivex;
        if (!visited[w])
            DFS_AML(G, w);
        if (p->ivex == v) {
            p = p->ilink;
        } else {
            p = p->jlink;
        }
    }
}

void DFSTraverse_AML(AMLGraph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS_AML(G, i);
}

// 打印邻接多重表结构
void PrintAMLGraph(AMLGraph G) {
    printf("\n邻接多重表结构:\n");
    for (int i = 0; i < G.vexnum; i++) {
        printf("顶点%c: ", G.adjmulist[i].data);
        
        EdgeNode *p = G.adjmulist[i].firstedge;
        while (p != NULL) {
            if (p->ivex == i) {
                printf("%c(%d) ", G.adjmulist[p->jvex].data, p->info);
                p = p->ilink;
            } else {
                printf("%c(%d) ", G.adjmulist[p->ivex].data, p->info);
                p = p->jlink;
            }
        }
        printf("\n");
    }
}

int main() {
    AMLGraph AMLG;
    
    printf("创建邻接多重表图:\n");
    CreateAMLGraph(&AMLG);
    
    PrintAMLGraph(AMLG);
    
    printf("\n邻接多重表图的广度优先遍历:\n");
    BFSTraverse_AML(AMLG);
    
    printf("\n邻接多重表图的深度优先遍历:\n");
    DFSTraverse_AML(AMLG);
    
    // 测试基本操作
    printf("\n\n测试基本操作:\n");
    if (Adjacent(AMLG, 0, 1)) {
        printf("顶点0和1相邻\n");
    }
    
    Neighbors(AMLG, 0);
    
    printf("添加新边(0,2)权值为5:\n");
    AddEdge(&AMLG, 0, 2, 5);
    PrintAMLGraph(AMLG);
    
    printf("删除边(0,1):\n");
    RemoveEdge(&AMLG, 0, 1);
    PrintAMLGraph(AMLG);
    
    return 0;
}
