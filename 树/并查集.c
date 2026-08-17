#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

// 并查集数组
int UFSets[SIZE];

// 初始化并查集
void Initial(int s[]) {
    int i;
    for(i = 0; i < SIZE; i++) {
        s[i] = -1;  // 每个元素初始化为-1，表示自己是根节点，集合大小为1
    }
}

// 基本查找操作 - 找到x所属集合的根
int Find(int s[], int x) {
    while(s[x] >= 0) {  // 如果不是根节点(根节点的值为负数)
        x = s[x];       // 向上查找父节点
    }
    return x;
}

// 基本合并操作 - 将Root2合并到Root1下
void Union(int s[], int Root1, int Root2) {
    if(Root1 == Root2) return;  // 修正：原代码中是赋值操作(=)，应为比较(==)
    s[Root2] = Root1;           // 将Root2的父节点设为Root1
}

// 改进的合并操作 - 按大小(秩)合并
void Union1(int s[], int Root1, int Root2) {
    if(Root1 == Root2) return;  // 相同集合不需要合并
    
    // 比较两个根节点的大小(负数，绝对值越大表示集合越大)
    if(s[Root2] > s[Root1]) {   // Root1的集合更大
        s[Root1] += s[Root2];   // 更新Root1的大小
        s[Root2] = Root1;       // 将较小的集合Root2合并到Root1
    }
    else {                      // Root2的集合更大或相等
        s[Root2] += s[Root1];   // 更新Root2的大小
        s[Root1] = Root2;       // 将较小的集合Root1合并到Root2
    }
}

// 改进的查找操作 - 路径压缩
int Find1(int s[], int x) {
    int root = x;
    // 找到根节点
    while(s[root] >= 0) {
        root = s[root];
    }
    // 路径压缩：将查找路径上的所有节点直接指向根
    while(x != root) {
        int t = s[x];  // 暂存父节点
        s[x] = root;   // 当前节点直接指向根
        x = t;         // 处理父节点
    }
    return root;
}

// 打印并查集状态
void PrintSet(int s[], int n) {
	int i; 
    printf("Index: ");
    for(i = 0; i < n; i++) {
        printf("%2d ", i);
    }
    printf("\nParent:");
    for(i = 0; i < n; i++) {
        printf("%2d ", s[i]);
    }
    printf("\n");
}

// 测试用例
int main() {
    // 初始化并查集
    Initial(UFSets);
    printf("Initial state:\n");
    PrintSet(UFSets, 10);
    
    // 测试基本操作
    Union(UFSets, 0, 1);
    Union(UFSets, 0, 2);
    Union(UFSets, 3, 4);
    Union(UFSets, 3, 5);
    printf("\nAfter basic unions:\n");
    PrintSet(UFSets, 10);
    
    printf("\nFind results:\n");
    printf("Find(1) = %d\n", Find(UFSets, 1));
    printf("Find(4) = %d\n", Find(UFSets, 4));
    
    // 重置并测试优化操作
    Initial(UFSets);
    Union1(UFSets, 0, 1);
    Union1(UFSets, 0, 2);
    Union1(UFSets, 3, 4);
    Union1(UFSets, 3, 5);
    printf("\nAfter size-based unions:\n");
    PrintSet(UFSets, 10);
    
    // 合并两个集合
    int root1 = Find1(UFSets, 1);
    int root2 = Find1(UFSets, 4);
    Union1(UFSets, root1, root2);
    printf("\nAfter merging sets:\n");
    PrintSet(UFSets, 10);
    
    printf("\nFind1 results with path compression:\n");
    printf("Find1(2) = %d\n", Find1(UFSets, 2));
    printf("Find1(5) = %d\n", Find1(UFSets, 5));
    PrintSet(UFSets, 10);
    
    return 0;
}

