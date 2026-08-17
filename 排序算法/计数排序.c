#include <stdio.h>
#include <stdlib.h>

// 计数排序
void CountSort(int A[], int B[], int n, int k) {
    int i, C[k];
    for (i = 0; i < k; i++) {
        C[i] = 0;    // 初始化计数数组 
    }
    for (i = 0; i < n; i++) {    // 遍历输入数组，统计每个元素出现的次数 
        C[A[i]]++;        // C[A[i]]保存的是等于A[i]的元素个数 
    }
    for (i = 1; i < k; i++) {
        C[i] = C[i] + C[i-1];    // C[x]保存的是小于或等于x的元素个数 
    } 
    for (i = n - 1; i >= 0; i--) {        // 从后往前遍历输入数组 
        B[C[A[i]] - 1] = A[i];    // 将元素A[i]放在输出数组B[]的正确位置上 
        C[A[i]] = C[A[i]] - 1;
    }
}

int main() {
    int A[] = {2, 4, 3, 0, 2, 3};
    int n = sizeof(A) / sizeof(A[0]); // 计算数组长度
    
    // 找出数组中的最大值，确定k的值
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    int k = max + 1; // k应该是最大值+1
    
    int B[n]; // 输出数组
    
    printf("原始数据: ");
    for (int i = 0; i < n; i++) { 
        printf("%d ", A[i]);
    }
    printf("\n");
    
    CountSort(A, B, n, k);
    
    printf("计数排序: ");
    for (int i = 0; i < n; i++) { 
        printf("%d ", B[i]);
    }
    printf("\n");
    
    return 0;
}
