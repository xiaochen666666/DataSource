#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 归并排序(二路归并) 

int *B = NULL; // 辅助数组，稍后分配内存

void Merge(int A[], int low, int mid, int high) {
    // 表A的两段A[low...mid]和A[mid+1...high]各自有序，将他们合并成一个有序表
    int i, j, k;
    for (k = low; k <= high; k++) {
        B[k] = A[k];
    }
    
    i = low;
    j = mid + 1;
    k = low;
    
    while (i <= mid && j <= high) {
        if (B[i] <= B[j]) {
            A[k++] = B[i++];
        } else {
            A[k++] = B[j++];
        }
    }
    
    while (i <= mid) A[k++] = B[i++];    // 若第一个表未检测完，复制 
    while (j <= high) A[k++] = B[j++];   // 若第二个表未检测完，复制 
}

void MergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, mid, high);
    }
}

int main() {
    int A[] = {49, 38, 65, 97, 76, 13, 27};
    int n = sizeof(A) / sizeof(A[0]); // 计算数组长度
    
    // 为辅助数组分配内存
    B = (int *)malloc(n * sizeof(int));
    if (B == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    
    printf("原始数据: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    MergeSort(A, 0, n - 1);
    
    printf("归并排序: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    // 释放内存
    free(B);
    
    return 0;
}
