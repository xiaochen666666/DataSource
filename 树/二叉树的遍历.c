#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 二叉树结点定义
typedef struct BiTNode {
    int data;                   // 结点数据
    struct BiTNode *lchild;     // 左孩子指针
    struct BiTNode *rchild;     // 右孩子指针
} BiTNode, *BiTree;

// 队列结构用于层序遍历
typedef struct {
    BiTree data[MAX_SIZE];
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue *Q) {
    Q->front = Q->rear = 0;
}

// 判断队列是否为空
int IsQueueEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

// 入队
void EnQueue(Queue *Q, BiTree node) {
    if ((Q->rear + 1) % MAX_SIZE == Q->front) {
        printf("Queue is full!\n");
        return;
    }
    Q->data[Q->rear] = node;
    Q->rear = (Q->rear + 1) % MAX_SIZE;
}

// 出队
BiTree DeQueue(Queue *Q) {
    if (IsQueueEmpty(Q)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    BiTree node = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX_SIZE;
    return node;
}

// 初始化空二叉树
void InitBiTree(BiTree *T) {
    *T = NULL;
}

// 创建新结点
BiTNode* CreateNode(int value) {
    BiTNode *newNode = (BiTNode*)malloc(sizeof(BiTNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// 递归插入结点（按值大小插入，左小右大）
void InsertNode(BiTree *T, int value) {
    if (*T == NULL) {
        *T = CreateNode(value);
    } else if (value < (*T)->data) {
        InsertNode(&(*T)->lchild, value);
    } else {
        InsertNode(&(*T)->rchild, value);
    }
}

// 先序遍历
void PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%d ", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 中序遍历
void InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild);
        printf("%d ", T->data);
        InOrderTraverse(T->rchild);
    }
}

// 后序遍历
void PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%d ", T->data);
    }
}

// 层序遍历
void LevelOrderTraverse(BiTree T) {
    if (T == NULL) return;
    
    Queue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);
    
    printf("LevelOrder: ");
    while (!IsQueueEmpty(&Q)) {
        BiTree current = DeQueue(&Q);
        printf("%d ", current->data);
        
        if (current->lchild) {
            EnQueue(&Q, current->lchild);
        }
        if (current->rchild) {
            EnQueue(&Q, current->rchild);
        }
    }
    printf("\n");
}

// 计算树深度
int TreeDepth(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int leftDepth = TreeDepth(T->lchild);
        int rightDepth = TreeDepth(T->rchild);
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

// 查找结点
BiTNode* SearchNode(BiTree T, int key) {
    if (T == NULL) return NULL;
    if (T->data == key) return T;
    if (key < T->data) 
        return SearchNode(T->lchild, key);
    else 
        return SearchNode(T->rchild, key);
}

// 销毁二叉树
void DestroyBiTree(BiTree *T) {
    if (*T) {
        DestroyBiTree(&(*T)->lchild);
        DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
}

int main() {
    BiTree root;
    InitBiTree(&root);
    
    // 构建二叉树
    InsertNode(&root, 5);
    InsertNode(&root, 3);
    InsertNode(&root, 7);
    InsertNode(&root, 2);
    InsertNode(&root, 4);
    InsertNode(&root, 6);
    InsertNode(&root, 8);
    
    // 遍历测试
    printf("PreOrder: ");
    PreOrderTraverse(root);
    printf("\n");
    
    printf("InOrder: ");
    InOrderTraverse(root);
    printf("\n");
    
    printf("PostOrder: ");
    PostOrderTraverse(root);
    printf("\n");
    
    // 层序遍历测试
    LevelOrderTraverse(root);
    
    // 深度测试
    printf("Tree Depth: %d\n", TreeDepth(root));
    
    // 查找测试
    int searchKey1 = 4;
    int searchKey2 = 1;
    BiTNode *found1 = SearchNode(root, searchKey1);
    BiTNode *found2 = SearchNode(root, searchKey2);
    if (found1) {
        printf("Found %d in the tree\n", searchKey1);
    } else {
        printf("%d not found in the tree\n", searchKey1);
    }
    if (found2) {
        printf("Found %d in the tree\n", searchKey2);
    } else {
        printf("%d not found in the tree\n", searchKey2);
    }
    // 销毁树
    DestroyBiTree(&root);
    
    return 0;
}
