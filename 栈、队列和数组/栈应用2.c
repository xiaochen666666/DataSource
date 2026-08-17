#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// 操作数栈节点
typedef struct NumNode {
    int data;
    struct NumNode* next;
} NumNode;

// 运算符栈节点
typedef struct OpNode {
    char op;
    struct OpNode* next;
} OpNode;

// 操作数链栈结构
typedef struct {
    NumNode* top;
} NumStack;

// 运算符链栈结构
typedef struct {
    OpNode* top;
} OpStack;

// 初始化操作数栈
void initNumStack(NumStack* s) {
    s->top = NULL;
}

// 初始化运算符栈
void initOpStack(OpStack* s) {
    s->top = NULL;
}

// 检查操作数栈是否为空
bool isNumEmpty(NumStack* s) {
    return s->top == NULL;
}

// 检查运算符栈是否为空
bool isOpEmpty(OpStack* s) {
    return s->top == NULL;
}

// 操作数压栈
void pushNum(NumStack* s, int num) {
    NumNode* newNode = (NumNode*)malloc(sizeof(NumNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = num;
    newNode->next = s->top;
    s->top = newNode;
}

// 运算符压栈
void pushOp(OpStack* s, char op) {
    OpNode* newNode = (OpNode*)malloc(sizeof(OpNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->op = op;
    newNode->next = s->top;
    s->top = newNode;
}

// 操作数弹栈
int popNum(NumStack* s) {
    if (isNumEmpty(s)) {
        fprintf(stderr, "Pop from empty number stack\n");
        exit(EXIT_FAILURE);
    }
    NumNode* temp = s->top;
    int num = temp->data;
    s->top = s->top->next;
    free(temp);
    return num;
}

// 运算符弹栈
char popOp(OpStack* s) {
    if (isOpEmpty(s)) {
        fprintf(stderr, "Pop from empty operator stack\n");
        exit(EXIT_FAILURE);
    }
    OpNode* temp = s->top;
    char op = temp->op;
    s->top = s->top->next;
    free(temp);
    return op;
}

// 查看栈顶运算符
char peekOp(OpStack* s) {
    return isOpEmpty(s) ? '\0' : s->top->op;
}

// 运算符优先级判断
int precedence(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

// 执行算术运算
int calculate(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Division by zero error\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            fprintf(stderr, "Invalid operator: %c\n", op);
            exit(EXIT_FAILURE);
    }
}

// 表达式求值主函数
int evaluateExpression(const char* expr) {
    NumStack numStack;
    OpStack opStack;
    initNumStack(&numStack);
    initOpStack(&opStack);
    
    int num = 0;
    bool readingNumber = false;
    
    while (*expr) {
        if (isdigit(*expr)) {        // 处理数字字符
            num = num * 10 + (*expr - '0');
            readingNumber = true;
        } else {
            if (readingNumber) {     // 完成完整数字的读取
                pushNum(&numStack, num);
                num = 0;
                readingNumber = false;
            }
            
            if (*expr == '(') {      // 处理左括号
                pushOp(&opStack, *expr);
            } else if (*expr == ')') { // 处理右括号
                while (peekOp(&opStack) != '(') {
                    char op = popOp(&opStack);
                    int b = popNum(&numStack);
                    int a = popNum(&numStack);
                    pushNum(&numStack, calculate(a, b, op));
                }
                popOp(&opStack);  // 弹出左括号
            } else if (*expr != ' ') { // 处理运算符
                // 优先级比较运算（跳过空格）
                while (!isOpEmpty(&opStack) && 
                      precedence(peekOp(&opStack)) >= precedence(*expr)) {
                    char op = popOp(&opStack);
                    int b = popNum(&numStack);
                    int a = popNum(&numStack);
                    pushNum(&numStack, calculate(a, b, op));
                }
                pushOp(&opStack, *expr);
            }
        }
        expr++;
    }
    
    if (readingNumber) {  // 处理最后一个数字
        pushNum(&numStack, num);
    }
    
    // 处理剩余运算符
    while (!isOpEmpty(&opStack)) {
        char op = popOp(&opStack);
        int b = popNum(&numStack);
        int a = popNum(&numStack);
        pushNum(&numStack, calculate(a, b, op));
    }
    
    return popNum(&numStack);
}

// 测试
int main() {
    char expr[256]; // 适当扩大缓冲区
    int retry = 1;
    
    while(retry) {
        printf("请输入计算表达式（输入q退出）: ");
        
        // 安全读取输入（包括空格）
        if (fgets(expr, sizeof(expr), stdin) == NULL) {
            fprintf(stderr, "输入读取失败\n");
            break;
        }
        
        // 处理换行符和退出指令
        size_t len = strcspn(expr, "\n");
        expr[len] = '\0';
        
        if(strcmp(expr, "q") == 0) {
            printf("程序退出\n");
            break;
        }
        
        // 执行计算并处理潜在错误
        printf("计算结果：%d\n", evaluateExpression(expr));
    }
    return 0;
}

