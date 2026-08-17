#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*选择排序*/

// 交换
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 简单选择排序
void SelectSort(int A[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int min = i;    // 记录最小元素位置 
        for(int j = i + 1; j < n; j++) {
            if(A[j] < A[min]) {
                min = j;
            }
        }
        if(min != i) {
            swap(&A[i], &A[min]);
        }
    }
}

// 堆排序（大根堆） 
void HeadAdjust(int A[], int k, int len) {
    // 对以元素K为根的子树进行调整
    A[0] = A[k];    // A[0]暂存子树的根节点 
    for(int i = 2 * k; i <= len; i *= 2) {
        if(i < len && A[i] < A[i + 1]) {    // 取左右孩子中较大的孩子下标 
            i++;
        }
        if(A[0] >= A[i]) {
            break;
        } else {
            A[k] = A[i];    // 将大的孩子改为父节点 
            k = i;
        }
    }    
    A[k] = A[0];
}

void BuildMaxHeap(int A[], int len) {
    for(int i = len / 2; i > 0; i--) {    // 从i=[n/2]~1,反复调整堆 
        HeadAdjust(A, i, len);
    }
}

// 完整的堆排序函数
void HeapSort(int A[], int len) {
    BuildMaxHeap(A, len);        // 初始建堆
    for(int i = len; i > 1; i--) {
        swap(&A[1], &A[i]);      // 将堆顶元素（最大）与末尾元素交换
        HeadAdjust(A, 1, i - 1); // 调整剩余元素为堆
    }
}

// 打印数组
void printArray(int arr[], int n, const char *name, int start) {
    printf("%s: ", name);
    for (int i = start; i < n; i++) { 
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {2, 2, 1};
    int B[] = {0, 49, 38, 65, 97, 76, 13, 27, 49}; // 注意：堆排序从索引1开始
    
    printf("=== 简单选择排序测试 ===\n");
    printf("原始数据: ");
    printArray(A, 3, "", 0);
    
    SelectSort(A, 3);
    printf("简单选择排序后: ");
    printArray(A, 3, "", 0);
    
    printf("\n=== 堆排序测试 ===\n");
    printf("原始数据: ");
    printArray(B, 9, "", 1); // 从索引1开始显示，跳过哨兵
    
    BuildMaxHeap(B, 8);
    printf("建堆后: ");
    printArray(B, 9, "", 1);
    
    // 完整的堆排序
    int C[] = {0, 49, 38, 65, 97, 76, 13, 27, 49}; // 重新初始化
    HeapSort(C, 8);
    printf("完整堆排序后: ");
    printArray(C, 9, "", 1);
    
    // 更多测试
    printf("\n=== 更多堆排序测试 ===\n");
    int test1[] = {0, 5, 2, 8, 1, 9, 3};
    int test2[] = {0, 1, 2, 3, 4, 5};
    int test3[] = {0, 5, 4, 3, 2, 1};
    
    printf("测试1 - 乱序: ");
    printArray(test1, 7, "前", 1);
    HeapSort(test1, 6);
    printArray(test1, 7, "后", 1);
    
    printf("测试2 - 已排序: ");
    printArray(test2, 6, "前", 1);
    HeapSort(test2, 5);
    printArray(test2, 6, "后", 1);
    
    printf("测试3 - 逆序: ");
    printArray(test3, 6, "前", 1);
    HeapSort(test3, 5);
    printArray(test3, 6, "后", 1);
    
    return 0;
}
