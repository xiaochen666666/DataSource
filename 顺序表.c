//静态数组实现顺序表
/*
#include<stdio.h>
#include<stdlib.h>
#define max 100

typedef struct {
    int data[max];
    int last;
} sqlist;

void initlist(sqlist* l) {  // Pass by reference to initialize
    l->last = 0;
    printf("初始化已完成，该表已为空表\n");
}

void createlist(sqlist* l, int n) {  // Create list
    int i = 0;
    int j;
    for (i = 0; i < n; i++) {
        scanf_s("%d", &j);
        l->data[i] = j;
    }
    l->last = n;
}

void insertelem(sqlist* l, int i, int e) {
    int k;
    if (i < 0 || i > l->last) {
        printf("插入的位置不合法\n");
        return;
    }
    if (l->last >= max) {  // Use '>=' to avoid overflow
        printf("表满，无法插入\n");
        return;
    }
    for (k = l->last; k >= i; --k) {  // Fix the loop by removing the semicolon
        l->data[k + 1] = l->data[k];
    }
    l->data[i] = e;  // Insert the new element at position i
    l->last++;
}

int deletelem1(sqlist* l, int i) {
    int k;
    if (i < 0 || i >= l->last) {  // Use '>=' to avoid invalid index
        printf("删除的位置不合法\n");
        return 0;
    }
    printf("删除的元素为%d\n", l->data[i]);
    for (k = i; k < l->last - 1; ++k) {  // Adjust loop to shift elements correctly
        l->data[k] = l->data[k + 1];
    }
    l->last--;
    return 1;
}

int findelem(sqlist* l, int e) {
    int k;
    for (k = 0; k < l->last; k++) {
        if (l->data[k] == e) {
            printf("查找成功！该元素在顺序表中的位置为%d\n", k);
            return 1;
        }
    }
    printf("查找失败\n");
    return 0;
}

int getelem(sqlist* l, int i) {
    if (i < 0 || i >= l->last) {  // Use '>=' to avoid invalid index
        printf("查找位置不合法\n");
        return 0;
    }
    printf("第%d的元素为%d\n", i, l->data[i]);
    return 1;
}

void printlist(sqlist l) {
    int i = 0;
    while (i < l.last) {
        printf("%d\t", l.data[i]);
        ++i;
    }
    printf("\n");
}

int main() {
    sqlist l;
    initlist(&l);  // Pass the address of l
    int n;
    printf("请输入数据元素的个数：\n");
    scanf_s("%d", &n);
    printf("请向顺序表中输入元素：\n");
    createlist(&l, n);
    printlist(l);

    int i;
    printf("请输入要删除的元素的位置:\n");
    scanf_s("%d", &i);
    deletelem1(&l, i);
    printlist(l);

    printf("请输入你要查找的元素值：\n");
    int a;
    scanf_s("%d", &a);
    findelem(&l, a);

    printf("请输入你要查找的元素的位置：\n");
    int p;
    scanf_s("%d", &p);
    getelem(&l, p);

    return 0;
}
*/
//动态数组实现顺序表
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* data;  // 动态数组
    int last;   // 表示数组中元素的个数
    int capacity;  // 数组的容量
} sqlist;

// 初始化
void initlist(sqlist* l, int initial_capacity) {
    l->data = (int*)malloc(initial_capacity * sizeof(int));
    if (l->data == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    l->last = 0;
    l->capacity = initial_capacity;
    printf("初始化已完成，该表已为空表\n");
}

// 动态调整数组大小
void resize(sqlist* l, int new_capacity) {
    int* new_data = (int*)realloc(l->data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        printf("内存重新分配失败\n");
        exit(1);
    }
    l->data = new_data;
    l->capacity = new_capacity;
}

// 创建表
void createlist(sqlist* l, int n) {
    if (n > l->capacity) {
        resize(l, n);
    }
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &l->data[i]);
    }
    l->last = n;
}

// 插入元素
void insertelem(sqlist* l, int i, int e) {
    if (i < 0 || i > l->last) {
        printf("插入的位置不合法\n");
        return;
    }
    if (l->last >= l->capacity) {
        resize(l, l->capacity * 2);  // 动态调整数组大小
    }
    for (int k = l->last; k > i; --k) {
        l->data[k] = l->data[k - 1];
    }
    l->data[i] = e;
    l->last++;
}

// 删除元素
int deletelem1(sqlist* l, int i) {
    if (i < 0 || i >= l->last) {
        printf("删除的位置不合法\n");
        return 0;
    }
    printf("删除的元素为%d\n", l->data[i]);
    for (int k = i; k < l->last - 1; ++k) {
        l->data[k] = l->data[k + 1];
    }
    l->last--;
    return 1;
}

// 查找元素值
int findelem(sqlist* l, int e) {
    for (int k = 0; k < l->last; k++) {
        if (l->data[k] == e) {
            printf("查找成功！该元素在顺序表中的位置为%d\n", k);
            return 1;
        }
    }
    printf("查找失败\n");
    return 0;
}

// 按位置查找元素
int getelem(sqlist* l, int i) {
    if (i < 0 || i >= l->last) {
        printf("查找位置不合法\n");
        return 0;
    }
    printf("第%d的元素为%d\n", i, l->data[i]);
    return 1;
}

// 打印列表
void printlist(sqlist* l) {
    for (int i = 0; i < l->last; i++) {
        printf("%d\t", l->data[i]);
    }
    printf("\n");
}

// 释放内存
void freelist(sqlist* l) {
    free(l->data);
    l->data = NULL;
    l->capacity = 0;
    l->last = 0;
}

int main() {
    sqlist l;
    initlist(&l, 10);  // 初始化动态数组，初始容量为10

    int n;
    printf("请输入数据元素的个数：\n");
    scanf_s("%d", &n);
    printf("请向顺序表中输入元素：\n");
    createlist(&l, n);
    printlist(&l);

    int i;
    printf("请输入要删除的元素的位置:\n");
    scanf_s("%d", &i);
    deletelem1(&l, i);
    printlist(&l);

    printf("请输入你要查找的元素值：\n");
    int a;
    scanf_s("%d", &a);
    findelem(&l, a);

    printf("请输入你要查找的元素的位置：\n");
    int p;
    scanf_s("%d", &p);
    getelem(&l, p);

    freelist(&l);  // 释放动态分配的内存

    return 0;
}
