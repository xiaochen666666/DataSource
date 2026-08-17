#include <stdio.h> 
#include <stdlib.h>
#define MaxSize 50
#define true 1
#define false 0
typedef int ElemType;

/***
typedef struct Stack{
    ElemType data[MaxSize];
    int top;
}SqStack;

//初始化 
void InitStack(SqStack *S){
    S->top = -1;
}

//判栈空 
int StackEmpty(SqStack S){
    if(S.top == -1)
        return true;
    else
        return false;
}

//入栈
int PushStack(SqStack *S, ElemType x) {
    if(S->top == MaxSize - 1)
        return false;
    S->data[++S->top] = x;
    return true;	
}

//出栈
int PopStack(SqStack *S, ElemType *x) {
    if(S->top == -1)
        return false;
    *x = S->data[S->top--];
    return true;
}

//读栈顶元素
int GetTop(SqStack S, ElemType *x) {
    if(S.top == -1)
        return false;
    *x = S.data[S.top];
    return true;
}

// 打印栈
int PrintStack(SqStack S) {
    int i;
    if (S.top == -1) {
        printf("栈为空，无法打印！\n");
        return false;
    }
    printf("栈中的元素为：");
    for (i = S.top; i >= 0; i--) {
        printf("%d ", S.data[i]);
    }
    printf("\n");
    return true;
}

int main(){
    SqStack S;
    InitStack(&S);
    PushStack(&S, 10);
    PushStack(&S, 100);
    PushStack(&S, 1000);

    ElemType popped;
    if(PopStack(&S, &popped)) {
        printf("%d已出栈\n", popped);
    }

    ElemType top;
    if(GetTop(S, &top)) {
        printf("栈顶元素为: %d\n", top);
    }
    PrintStack(S);
    return 0;
}
***/

// 定义链栈节点结构体
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode;

// 定义链栈结构体
typedef struct {
    LinkNode *top;  // 栈顶指针
} LiStack;

// 初始化
int InitStack(LiStack *S) {
    S->top = NULL;  // 栈顶指针初始化为空
    return true;
}

// 判栈空
int StackEmpty(LiStack S) {
    if (S.top == NULL)
        return true;
    else
        return false;
}

// 入栈
int PushStack(LiStack *S, ElemType x) {
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    if (s == NULL) {
        printf("分配内存失败!\n");
        return false;
    }
    s->data = x;
    s->next = S->top;  // 新节点的 next 指向原栈顶
    S->top = s;  // 栈顶指针指向新节点
    return true;
}

// 出栈
int PopStack(LiStack *S, ElemType *x) {
    if (StackEmpty(*S))
        return false;
    LinkNode *p = S->top;  // 保存栈顶节点指针
    *x = p->data;  // 获取栈顶元素的值
    S->top = p->next;  // 栈顶指针指向下一个节点
    free(p);  // 释放原栈顶节点的内存
    return true;
}

// 读栈顶元素
int GetTop(LiStack S, ElemType *x) {
    if (StackEmpty(S))
        return false;
    *x = S.top->data;  // 获取栈顶元素的值
    return true;
}

// 打印栈
int PrintStack(LiStack S) {
    if (StackEmpty(S)) {
        printf("栈为空，无法打印！\n");
        return false;
    }
    LinkNode *p = S.top;
    printf("栈中的元素为：");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return true;
}

int main() {
    LiStack S;
    ElemType x;

    // 初始化栈
    InitStack(&S);

    // 入栈操作
    PushStack(&S, 10);
    PushStack(&S, 20);
    PushStack(&S, 30);

    // 打印栈
    PrintStack(S);

    // 读栈顶元素
    if (GetTop(S, &x)) {
        printf("栈顶元素为：%d\n", x);
    }

    // 出栈操作
    if (PopStack(&S, &x)) {
        printf("出栈元素为：%d\n", x);
    }

    // 再次打印栈
    PrintStack(S);

    return 0;
}
