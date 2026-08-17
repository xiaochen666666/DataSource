#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50

// 顺序储存二叉树
typedef struct TreeNode {
    int value;
    bool isEmpty; 
} TreeNode;

TreeNode t[MaxSize];  // 全局数组

// 初始化二叉树
void InitTree() {
    int i;  
    for (i = 0; i < MaxSize; i++) {
        t[i].isEmpty = true;  // 标记所有节点为空
    }
}

// 在指定位置插入节点
bool InsertNode(int index, int val) {
    if (index < 0 || index >= MaxSize) {
        printf("Index out of range!\n");
        return false;
    }
    if (!t[index].isEmpty) {
        printf("Position already occupied!\n");
        return false;
    }
    t[index].value = val;
    t[index].isEmpty = false;
    return true;
}

// 获取左孩子索引
int LeftChild(int index) {
    return 2 * index + 1;  // 数组从0开始
}

// 获取右孩子索引
int RightChild(int index) {
    return 2 * index + 2;  // 数组从0开始
}

// 获取父节点索引
int Parent(int index) {
    return (index - 1) / 2;
}

// 中序遍历（递归实现）
void InOrderTraverse(int index) {
    if (index >= MaxSize || t[index].isEmpty) {
        return;
    }
    InOrderTraverse(LeftChild(index));  // 遍历左子树
    printf("%d ", t[index].value);      // 访问当前节点
    InOrderTraverse(RightChild(index)); // 遍历右子树
}

int main() {
    InitTree();  // 初始化树
    
    // 构建一个简单的树
    //       1
    //      / \
    //     2   3
    InsertNode(0, 1);          // 根节点
    InsertNode(LeftChild(0), 2);   // 左孩子
    InsertNode(RightChild(0), 3);  // 右孩子
    
    // 中序遍历验证
    printf("InOrder Traverse: ");
    InOrderTraverse(0);  // 从根节点开始遍历
    printf("\n");
    
    return 0;
}
/*链表储存代码在遍历中*/
//typedef struct BiTNode{
//	int data;
//	struct BiTNode *lchild,*rchild;
//}BiTNode,*BiTree; 


