////
//////静态顺序表 
////#include <stdio.h>
////#include <stdlib.h>
////#define MaxSize 50
////#define true 1
////#define false 0
////
////typedef int ElemType;   // 将 ElemType 定义为 int 类型
////
////
////typedef struct {
////	ElemType data[MaxSize];  // 此时 data 是 int 型数组
////	int length;
////} SqList;
////
/////*
////typedef struct{
////	ElemType *data;
////	int Maxsize,length;
////}SeqList;
////
////SeqList L;
////L = (ElemType*)malloc(sizeof(ElemType)*InitSize)
////*/
//////初始化
////void InitList(SqList *L) {
////	L->length = 0;
////}
/////*
////void InitList(SeqList *L) {
////	L.data=(ElemType*)malloc(sizeof(ElemType)*InitSize);
////	L.length=0;
////	L.MaxSize=InitSize;
////}
////*/
////
//////插入
////int ListInsert(SqList *L,int i,ElemType e) {
////	int j;
////	if(i<1||i>L->length+1) {
////		return false;
////	}
////	if(L->length>=MaxSize) {
////		return false;
////	}
////	for(j=L->length; j>=i; j--) {
////		L->data[j]=L->data[j-1];
////	}
////	L->data[i-1]=e;
////	L->length++;
////	return true;
////}
////
////
//////删除
////int ListDelete(SqList *L,int i,ElemType *e) {
////	int j;
////	if(i<1||i>L->length+1) {
////		return false;
////	}
////	*e=L->data[i-1];
////	for(j=L->length; j>=i; j--) {
////		L->data[j-1]=L->data[j];
////	}
////	L->length--;
////	return true;
////}
////
//////查找
////int LocateElem(SqList *L,ElemType e) {
////	int i;
////	for(i=0; i<L->length; i++) {
////		if(L->data[i]==e) {
////			return i+1;
////		}
////	}
////	return 0;
////}
////
//////修改
////int ModifyElem(SqList *L,ElemType e,int m) {
////	int i;
////	for(i=0; i<L->length; i++) {
////		if(L->data[i]==e) {
////			L->data[i]=m;
////			return true;
////		} else {
////			return false;
////		}
////	}
////}
////
////int main() {
////	SqList L;
////	InitList(&L);  // 初始化顺序表
////	// 测试插入操作
////	printf("插入元素测试:\n");
////	int elements[] = {10, 20, 30, 40, 50};
////	int i;
////	for (i = 0; i < 5; i++) {
////		if (ListInsert(&L, i + 1, elements[i])) {
////			printf("插入 %d 成功，当前长度: %d\n", elements[i], L.length);
////		} else {
////			printf("插入 %d 失败!\n", elements[i]);
////		}
////	}
////
////	// 打印当前顺序表
////	printf("\n当前顺序表内容: ");
////	for (i = 0; i < L.length; i++)
////		printf("%d ", L.data[i]);
////	printf("\n");
////
////	// 测试删除操作
////	printf("\n删除位置3的元素:\n");
////	ElemType deletedValue;
////	if (ListDelete(&L, 3, &deletedValue)) {
////		printf("删除成功，删除值: %d\n", deletedValue);
////	} else {
////		printf("删除失败!\n");
////	}
////
////	// 打印删除后的顺序表
////	printf("删除后顺序表内容: ");
////	for (i = 0; i < L.length; i++)
////		printf("%d ", L.data[i]);
////	printf("\n");
////
////	// 测试查找操作
////	printf("\n查找元素测试:\n");
////	int targets[] = {20, 40, 99};
////	for (i = 0; i < 3; i++) {
////		int pos = LocateElem(&L, targets[i]);
////		if (pos)
////			printf("元素 %d 在位置 %d\n", targets[i], pos);
////		else
////			printf("元素 %d 未找到\n", targets[i]);
////	}
////	//测试修改操作
////	printf("\n测试元素测试:\n");
////	int m = 100;
////	int j;
////	printf("请输入修改的元素位置:");
////	scanf("%d",&j);
////	ModifyElem(&L,L.data[j-1],m);
////	int flag=ModifyElem(&L,L.data[j-1],m);
////	if(flag==0) {
////		printf("输入位置非法！");
////	}
////	printf("\n当前顺序表内容: ");
////	for (i = 0; i < L.length; i++)
////		printf("%d ", L.data[i]);
////	printf("\n");
////
////	return 0;
////}


