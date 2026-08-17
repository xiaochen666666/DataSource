#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXLEN 255

typedef struct{
    char ch[MAXLEN];
    int length;
}SString;

// 赋值
bool StrAssign(SString *T, const char *chars) {
    int len = strlen(chars);
    if (len > MAXLEN) {
        return false;
    }
    strcpy(T->ch, chars);
    T->length = len;
    return true;
}

// 判空
bool StrEmpty(SString S) {
    return S.length == 0;
} 

// 复制
bool StrCopy(SString *T, SString S) {
    strcpy(T->ch, S.ch);
    T->length = S.length;
    return true;
}

// 比较
int StrCompare(SString S, SString T) {
    return strcmp(S.ch, T.ch);
}

// 求串长
int StrLength(SString S) {
    return S.length;
}

// 求子串
bool SubString(SString *Sub, SString S, int pos, int len) {
	int i; 
    if (pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length) {
        return false;
    }
    for ( i = 0; i < len; i++) {
        Sub->ch[i] = S.ch[pos - 1 + i];
    }
    Sub->ch[len] = '\0';
    Sub->length = len;
    return true;
}

// 串连接
bool Concat(SString *T, SString S1, SString S2) {
    if (S1.length + S2.length > MAXLEN) {
        return false;
    }
    strcpy(T->ch, S1.ch);
    strcat(T->ch, S2.ch);
    T->length = S1.length + S2.length;
    return true;
}

