#include <stdio.h>
#include <stdlib.h>

// 定义顺序存储的二叉树结构
typedef struct {
    int *nodes;      // 存储节点的数组
    int capacity;    // 数组容量
    int size;        // 当前节点数量
} SeqBinaryTree;

// 初始化二叉树
void init_tree(SeqBinaryTree *tree, int initial_capacity) {
    tree->nodes = (int *)malloc(initial_capacity * sizeof(int));  // 分配初始内存
    tree->capacity = initial_capacity;  // 设置初始容量
    tree->size = 0;                     // 初始大小为0
}

// 扩展二叉树存储空间
void expand_capacity(SeqBinaryTree *tree) {
    int new_capacity = tree->capacity * 2;  // 容量扩大为原来的2倍
    tree->nodes = (int *)realloc(tree->nodes, new_capacity * sizeof(int));  // 重新分配内存
    tree->capacity = new_capacity;          // 更新容量
}

// 插入节点
void insert_node(SeqBinaryTree *tree, int value) {
    if (tree->size >= tree->capacity) {  // 如果空间不足
        expand_capacity(tree);           // 扩展容量
    }
    tree->nodes[tree->size++] = value;   // 插入值并增加大小
}

// 获取父节点索引
int parent_index(int child_index) {
    return (child_index - 1) / 2;  // 根据子节点索引计算父节点索引
}

// 获取左孩子索引
int left_child_index(int parent_index) {
    return 2 * parent_index + 1;   // 根据父节点索引计算左孩子索引
}

// 获取右孩子索引
int right_child_index(int parent_index) {
    return 2 * parent_index + 2;   // 根据父节点索引计算右孩子索引
}

// 前序遍历
void pre_order_traversal(SeqBinaryTree *tree, int index) {
    if (index >= tree->size) return;  // 递归终止条件：索引超出范围
    
    printf("%d ", tree->nodes[index]);                     // 访问当前节点
    pre_order_traversal(tree, left_child_index(index));    // 递归遍历左子树
    pre_order_traversal(tree, right_child_index(index));   // 递归遍历右子树
}

int main() {
    SeqBinaryTree tree;
    init_tree(&tree, 10);  // 初始化树，初始容量为10
    
    // 示例插入节点（按完全二叉树顺序）
    insert_node(&tree, 1);
    insert_node(&tree, 2);
    insert_node(&tree, 3);
    insert_node(&tree, 4);
    insert_node(&tree, 5);

    printf("前序遍历结果：");
    pre_order_traversal(&tree, 0);  // 从根节点(索引0)开始前序遍历
    
    free(tree.nodes);  // 释放内存
    return 0;
}
