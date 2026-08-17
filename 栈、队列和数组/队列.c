#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#define MaxSize 50
 
/***
typedef int ElemType; 

typedef struct {
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;

// 初始化
void InitQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
}

// 判队空
bool isEmpty(SqQueue Q) {
    return Q.rear == Q.front;
}

// 入队
bool EnQueue(SqQueue *Q, ElemType x) {
    if ((Q->rear + 1) % MaxSize == Q->front)
        return false;
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MaxSize;
    return true;
}

// 出队
bool DeQueue(SqQueue *Q, ElemType *x) {
    if (Q->rear == Q->front)
        return false;
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MaxSize;
    return true;
}

// 读队首元素
bool GetHead(SqQueue Q, ElemType *x) {
    if (Q.rear == Q.front)
        return false;
    *x = Q.data[Q.front];
    return true;
}

int main() {
    SqQueue Q;
    int x, y;
    InitQueue(&Q);  // 修正函数调用
    EnQueue(&Q, 10);
    EnQueue(&Q, 100);
    EnQueue(&Q, 1000);
    if (GetHead(Q, &x))  // 使用指针传递参数
        printf("队首元素是%d\n", x);
    if (DeQueue(&Q, &y))  // 使用指针传递参数
        printf("出队元素是%d\n", y);
    if (GetHead(Q, &x))  // 使用指针传递参数
        printf("队首元素是%d\n", x);
    if (DeQueue(&Q, &y))  // 使用指针传递参数
        printf("出队元素是%d\n", y);
    if (GetHead(Q, &x))  // 使用指针传递参数
        printf("队首元素是%d\n", x);
    return 0;
}
***/
/***
typedef struct LinkNode{
	int data;
	struct LinkNode *next;
}LinkNode; 

typedef struct{
	LinkNode *front,*rear;
}LinkQueue;

//初始化
void Init(LinkQueue *Q) {
	Q->front = Q->rear = (LinkNode*)malloc(sizeof(LinkNode));
	if (Q->front == NULL) {
    	printf("内存分配失败！\n");
        exit(1);
    }
	Q->front->next = NULL;
}

//判队空 
bool isEmpty(LinkQueue Q){
	if(Q.rear==Q.front)
		return true;
	else
		return false;
}

//入队
bool En(LinkQueue *Q,int x) {
    LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = x;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
}

//出队
bool De(LinkQueue *Q,int *x){
	if(Q->rear==Q->front)
		return false;
	LinkNode *p = Q->front->next;
	*x = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return true;
} 

//读队首元素
bool GetHead(LinkQueue *Q,int *x) {
	if(Q->rear==Q->front)
		return false;
	*x = Q->front->next->data;
	return true;
}

int main(){
	LinkQueue Q;
	int x,y;
	Init(&Q);
	En(&Q,10);
	En(&Q,100);
	En(&Q,1000);
	if (GetHead(&Q, &x))
        printf("队首元素是%d\n", x);
    if (De(&Q, &y))
        printf("出队元素是%d\n", y);
    if (GetHead(&Q, &x))
        printf("队首元素是%d\n", x);
    if (De(&Q, &y))
        printf("出队元素是%d\n", y);
    if (GetHead(&Q, &x)) 
        printf("队首元素是%d\n", x);
    return 0;
	
}
***/


// 定义双端队列的节点结构体
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// 定义双端队列结构体
typedef struct {
    Node *front;
    Node *rear;
    int size;
} Deque;

// 初始化双端队列
void initDeque(Deque *deque) {
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
}

// 判断双端队列是否为空
bool isEmpty(Deque *deque) {
    return deque->size == 0;
}

// 在双端队列的前端插入元素
void insertFront(Deque *deque, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return;
    }
    newNode->data = value;
    newNode->prev = NULL;
    if (isEmpty(deque)) {
        newNode->next = NULL;
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
    deque->size++;
}

// 在双端队列的后端插入元素
void insertRear(Deque *deque, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    if (isEmpty(deque)) {
        newNode->prev = NULL;
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
    deque->size++;
}

// 从双端队列的前端删除元素
int deleteFront(Deque *deque) {
    if (isEmpty(deque)) {
        printf("双端队列为空，无法删除\n");
        return -1;
    }
    Node *temp = deque->front;
    int value = temp->data;
    if (deque->front == deque->rear) {
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        deque->front = deque->front->next;
        deque->front->prev = NULL;
    }
    free(temp);
    deque->size--;
    return value;
}

// 从双端队列的后端删除元素
int deleteRear(Deque *deque) {
    if (isEmpty(deque)) {
        printf("双端队列为空，无法删除\n");
        return -1;
    }
    Node *temp = deque->rear;
    int value = temp->data;
    if (deque->front == deque->rear) {
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        deque->rear = deque->rear->prev;
        deque->rear->next = NULL;
    }
    free(temp);
    deque->size--;
    return value;
}

// 获取双端队列的前端元素
int getFront(Deque *deque) {
    if (isEmpty(deque)) {
        printf("双端队列为空，无前端元素\n");
        return -1;
    }
    return deque->front->data;
}

// 获取双端队列的后端元素
int getRear(Deque *deque) {
    if (isEmpty(deque)) {
        printf("双端队列为空，无后端元素\n");
        return -1;
    }
    return deque->rear->data;
}

// 打印双端队列的元素
void printDeque(Deque *deque) {
    if (isEmpty(deque)) {
        printf("双端队列为空\n");
        return;
    }
    Node *current = deque->front;
    printf("双端队列元素: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 释放双端队列的内存
void freeDeque(Deque *deque) {
    while (!isEmpty(deque)) {
        deleteFront(deque);
    }
}

int main() {
    Deque deque;
    initDeque(&deque);

    insertFront(&deque, 10);
    insertRear(&deque, 20);
    insertFront(&deque, 5);

    printDeque(&deque);

    printf("前端元素: %d\n", getFront(&deque));
    printf("后端元素: %d\n", getRear(&deque));

    printf("删除前端元素: %d\n", deleteFront(&deque));
    printDeque(&deque);

    printf("删除后端元素: %d\n", deleteRear(&deque));
    printDeque(&deque);

    freeDeque(&deque);
    return 0;
}