// 定位
int Index(SString S, SString T) {
    int i = 0, j = 0;
    while (i < S.length && j < T.length) {
        if (S.ch[i] == T.ch[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == T.length) {
        return i - j + 1;
    }
    return 0;
}

// 清空串
bool ClearString(SString *S) {
    S->length = 0;
    S->ch[0] = '\0';
    return true;
}

// 销毁串 
bool DestroyString(SString *S) {
    // 对于定长顺序存储的串，无需额外操作，清空即可
    return ClearString(S);
}

int main() {
    SString s1, s2, sub;
    StrAssign(&s1, "hello");
    StrAssign(&s2, "world");
    printf("s1 length: %d\n", StrLength(s1));
    printf("s2 length: %d\n", StrLength(s2));
    if (Concat(&sub, s1, s2)) {
        printf("Concatenated string: %s\n", sub.ch);
    }
    int pos = Index(sub, s2);
    if (pos > 0) {
        printf("T found at position: %d\n", pos);
    } else {
        printf("T not found\n");
    }
    return 0;
}
/***
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 修改字符串结构体
typedef struct {
    char *ch;    // 改为指针，用于动态分配
    int length;
} SString;

// 初始化字符串
bool StrInit(SString *S) {
    S->ch = NULL;
    S->length = 0;
    return true;
}

// 赋值函数
bool StrAssign(SString *T, const char *chars) {
    int len = strlen(chars);
    // 释放原有内存
    if (T->ch != NULL) {
        free(T->ch);
    }
    // 分配新内存
    T->ch = (char *)malloc((len + 1) * sizeof(char));
    if (T->ch == NULL) {
        return false;
    }
    strcpy(T->ch, chars);
    T->length = len;
    return true;
}

// 判空
bool StrEmpty(SString S) {
    return S.length == 0;
}

// 复制函数
bool StrCopy(SString *T, SString S) {
    if (T->ch != NULL) {
        free(T->ch);
    }
    T->ch = (char *)malloc((S.length + 1) * sizeof(char));
    if (T->ch == NULL) {
        return false;
    }
    strcpy(T->ch, S.ch);
    T->length = S.length;
    return true;
}

// 比较函数
int StrCompare(SString S, SString T) {
    return strcmp(S.ch, T.ch);
}

// 获取长度
int StrLength(SString S) {
    return S.length;
}

// 获取子串
bool SubString(SString *Sub, SString S, int pos, int len) {
    if (pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length) {
        return false;
    }
    if (Sub->ch != NULL) {
        free(Sub->ch);
    }
    Sub->ch = (char *)malloc((len + 1) * sizeof(char));
    if (Sub->ch == NULL) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        Sub->ch[i] = S.ch[pos - 1 + i];
    }
    Sub->ch[len] = '\0';
    Sub->length = len;
    return true;
}

// 连接函数
bool Concat(SString *T, SString S1, SString S2) {
    if (T->ch != NULL) {
        free(T->ch);
    }
    T->ch = (char *)malloc((S1.length + S2.length + 1) * sizeof(char));
    if (T->ch == NULL) {
        return false;
    }
    strcpy(T->ch, S1.ch);
    strcat(T->ch, S2.ch);
    T->length = S1.length + S2.length;
    return true;
}

// 查找子串位置
int Index(SString S, SString T) {
    int i = 0, j = 0;
    while (i < S.length && j < T.length) {
        if (S.ch[i] == T.ch[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == T.length) {
        return i - j + 1;
    }
    return 0;
}

// 清空字符串
bool ClearString(SString *S) {
    if (S->ch != NULL) {
        free(S->ch);
        S->ch = NULL;
    }
    S->length = 0;
    return true;
}

// 销毁字符串
bool DestroyString(SString *S) {
    return ClearString(S);
}

int main() {
    SString s1, s2, sub;
    StrInit(&s1);
    StrInit(&s2);
    StrInit(&sub);
    
    StrAssign(&s1, "hello");
    StrAssign(&s2, "world");
    
    printf("s1 length: %d\n", StrLength(s1));
    printf("s2 length: %d\n", StrLength(s2));
    
    if (Concat(&sub, s1, s2)) {
        printf("Concatenated string: %s\n", sub.ch);
    }
    
    int pos = Index(sub, s2);
    if (pos > 0) {
        printf("T found at position: %d\n", pos);
    } else {
        printf("T not found\n");
    }
    
    // 使用完毕后需要销毁
    DestroyString(&s1);
    DestroyString(&s2);
    DestroyString(&sub);
    
    return 0;
}
***/
/***
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 定义链表节点
typedef struct StringNode {
    char ch;
    struct StringNode *next;
} StringNode;

// 定义字符串结构
typedef struct {
    StringNode *head;
    int length;
} SString;

// 初始化字符串
bool StrInit(SString *S) {
    S->head = NULL;
    S->length = 0;
    return true;
}

// 赋值函数
bool StrAssign(SString *T, const char *chars) {
    int len = strlen(chars);
    // 释放原有链表
    StringNode *p = T->head;
    while (p != NULL) {
        StringNode *temp = p;
        p = p->next;
        free(temp);
    }
    
    // 创建新链表
    StringNode *tail = NULL;
    for (int i = 0; i < len; i++) {
        StringNode *node = (StringNode *)malloc(sizeof(StringNode));
        if (node == NULL) {
            return false;
        }
        node->ch = chars[i];
        node->next = NULL;
        
        if (tail == NULL) {
            T->head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    T->length = len;
    return true;
}

// 判空
bool StrEmpty(SString S) {
    return S.length == 0;
}

// 复制函数
bool StrCopy(SString *T, SString S) {
    // 释放T原有链表
    StringNode *p = T->head;
    while (p != NULL) {
        StringNode *temp = p;
        p = p->next;
        free(temp);
    }
    
    // 复制S
    StringNode *tail = NULL;
    p = S.head;
    while (p != NULL) {
        StringNode *node = (StringNode *)malloc(sizeof(StringNode));
        if (node == NULL) {
            return false;
        }
        node->ch = p->ch;
        node->next = NULL;
        
        if (tail == NULL) {
            T->head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        p = p->next;
    }
    T->length = S.length;
    return true;
}

// 比较函数
int StrCompare(SString S, SString T) {
    StringNode *p1 = S.head, *p2 = T.head;
    while (p1 != NULL && p2 != NULL) {
        if (p1->ch != p2->ch) {
            return p1->ch - p2->ch;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    if (p1 == NULL && p2 == NULL) return 0;
    return (p1 == NULL) ? -1 : 1;
}

// 获取长度
int StrLength(SString S) {
    return S.length;
}

// 获取子串
bool SubString(SString *Sub, SString S, int pos, int len) {
    if (pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length) {
        return false;
    }
    // 释放Sub原有链表
    StringNode *p = Sub->head;
    while (p != NULL) {
        StringNode *temp = p;
        p = p->next;
        free(temp);
    }
    
    // 创建新链表
    StringNode *tail = NULL;
    p = S.head;
    for (int i = 1; i < pos; i++) {
        p = p->next;
    }
    for (int i = 0; i < len; i++) {
        StringNode *node = (StringNode *)malloc(sizeof(StringNode));
        if (node == NULL) {
            return false;
        }
        node->ch = p->ch;
        node->next = NULL;
        
        if (tail == NULL) {
            Sub->head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        p = p->next;
    }
    Sub->length = len;
    return true;
}

// 连接函数
bool Concat(SString *T, SString S1, SString S2) {
    // 释放T原有链表
    StringNode *p = T->head;
    while (p != NULL) {
        StringNode *temp = p;
        p = p->next;
        free(temp);
    }
    
    // 复制S1
    StringNode *tail = NULL;
    p = S1.head;
    while (p != NULL) {
        StringNode *node = (StringNode *)malloc(sizeof(StringNode));
        if (node == NULL) {
            return false;
        }
        node->ch = p->ch;
        node->next = NULL;
        
        if (tail == NULL) {
            T->head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        p = p->next;
    }
    
    // 复制S2
    p = S2.head;
    while (p != NULL) {
        StringNode *node = (StringNode *)malloc(sizeof(StringNode));
        if (node == NULL) {
            return false;
        }
        node->ch = p->ch;
        node->next = NULL;
        
        if (tail == NULL) {
            T->head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        p = p->next;
    }
    
    T->length = S1.length + S2.length;
    return true;
}

// 查找子串位置
int Index(SString S, SString T) {
    if (T.length == 0) return 0;
    
    StringNode *p1 = S.head, *p2 = T.head;
    int pos = 1;
    
    while (p1 != NULL) {
        StringNode *temp1 = p1;
        StringNode *temp2 = p2;
        
        while (temp1 != NULL && temp2 != NULL && temp1->ch == temp2->ch) {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        
        if (temp2 == NULL) {
            return pos;
        }
        
        p1 = p1->next;
        pos++;
    }
    
    return 0;
}

// 清空字符串
bool ClearString(SString *S) {
    StringNode *p = S->head;
    while (p != NULL) {
        StringNode *temp = p;
        p = p->next;
        free(temp);
    }
    S->head = NULL;
    S->length = 0;
    return true;
}

// 销毁字符串
bool DestroyString(SString *S) {
    return ClearString(S);
}

int main() {
    SString s1, s2, sub;
    StrInit(&s1);
    StrInit(&s2);
    StrInit(&sub);
    
    StrAssign(&s1, "hello");
    StrAssign(&s2, "world");
    
    printf("s1 length: %d\n", StrLength(s1));
    printf("s2 length: %d\n", StrLength(s2));
    
    if (Concat(&sub, s1, s2)) {
        printf("Concatenated string: ");
        StringNode *p = sub.head;
        while (p != NULL) {
            printf("%c", p->ch);
            p = p->next;
        }
        printf("\n");
    }
    
    int pos = Index(sub, s2);
    if (pos > 0) {
        printf("T found at position: %d\n", pos);
    } else {
        printf("T not found\n");
    }
    
    // 使用完毕后需要销毁
    DestroyString(&s1);
    DestroyString(&s2);
    DestroyString(&sub);
    
    return 0;
}
***/
