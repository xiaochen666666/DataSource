#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成指定范围内的随机整数
int generate_random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// 生成指定范围内的随机浮点数
double generate_random_double(double min, double max) {
    double scale = (double)rand() / RAND_MAX; // 0.0 到 1.0
    return min + scale * (max - min);
}

int main() {
    // 设置随机数种子，使用当前时间
    srand((unsigned int)time(NULL));
    
    printf("随机数生成器示例\n");
    printf("================\n");
    
    // 生成10个随机整数（1-100）
    printf("10个1-100的随机整数：\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", generate_random_int(1, 100));
    }
    printf("\n\n");
    
    // 生成10个随机浮点数（0.0-1.0）
    printf("10个0.0-1.0的随机浮点数：\n");
    for (int i = 0; i < 10; i++) {
        printf("%.4f ", generate_random_double(0.0, 1.0));
    }
    printf("\n\n");
    
    // 生成随机布尔值
    printf("10个随机布尔值：\n");
    for (int i = 0; i < 10; i++) {
        printf("%s ", rand() % 2 ? "true" : "false");
    }
    printf("\n");
    
    return 0;
}
