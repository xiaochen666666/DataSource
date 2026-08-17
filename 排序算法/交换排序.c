#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 交换排序
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 冒泡排序
void BubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {        // 外层循环：n-1轮比较
        bool flag = false;                   // 标记本轮是否有交换
        for (int j = 0; j < n - 1 - i; j++) { // 内层循环：每轮比较相邻元素
            if (A[j] > A[j + 1]) {           // 如果前一个大于后一个
                swap(&A[j], &A[j + 1]);      // 交换位置
                flag = true;                 // 标记有交换发生
            }
        }
        if (flag == false) {                 // 如果本轮没有交换，说明已排序完成
            return;                          // 提前结束排序
        }
    }
}


// 快速排序主函数
// 划分操作 
int Partition(int A[], int low, int high) {
    int pivot = A[low];  // 选取第一个元素作为基准
    while (low < high) {
        // 从右往左找第一个小于基准的元素
        while (low < high && A[high] >= pivot)  
            --high;
        A[low] = A[high];  // 将小于基准的元素移到左边
        
        // 从左往右找第一个大于基准的元素
        while (low < high && A[low] <= pivot)   
            ++low;
        A[high] = A[low];  // 将大于基准的元素移到右边
    }
    A[low] = pivot;        // 基准元素放到最终位置
    return low;            // 返回基准位置
}
// 快速排序
void QuickSort(int A[], int low, int high) {
    if (low < high) {
        int pivotpos = Partition(A, low, high);  
        QuickSort(A, low, pivotpos - 1);         
        QuickSort(A, pivotpos + 1, high);        
    }
}

// 打印数组函数
void printArray(int arr[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int B[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(A) / sizeof(A[0]);        // 计算数组长度
    
    printf("原始数据: ");
    printArray(A, n, "");
    
    BubbleSort(A, n);  
    QuickSort(B, 0, n-1); 
    
    printf("冒泡排序: ");
    printArray(A, n, "");
    printf("快速排序: ");
    printArray(A, n, "");

    return 0;
}
