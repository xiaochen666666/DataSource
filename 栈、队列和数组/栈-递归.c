#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1)  
        return 1;
    else                  
        return n * factorial(n - 1);
}

int main() {
    int x = factorial(10);  
    printf("10 的阶乘是: %d\n", x);  
    printf("完成啦！\n");    
    return 0;
}