#include <stdio.h>
#include <stdlib.h>

#define InitSize 50
#define true 1
#define false 0

typedef int ElemType;

// 定义顺序表结构体
typedef struct {
    ElemType *data;
    int MaxSize;
    int length;
} SeqList;

// 初始化顺序表
void InitList(SeqList *L) {
    L->data = (ElemType *)malloc(InitSize * sizeof(ElemType));
    if (L->data == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    L->length = 0;
    L->MaxSize = InitSize;
}

// 增加顺序表的容量
void IncreaseSize(SeqList *L, int len) {
    ElemType *p = L->data;
    L->data = (ElemType *)malloc((L->MaxSize + len) * sizeof(ElemType));
    int i;
    for (i = 0; i < L->length; i++) {
        L->data[i] = p[i];
    }
    L->MaxSize = L->MaxSize + len;
    free(p);
}

// 插入元素
int ListInsert(SeqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length + 1) {
        return false;
    }
    if (L->length >= L->MaxSize) {
        IncreaseSize(L, 10);
    }
    int j;
    for (j = L->length; j >= i; j--) {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return true;
}

// 删除元素
int ListDelete(SeqList *L, int i, ElemType *e) {
    if (i < 1 || i > L->length) {
        return false;
    }
    *e = L->data[i - 1];
    int j;
    for (j = i; j < L->length; j++) {
        L->data[j - 1] = L->data[j];
    }
    L->length--;
    return true;
}

// 查找元素
int LocateElem(SeqList *L, ElemType e) {
    int i;
    for (i = 0; i < L->length; i++) {
        if (L->data[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

// 修改元素
int ModifyElem(SeqList *L, ElemType e, int m) {
    int i;
    for (i = 0; i < L->length; i++) {
        if (L->data[i] == e) {
            L->data[i] = m;
            return true;
        }
    }
    return false;
}

// 释放顺序表内存
void DestroyList(SeqList *L) {
    free(L->data);
    L->data = NULL;
    L->length = 0;
    L->MaxSize = 0;
}

int main() {
    SeqList L;
    InitList(&L);  // 初始化顺序表

    // 测试插入操作
    printf("插入元素测试:\n");
    int elements[] = {10, 20, 30, 40, 50};
    int i;
    for (i = 0; i < 5; i++) {
        if (ListInsert(&L, i + 1, elements[i])) {
            printf("插入 %d 成功，当前长度: %d\n", elements[i], L.length);
        } else {
            printf("插入 %d 失败!\n", elements[i]);
        }
    }

    // 打印当前顺序表
    printf("\n当前顺序表内容: ");
    for (i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");

    // 测试删除操作
    printf("\n删除位置3的元素:\n");
    ElemType deletedValue;
    if (ListDelete(&L, 3, &deletedValue)) {
        printf("删除成功，删除值: %d\n", deletedValue);
    } else {
        printf("删除失败!\n");
    }

    // 打印删除后的顺序表
    printf("删除后顺序表内容: ");
    for (i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");

    // 测试查找操作
    printf("\n查找元素测试:\n");
    int targets[] = {20, 40, 99};
    for (i = 0; i < 3; i++) {
        int pos = LocateElem(&L, targets[i]);
        if (pos) {
            printf("元素 %d 在位置 %d\n", targets[i], pos);
        } else {
            printf("元素 %d 未找到\n", targets[i]);
        }
    }

    // 测试修改操作
    printf("\n测试元素修改:\n");
    int m = 100;
    int j;
    printf("请输入修改的元素位置:");
    scanf("%d", &j);
    if (j >= 1 && j <= L.length) {
        int flag = ModifyElem(&L, L.data[j - 1], m);
        if (flag) {
            printf("修改成功！\n");
        } else {
            printf("修改失败！\n");
        }
    } else {
        printf("输入位置非法！\n");
    }

    // 打印修改后的顺序表
    printf("\n当前顺序表内容: ");
    for (i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");

    // 释放顺序表内存
    DestroyList(&L);

    return 0;
}
