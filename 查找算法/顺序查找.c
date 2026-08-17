#include <stdio.h>
#include <stdlib.h>
//À≥–Ú≤È’“
int FindBySeq(int *ListSeq, int ListLength, int KeyData);

int main()
{
    int TestData[5] = { 34, 35, 26, 89, 56 };
    int retData = FindBySeq(TestData, 5, 89);
    printf("retData: %d\n", retData);
    return 0;
}

int FindBySeq(int *ListSeq, int ListLength, int KeyData)
{
	int i; 
    int tmp = 0;
    int length = ListLength;
    for (i = 0; i < ListLength; i++)
    {
        if (ListSeq[i] == KeyData)
            return i;
    }
    return 0;
} 
