#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

// 初始化链表
int InitList(LinkList *L) {
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL) {
		printf("分配内存失败!\n");
		exit(1);
	}
	(*L)->next = NULL;
	return true;
}

// 求表长（头节点不计入长度）
int Length(LinkList L) {
	int len = 0;
	LNode *p = L->next;
	while (p != NULL) {
		len++;
		p = p->next;
	}
	return len;
}

// 按序号查找元素（i从1开始）
LNode *GetElem(LinkList L, int i) {
	if (i < 1) return NULL;
	LNode *p = L->next;
	int j = 1;
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	return p;
}

// 按值查找元素
LNode *LocateElem(LinkList L, ElemType e) {
	LNode *p = L->next;
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;
}

// 插入元素到第i个位置
int ListInsert(LinkList L, int i, ElemType e) {
	if (i < 1) return false;
	LNode *p = L;
	int j = 0;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL) return false;
	LNode *s = (LNode *)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

// 删除第i个节点
int ListDelete(LinkList L, int i, ElemType *e) {
	if (i < 1) return false;
	LNode *p = L;
	int j = 0;
	while (p->next != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p->next == NULL) return false;
	LNode *q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	return true;
}

//头插法
/*
LinkList List_HeadInsert(LinkList *L) {
	LNode *s;
	int x;
	*L=(LNode*)malloc(sizeof(LNode));
	(*L)->next = NULL;
	scanf("%d",&x);
	while(x!=9999){
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		s->next=(*L)->next;
		(*L)->next=s;
		scanf("%d",&x);
	}
	return L;
}

//尾插法
LinkList List_TailInsert(LinkList *L) {
	int x;
	*L=(LNode*)malloc(sizeof(LNode));
	LNode *s,*r=L;
	(*L)->next = NULL;
	scanf("%d",&x);
	while(x!=9999){
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		r->next=s;
		r=s;
		scanf("%d",&x);
	}
	r->next=NULL;
	return L;
}
*/
int main() {
    LinkList L;
    InitList(&L);
    // 测试插入操作
    ListInsert(L, 1, 10); // 插入到第1个位置
    ListInsert(L, 2, 20); // 插入到第2个位置
    // 测试求表长
    printf("链表长度: %d\n", Length(L)); // 预期输出2
    // 测试按序号查找
    LNode *node = GetElem(L, 1);
    if (node != NULL) {
        printf("按序号查找结果: %d\n", node->data); // 预期输出10
    }
    // 测试按值查找
    node = LocateElem(L, 20);
    if (node != NULL) {
        printf("按值查找结果: %d\n", node->data); // 预期输出20
    }
    // 测试删除操作
    ElemType deleted;
    if (ListDelete(L, 1, &deleted)) {
        printf("删除元素: %d\n", deleted); // 预期输出10
    }
    printf("删除后链表长度: %d\n", Length(L)); // 预期输出1
    return 0;
}
//双链表
/***
typedef int ElemType;

// 定义双链表节点结构体
typedef struct DNode {
    ElemType data;
    struct DNode *prior;
    struct DNode *next;
} DNode, *DLinkList;

// 初始化双链表
int InitDList(DLinkList *L) {
    *L = (DNode *)malloc(sizeof(DNode));
    if (*L == NULL) {
        printf("分配内存失败!\n");
        return false;
    }
    (*L)->prior = NULL;
    (*L)->next = NULL;
    return true;
}

// 求双链表长度（头节点不计入长度）
int DLength(DLinkList L) {
    int len = 0;
    DNode *p = L->next;
    while (p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}

// 按序号查找元素（i 从 1 开始）
DNode *DGetElem(DLinkList L, int i) {
    if (i < 1) return NULL;
    DNode *p = L->next;
    int j = 1;
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找元素
DNode *DLocateElem(DLinkList L, ElemType e) {
    DNode *p = L->next;
    while (p != NULL && p->data != e) {
        p = p->next;
    }
    return p;
}

// 插入元素到第 i 个位置
int DListInsert(DLinkList L, int i, ElemType e) {
    if (i < 1) return false;
    DNode *p = L;
    int j = 0;
    while (p != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p == NULL) return false;
    DNode *s = (DNode *)malloc(sizeof(DNode));
    s->data = e;
    s->next = p->next;
    if (p->next != NULL) {
        p->next->prior = s;
    }
    s->prior = p;
    p->next = s;
    return true;
}

// 删除第 i 个节点
int DListDelete(DLinkList L, int i, ElemType *e) {
    if (i < 1) return false;
    DNode *p = L;
    int j = 0;
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p->next == NULL) return false;
    DNode *q = p->next;
    *e = q->data;
    p->next = q->next;
    if (q->next != NULL) {
        q->next->prior = p;
    }
    free(q);
    return true;
}

// 头插法创建双链表
DLinkList DList_HeadInsert(DLinkList *L) {
    DNode *s;
    int x;
    *L = (DNode *)malloc(sizeof(DNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
    scanf("%d", &x);
    while (x != 9999) {
        s = (DNode *)malloc(sizeof(DNode));
        s->data = x;
        s->next = (*L)->next;
        if ((*L)->next != NULL) {
            (*L)->next->prior = s;
        }
        s->prior = *L;
        (*L)->next = s;
        scanf("%d", &x);
    }
    return *L;
}

// 尾插法创建双链表
DLinkList DList_TailInsert(DLinkList *L) {
    int x;
    *L = (DNode *)malloc(sizeof(DNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
    DNode *s, *r = *L;
    scanf("%d", &x);
    while (x != 9999) {
        s = (DNode *)malloc(sizeof(DNode));
        s->data = x;
        r->next = s;
        s->prior = r;
        r = s;
        scanf("%d", &x);
    }
    r->next = NULL;
    return *L;
}

int main() {
    DLinkList L;
    InitDList(&L);

    // 测试尾插法创建双链表
    printf("请输入元素（输入 9999 结束）：\n");
    DList_TailInsert(&L);

    // 测试求表长
    printf("双链表长度: %d\n", DLength(L));

    // 测试按序号查找
    DNode *node = DGetElem(L, 1);
    if (node != NULL) {
        printf("按序号查找结果: %d\n", node->data);
    }

    // 测试按值查找
    node = DLocateElem(L, 20);
    if (node != NULL) {
        printf("按值查找结果: %d\n", node->data);
    }

    // 测试插入操作
    DListInsert(L, 2, 30);
    printf("插入元素后双链表长度: %d\n", DLength(L));

    // 测试删除操作
    ElemType deleted;
    if (DListDelete(L, 1, &deleted)) {
        printf("删除元素: %d\n", deleted);
    }
    printf("删除元素后双链表长度: %d\n", DLength(L));

    return 0;
}
***/
//循环链表
/***
// 定义循环链表节点结构体
typedef struct Node {
    int data;           // 节点存储的数据
    struct Node *next;  // 指向下一个节点的指针
} Node;

// 初始化循环链表
Node* initList() {
    Node *head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    head->next = head;  // 头节点的 next 指向自身，形成循环
    return head;
}

// 在链表尾部插入新节点
void insertNode(Node *head, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = data;
    Node *p = head;
    while (p->next != head) {
        p = p->next;
    }
    newNode->next = head;
    p->next = newNode;
}

// 删除指定值的节点
void deleteNode(Node *head, int data) {
    Node *p = head->next;
    Node *prev = head;
    while (p != head) {
        if (p->data == data) {
            prev->next = p->next;
            free(p);
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("未找到值为 %d 的节点！\n", data);
}

// 查找指定值的节点
Node* findNode(Node *head, int data) {
    Node *p = head->next;
    while (p != head) {
        if (p->data == data) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 遍历循环链表
void traverseList(Node *head) {
    Node *p = head->next;
    while (p != head) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 释放循环链表内存
void freeList(Node *head) {
    Node *p = head->next;
    Node *temp;
    while (p != head) {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
}

int main() {
    Node *list = initList();
    if (list == NULL) {
        return 1;
    }

    // 插入节点
    insertNode(list, 10);
    insertNode(list, 20);
    insertNode(list, 30);

    // 遍历链表
    printf("插入节点后的链表: ");
    traverseList(list);

    // 查找节点
    Node *found = findNode(list, 20);
    if (found != NULL) {
        printf("找到值为 20 的节点！\n");
    } else {
        printf("未找到值为 20 的节点！\n");
    }

    // 删除节点
    deleteNode(list, 20);
    printf("删除值为 20 的节点后的链表: ");
    traverseList(list);

    // 释放链表内存
    freeList(list);

    return 0;
}
***/
//循环双链表
/***
// 定义循环双链表节点结构体
typedef struct DNode {
    int data;  // 数据域
    struct DNode *prior;  // 指向前驱节点的指针
    struct DNode *next;   // 指向后继节点的指针
} DNode, *DLinkList;

// 初始化循环双链表
int InitList(DLinkList *L) {
    *L = (DNode *)malloc(sizeof(DNode));
    if (*L == NULL) {
        return 0;  // 内存分配失败
    }
    (*L)->next = *L;
    (*L)->prior = *L;
    return 1;
}

// 在第 i 个位置插入元素 e
int ListInsert(DLinkList *L, int i, int e) {
    if (i < 1) {
        return 0;
    }
    DNode *p = *L;
    int j = 0;
    while (p->next != *L && j < i - 1) {
        p = p->next;
        j++;
    }
    if (j != i - 1) {
        return 0;  // 插入位置不合法
    }
    DNode *s = (DNode *)malloc(sizeof(DNode));
    if (s == NULL) {
        return 0;  // 内存分配失败
    }
    s->data = e;
    s->next = p->next;
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return 1;
}

// 删除第 i 个位置的元素，并将其值赋给 e
int ListDelete(DLinkList *L, int i, int *e) {
    if (i < 1) {
        return 0;
    }
    DNode *p = (*L)->next;
    int j = 1;
    while (p != *L && j < i) {
        p = p->next;
        j++;
    }
    if (p == *L) {
        return 0;  // 删除位置不合法
    }
    *e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return 1;
}

// 查找值为 e 的节点，返回其位置
int LocateElem(DLinkList L, int e) {
    DNode *p = L->next;
    int i = 1;
    while (p != L) {
        if (p->data == e) {
            return i;
        }
        p = p->next;
        i++;
    }
    return 0;
}

// 遍历循环双链表
void TraverseList(DLinkList L) {
    DNode *p = L->next;
    while (p != L) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 释放循环双链表的内存
void DestroyList(DLinkList *L) {
    DNode *p = (*L)->next;
    DNode *q;
    while (p != *L) {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}

int main() {
    DLinkList L;
    int e;

    // 初始化循环双链表
    if (InitList(&L)) {
        printf("循环双链表初始化成功！\n");
    }

    // 插入元素
    ListInsert(&L, 1, 10);
    ListInsert(&L, 2, 20);
    ListInsert(&L, 3, 30);

    // 遍历链表
    printf("当前链表元素为: ");
    TraverseList(L);

    // 查找元素
    int pos = LocateElem(L, 20);
    if (pos) {
        printf("元素 20 的位置是: %d\n", pos);
    } else {
        printf("未找到元素 20\n");
    }

    // 删除元素
    if (ListDelete(&L, 2, &e)) {
        printf("删除的元素是: %d\n", e);
    }

    // 再次遍历链表
    printf("删除元素后链表元素为: ");
    TraverseList(L);

    // 释放链表内存
    DestroyList(&L);

    return 0;
}
***/
//静态链表

