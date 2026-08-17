#include<stdio.h>
//二分查找-C语言实现
//基本思路：将排序好的数据存放到数组里（不能是链表）
//        这只前中后标签，与中间元素比，若小于就将后变为原来的中
//        继续计算中，比较，循环，直至等于中，或循环结束。
int Binary_Search(int *sortedSeq, int seqLength, int keyData);

int main() {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int location;
	int target = 4;
	location = Binary_Search(array, 9, target);
	printf("%d\n", location);
	return 0;
}

int Binary_Search(int *sortedSeq, int seqLength, int keyData) {
	int low = 0,high = seqLength - 1,mid;
	while(low <= high) {
		mid = (low + high) / 2;
		if(sortedSeq[mid] == keyData) {
			return mid;
		} else if(sortedSeq[mid] > keyData) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;  //查找失败
}

