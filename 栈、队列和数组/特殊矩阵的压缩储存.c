#include <stdio.h>
#include <stdlib.h>
#define N 5  // 定义矩阵的阶数

/***
// 压缩存储对称矩阵
void compressSymmetricMatrix(int matrix[N][N], int *compressed) {
    int index = 0;
    int i,j; 
    for ( i = 0; i < N; i++) {
        for ( j = 0; j <= i; j++) {
            // 存储下三角部分（包含对角线）的元素
            compressed[index++] = matrix[i][j];
        }
    }
}

// 根据压缩数组获取对称矩阵中的元素
int getElement(int *compressed, int i, int j) {
    if (i < j) {
        // 如果 i < j，交换 i 和 j 以访问下三角部分
        int temp = i;
        i = j;
        j = temp;
    }
    // 计算下三角部分元素在压缩数组中的索引
    int index = i * (i + 1) / 2 + j;
    return compressed[index];
}

// 打印压缩后的数组
void printCompressedArray(int *compressed) {
	int i;
    int size = N * (N + 1) / 2;
    for ( i = 0; i < size; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");
}

int main() {
    int matrix[N][N] = {
        {1, 2, 3, 4, 5},
        {2, 6, 7, 8, 9},
        {3, 7, 10, 11, 12},
        {4, 8, 11, 13, 14},
        {5, 9, 12, 14, 15}
    };

    // 计算压缩数组的大小
    int compressedSize = N * (N + 1) / 2;
    int *compressed = (int *)malloc(compressedSize * sizeof(int));

    // 压缩对称矩阵
    compressSymmetricMatrix(matrix, compressed);

    // 打印压缩后的数组
    printf("压缩后的数组: ");
    printCompressedArray(compressed);

    // 测试获取元素
    int row = 2, col = 3;
    int element = getElement(compressed, row, col);
    printf("矩阵中第 %d 行第 %d 列的元素是: %d\n", row + 1, col + 1, element);

    // 释放动态分配的内存
    free(compressed);

    return 0;
}
***/

/***
三角矩阵 
// 上三角矩阵压缩存储
void upperTriangularCompression(int matrix[N][N], int compressed[]) {
    int k = 0;
    int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = i; j < N; j++) {
            compressed[k++] = matrix[i][j];
        }
    }
}

// 下三角矩阵压缩存储
void lowerTriangularCompression(int matrix[N][N], int compressed[]) {
    int k = 0;
    int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j <= i; j++) {
            compressed[k++] = matrix[i][j];
        }
    }
}

// 打印压缩后的数组
void printCompressedArray(int compressed[], int size) {
	int i;
    for ( i = 0; i < size; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");
}

int main() {
    int matrix[N][N] = {
        {1, 2, 3, 4},
        {0, 5, 6, 7},
        {0, 0, 8, 9},
        {0, 0, 0, 10}
    };

    int upperCompressed[N * (N + 1) / 2];
    int lowerCompressed[N * (N + 1) / 2];

    // 上三角矩阵压缩
    upperTriangularCompression(matrix, upperCompressed);
    printf("上三角矩阵压缩后的数组: ");
    printCompressedArray(upperCompressed, N * (N + 1) / 2);

    // 下三角矩阵压缩
    lowerTriangularCompression(matrix, lowerCompressed);
    printf("下三角矩阵压缩后的数组: ");
    printCompressedArray(lowerCompressed, N * (N + 1) / 2);

    return 0;
}
***/

/***
// 三对角矩阵压缩存储
void compressTridiagonalMatrix(int matrix[N][N], int compressed[]) {
    int index = 0;
    int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < N; j++) {
            if (i == j || i == j - 1 || i == j + 1) {
                compressed[index++] = matrix[i][j];
            }
        }
    }
}

// 根据压缩数组获取三对角矩阵中指定位置的元素
int getElement(int compressed[], int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= N) {
        return 0;  // 越界返回 0
    }
    if (i == j) {
        return compressed[2 * i];
    } else if (i == j - 1) {
        return compressed[2 * i + 1];
    } else if (i == j + 1) {
        if (i > 0) {
            return compressed[2 * i - 1];
        }
    }
    return 0;  // 非三对角线上的元素为 0
}

int main() {
	int i;
    int matrix[N][N] = {
        {1, 2, 0, 0, 0},
        {3, 4, 5, 0, 0},
        {0, 6, 7, 8, 0},
        {0, 0, 9, 10, 11},
        {0, 0, 0, 12, 13}
    };
    int compressed[3 * N - 2];

    // 压缩矩阵
    compressTridiagonalMatrix(matrix, compressed);

    // 输出压缩后的数组
    printf("压缩后的数组: ");
    for ( i = 0; i < 3 * N - 2; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");

    // 测试获取元素
    int row = 2, col = 3;
    int element = getElement(compressed, row, col);
    printf("矩阵中第 %d 行第 %d 列的元素是: %d\n", row + 1, col + 1, element);

    return 0;
}
***/