/*
// 定义静态链表节点
typedef struct {
    int data;  // 数据域
    int cur;   // 游标
} Component, StaticLinkList[MAXSIZE];

// 初始化静态链表
void InitList(StaticLinkList space) {
    int i;
    for (i = 0; i < MAXSIZE - 1; i++) {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;  // 最后一个元素的游标指向头节点
}

// 分配一个空闲节点
int Malloc_SLL(StaticLinkList space) {
    int i = space[0].cur;
    if (space[0].cur) {
        space[0].cur = space[i].cur;
    }
    return i;
}

// 释放一个节点
void Free_SLL(StaticLinkList space, int k) {
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

// 在第 i 个位置插入元素 e
int ListInsert(StaticLinkList space, int i, int e) {
    int j, k, l;
    k = MAXSIZE - 1;  // 指向头节点
    if (i < 1 || i > ListLength(space) + 1) {
        return 0;
    }
    j = Malloc_SLL(space);
    if (j) {
        space[j].data = e;
        for (l = 1; l <= i - 1; l++) {
            k = space[k].cur;
        }
        space[j].cur = space[k].cur;
        space[k].cur = j;
        return 1;
    }
    return 0;
}

// 删除第 i 个位置的元素
int ListDelete(StaticLinkList space, int i) {
    int j, k;
    if (i < 1 || i > ListLength(space)) {
        return 0;
    }
    k = MAXSIZE - 1;
    for (j = 1; j <= i - 1; j++) {
        k = space[k].cur;
    }
    j = space[k].cur;
    space[k].cur = space[j].cur;
    Free_SLL(space, j);
    return 1;
}

// 计算静态链表的长度
int ListLength(StaticLinkList space) {
    int j = 0;
    int i = space[MAXSIZE - 1].cur;
    while (i) {
        i = space[i].cur;
        j++;
    }
    return j;
}

// 打印静态链表
void PrintList(StaticLinkList space) {
    int i = space[MAXSIZE - 1].cur;
    while (i) {
        printf("%d ", space[i].data);
        i = space[i].cur;
    }
    printf("\n");
}

int main() {
    StaticLinkList space;
    InitList(space);

    // 插入元素
    ListInsert(space, 1, 10);
    ListInsert(space, 2, 20);
    ListInsert(space, 3, 30);

    // 打印链表
    printf("插入元素后的链表: ");
    PrintList(space);

    // 删除元素
    ListDelete(space, 2);

    // 打印链表
    printf("删除元素后的链表: ");
    PrintList(space);

    return 0;
}
***/
