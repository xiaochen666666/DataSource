#include <stdio.h>
#include <stdlib.h>

// 获取数组中最大数字的位数
int getMaxDigits(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    int digits = 0;
    while (max > 0) {
        digits++;
        max /= 10;
    }
    return digits;
}

// 获取数字的某一位数字 (从右往左，从0开始)
int getDigit(int num, int digitPos) {
    int divisor = 1;
    for (int i = 0; i < digitPos; i++) {
        divisor *= 10;
    }
    return (num / divisor) % 10;
}

// 基数排序
void radixSort(int arr[], int n) {
    // 获取最大位数
    int maxDigits = getMaxDigits(arr, n);
    
    // 创建10个桶（0-9）
    int **buckets = (int **)malloc(10 * sizeof(int *));
    int bucketSizes[10] = {0};
    
    // 为每个桶分配内存（最坏情况是所有数字都在同一个桶中）
    for (int i = 0; i < 10; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int));
    }
    
    // 按每一位进行排序
    for (int digit = 0; digit < maxDigits; digit++) {
        // 重置桶大小计数器
        for (int i = 0; i < 10; i++) {
            bucketSizes[i] = 0;
        }
        
        // 将数字分配到对应的桶中
        for (int i = 0; i < n; i++) {
            int digitVal = getDigit(arr[i], digit);
            buckets[digitVal][bucketSizes[digitVal]++] = arr[i];
        }
        
        // 从桶中收集数字（按桶的顺序）
        int index = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
    }
    
    // 释放桶的内存
    for (int i = 0; i < 10; i++) {
        free(buckets[i]);
    }
    free(buckets);
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("原始数组: ");
    printArray(arr, n);
    
    radixSort(arr, n);
    
    printf("基数排序: ");
    printArray(arr, n);
    
    return 0;
}