//稀疏矩阵 
//1.三元表
//#include <stdio.h>
//#include <stdlib.h>
//#define MAX_SIZE 100
//
//// 定义三元组结构体
//typedef struct {
//    int row;  // 行号
//    int col;  // 列号
//    int value;  // 元素值
//} Triple;
//
//// 定义稀疏矩阵结构体
//typedef struct {
//    Triple data[MAX_SIZE];  // 存储三元组的数组
//    int rows;  // 矩阵的行数
//    int cols;  // 矩阵的列数
//    int nums;  // 非零元素的个数
//} TSMatrix;
//
//// 初始化稀疏矩阵
//void initMatrix(TSMatrix *M, int rows, int cols) {
//    M->rows = rows;
//    M->cols = cols;
//    M->nums = 0;
//}
//
//// 插入非零元素
//void insertElement(TSMatrix *M, int row, int col, int value) {
//    if (M->nums >= MAX_SIZE) {
//        printf("三元组表已满，无法插入新元素！\n");
//        return;
//    }
//    M->data[M->nums].row = row;
//    M->data[M->nums].col = col;
//    M->data[M->nums].value = value;
//    M->nums++;
//}
//
//// 打印稀疏矩阵
//void printMatrix(TSMatrix M) {
//	int i; 
//    for ( i = 0; i < M.nums; i++) {
//        printf("(%d, %d): %d\n", M.data[i].row, M.data[i].col, M.data[i].value);
//    }
//}
//
//int main() {
//    TSMatrix M;
//    initMatrix(&M, 3, 3);
//
//    insertElement(&M, 0, 0, 1);
//    insertElement(&M, 1, 1, 2);
//    insertElement(&M, 2, 2, 3);
//
//    printMatrix(M);
//
//    return 0;
//}
//2.十字链表
#include <stdio.h>
#include <stdlib.h>

// 定义十字链表节点结构体
typedef struct OLNode {
    int row, col;  // 行号和列号
    int value;  // 元素值
    struct OLNode *right, *down;  // 同行和同列的下一个节点指针
} OLNode, *OLink;

// 定义十字链表结构体
typedef struct {
    OLink *rhead, *chead;  // 行和列的头指针数组
    int rows, cols, nums;  // 矩阵的行数、列数和非零元素的个数
} CrossList;

// 初始化十字链表
void initCrossList(CrossList *M, int rows, int cols) {
    M->rows = rows;
    M->cols = cols;
    M->nums = 0;

    M->rhead = (OLink *)malloc(rows * sizeof(OLink));
    M->chead = (OLink *)malloc(cols * sizeof(OLink));
    
    int i,j;
    for ( i = 0; i < rows; i++) {
        M->rhead[i] = NULL;
    }
    for ( j = 0; j < cols; j++) {
        M->chead[j] = NULL;
    }
}

// 插入非零元素
void insertElementCrossList(CrossList *M, int row, int col, int value) {
    OLNode *p = (OLNode *)malloc(sizeof(OLNode));
    p->row = row;
    p->col = col;
    p->value = value;

    // 插入到行链表中
    if (M->rhead[row] == NULL || M->rhead[row]->col > col) {
        p->right = M->rhead[row];
        M->rhead[row] = p;
    } else {
        OLNode *q = M->rhead[row];
        while (q->right != NULL && q->right->col < col) {
            q = q->right;
        }
        p->right = q->right;
        q->right = p;
    }

    // 插入到列链表中
    if (M->chead[col] == NULL || M->chead[col]->row > row) {
        p->down = M->chead[col];
        M->chead[col] = p;
    } else {
        OLNode *q = M->chead[col];
        while (q->down != NULL && q->down->row < row) {
            q = q->down;
        }
        p->down = q->down;
        q->down = p;
    }

    M->nums++;
}

// 打印十字链表
void printCrossList(CrossList M) {
	int i;
    for ( i = 0; i < M.rows; i++) {
        OLNode *p = M.rhead[i];
        while (p != NULL) {
            printf("(%d, %d): %d\n", p->row, p->col, p->value);
            p = p->right;
        }
    }
}

int main() {
    CrossList M;
    initCrossList(&M, 3, 3);

    insertElementCrossList(&M, 0, 0, 1);
    insertElementCrossList(&M, 1, 1, 2);
    insertElementCrossList(&M, 2, 2, 3);

    printCrossList(M);

    return 0;
} 
