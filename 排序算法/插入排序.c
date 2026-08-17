#include <stdio.h>
#include <stdlib.h>

//直接插入排序
void StraightInsertionSort(int *A, int n) {
	int i, j;
	for (i = 2; i <= n; i++) {
		if (A[i] < A[i - 1]) {
			A[0] = A[i]; // 使用 A[0] 作为哨兵
			for (j = i - 1; A[0] < A[j]; --j) {
				A[j + 1] = A[j];
			}
			A[j + 1] = A[0];
		}
	}
}

//折半插入排序
void  BinaryInsertSort(int *A, int n) {
	int i,j,low,high,mid;
	for(i = 2; i<=n; i++) {
		A[0] = A[i];
		low = 1;
		high = i-1;
		while(low <= high) {
			mid = (low + high) / 2;
			if(A[mid] > A[0]) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		for(j = i-1; j >= high+1;--j) {
			A[j+1] = A[j];
		}
		A[high+1] = A[0];
	}
}

//希尔排序
void ShellSort(int A[], int n) {
    int dk, i, j;
    // 外层循环：控制增量序列，从n/2开始，每次减半，直到增量为1
    for (dk = n / 2; dk >= 1; dk = dk / 2) {        
        // 中层循环：从第dk+1个元素开始，对每个子序列进行插入排序
        for (i = dk + 1; i <= n; ++i) {            
            // 判断当前元素是否小于前面同子序列的元素
            if (A[i] < A[i - dk]) {               
                // 将当前元素暂存到A[0]
                A[0] = A[i];               
                // 内层循环：在子序列中寻找合适的插入位置
                // j从当前元素的前一个同子序列元素开始，向前移动dk步长
                for (j = i - dk; j > 0 && A[0] < A[j]; j -= dk) {
                    // 将元素向后移动dk个位置
                    A[j + dk] = A[j];
                }               
                // 将暂存的元素插入到正确位置
                A[j + dk] = A[0];
            }
        }
    }
}

int main() {
	int A[9] = {0, 49, 38, 65, 97, 76, 13, 27, 49}; // 开头添加 0 作为哨兵
	int B[9] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
	int C[9] = {0, 49, 38, 65, 97, 76, 13, 27, 49}; //A[0]作为暂存位置，不作哨兵 

	printf("原始数据: ");
	for (int i = 1; i <= 8; i++) { // 从 1 开始，跳过哨兵
		printf("%d ", A[i]);
	}
	printf("\n");
	
	StraightInsertionSort(A, 8);
	BinaryInsertSort(B,8);
	ShellSort(C,8);

	printf("直接插入排序: ");
	for (int i = 1; i <= 8; i++) { // 从 1 开始，跳过哨兵
		printf("%d ", A[i]);
	}
	printf("\n");
	
	printf("折半插入排序: ");
	for (int i = 1; i <= 8; i++) { // 从 1 开始，跳过哨兵
		printf("%d ", B[i]);
	}
	printf("\n");
	
	printf("希尔排序: ");
	for (int i = 1; i <= 8; i++) { // 从 1 开始，跳过哨兵
		printf("%d ", C[i]);
	}
	printf("\n");
	return 0;
}
