#include <stdio.h>

void swap(int *x, int *y);

int main() {
    int *p;
    int a = 10;
    p = &a;
    // printf("%d %p", *p, p);

/*    int x = 5, y = 10;
    swap(&x, &y);
    printf("x=%d,y=%d", x, y); 
*/
/*
    int array[5] = {1,2,3,4,5};
    printf("%d %p \n%d %p",*array,array,*(array+1),(array+1));
*/
    int A[5][5]={{1,2,3,4,5},{1,2,3,4,5}};
    printf("%d %p\n%d %p\n%d %p",**A,A,*A,*A,A,**A);
    return 0;
}
/*
void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
*/
