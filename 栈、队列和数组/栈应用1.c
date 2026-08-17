#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/***
栈应用:(括号匹配)
***/ 
 
typedef struct LinkNode {
    char data;
    struct LinkNode *next;
} LinkNode;

// 定义链栈结构体
typedef struct {
    LinkNode *top;  // 栈顶指针
} LiStack;



bool InitStack(LiStack *S);
bool StackEmpty(LiStack S);
bool PushStack(LiStack *S, char x);
bool PopStack(LiStack *S, char *x);


//算法实现
bool bracketCheck(char str[] , int length){
    LiStack S;
    int i;
    InitStack(&S);
    for(i=0;i<length;i++){
        if(str[i]=='('||str[i]=='['||str[i]=='{'){
            PushStack(&S,str[i]);
        }else{
            if(StackEmpty(S))
                return false;
                
            char topElem;
            PopStack(&S, &topElem); //传入 topElem 的地址
            if(str[i]==')' && topElem!='(')
                return false;
            if(str[i]==']' && topElem!='[')
                return false;
            if(str[i]=='}' && topElem!='{')
                return false;
        }
    }
    return StackEmpty(S);
}

// 初始化
bool InitStack(LiStack *S) {
    S->top = NULL;  // 栈顶指针初始化为空
    return true;
}

// 判栈空
bool StackEmpty(LiStack S) { 
    return S.top == NULL;
}

// 入栈
bool PushStack(LiStack *S, char x) {
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
bool PopStack(LiStack *S, char *x) {
    if (StackEmpty(*S))
        return false;
    LinkNode *p = S->top;  // 保存栈顶节点指针
    *x = p->data;  // 获取栈顶元素的值
    S->top = p->next;  // 栈顶指针指向下一个节点
    free(p);  // 释放原栈顶节点的内存
    return true;
}

int main() {
    char str[100]; // 定义一个大小为 100 的字符数组
    printf("请输入字符串:\n");
    // 使用 fgets 读取包含空格的字符串
    fgets(str, sizeof(str), stdin); 
    int length = strlen(str);
    // 处理掉换行符
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
        length--;
    }
    if (bracketCheck(str, length)) {
        printf("括号匹配成功！\n");
    } else {
        printf("括号匹配失败！\n");
    }
    return 0;
}
