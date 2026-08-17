#include <stdio.h> 
#include <stdlib.h>
#define MAX_TREE_SIZE 100
//树的储存
//1.双亲表示法
typedef struct {
    int data;    // 节点数据
    int parent;  // 双亲位置索引
} PTNode;

typedef struct {
    PTNode nodes[MAX_TREE_SIZE];  // 节点数组
    int n;                       // 节点数量
} PTree;

// 初始化树
void initParentTree(PTree *tree) {
    tree->n = 0;
}

// 添加节点
int addNode(PTree *tree, int data, int parentIndex) {
    if (tree->n >= MAX_TREE_SIZE) {
        printf("Tree is full!\n");
        return -1;
    }
    
    tree->nodes[tree->n].data = data;
    tree->nodes[tree->n].parent = parentIndex;
    tree->n++;
    return tree->n - 1;  // 返回新节点的索引
}

// 打印树
void printParentTree(PTree *tree) {
    printf("Index\tData\tParent\n");
    int i;
    for (i = 0; i < tree->n; i++) {
        printf("%d\t%d\t%d\n", i, tree->nodes[i].data, tree->nodes[i].parent);
    }
}

// 测试双亲表示法
void testParentRepresentation() {
    PTree tree;
    initParentTree(&tree);
    
    // 添加根节点(没有父节点，parent设为-1)
    int root = addNode(&tree, 10, -1);
    int child1 = addNode(&tree, 20, root);
    int child2 = addNode(&tree, 30, root);
    addNode(&tree, 40, child1);
    addNode(&tree, 50, child1);
    addNode(&tree, 60, child2);
    
    printf("Parent Representation:\n");
    printParentTree(&tree);
}

//2.孩子表示法
typedef struct CTNode {
    int child;              // 孩子节点索引
    struct CTNode *next;    // 下一个孩子节点
} *ChildPtr;

typedef struct {
    int data;               // 节点数据
    ChildPtr firstchild;    // 第一个孩子指针
} CTBox;

typedef struct {
    CTBox nodes[MAX_TREE_SIZE];  // 节点数组
    int n, r;                   // 节点数量和根的位置
} CTree;

// 初始化孩子表示法的树
void initChildTree(CTree *tree) {
    tree->n = 0;
    tree->r = -1;
}

// 添加节点
int addCTNode(CTree *tree, int data) {
    if (tree->n >= MAX_TREE_SIZE) {
        printf("Tree is full!\n");
        return -1;
    }
    
    tree->nodes[tree->n].data = data;
    tree->nodes[tree->n].firstchild = NULL;
    tree->n++;
    return tree->n - 1;
}

// 添加孩子关系
void addChild(CTree *tree, int parentIndex, int childIndex) {
    ChildPtr newChild = (ChildPtr)malloc(sizeof(struct CTNode));
    newChild->child = childIndex;
    newChild->next = NULL;
    
    if (tree->nodes[parentIndex].firstchild == NULL) {
        tree->nodes[parentIndex].firstchild = newChild;
    } else {
        ChildPtr p = tree->nodes[parentIndex].firstchild;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newChild;
    }
}

// 打印孩子表示法的树
void printChildTree(CTree *tree) {
    printf("Child Representation:\n");
    printf("Index\tData\tChildren\n");
    int i;
    for (i = 0; i < tree->n; i++) {
        printf("%d\t%d\t", i, tree->nodes[i].data);
        
        ChildPtr p = tree->nodes[i].firstchild;
        while (p != NULL) {
            printf("%d ", p->child);
            p = p->next;
        }
        printf("\n");
    }
}

// 测试孩子表示法
void testChildRepresentation() {
    CTree tree;
    initChildTree(&tree);
    
    int root = addCTNode(&tree, 10);
    tree.r = root;  // 设置根节点
    
    int child1 = addCTNode(&tree, 20);
    int child2 = addCTNode(&tree, 30);
    int child3 = addCTNode(&tree, 40);
    int child4 = addCTNode(&tree, 50);
    int child5 = addCTNode(&tree, 60);
    
    // 建立父子关系
    addChild(&tree, root, child1);
    addChild(&tree, root, child2);
    addChild(&tree, child1, child3);
    addChild(&tree, child1, child4);
    addChild(&tree, child2, child5);
    
    printChildTree(&tree);
}
//3.孩子兄弟表示法
typedef struct CSNode {
    int data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

// 创建新节点
CSNode* createCSNode(int data) {
    CSNode* node = (CSNode*)malloc(sizeof(CSNode));
    node->data = data;
    node->firstchild = NULL;
    node->nextsibling = NULL;
    return node;
}

// 添加孩子节点
void addCSChild(CSNode* parent, CSNode* child) {
    if (parent->firstchild == NULL) {
        parent->firstchild = child;
    } else {
        CSNode* sibling = parent->firstchild;
        while (sibling->nextsibling != NULL) {
            sibling = sibling->nextsibling;
        }
        sibling->nextsibling = child;
    }
}

// 先序遍历
void preOrderTraversal(CSTree tree) {
    if (tree != NULL) {
        printf("%d ", tree->data);
        preOrderTraversal(tree->firstchild);
        preOrderTraversal(tree->nextsibling);
    }
}

// 打印树结构
void printCSTree(CSTree tree, int level) {
    if (tree == NULL) return;
    int i;
    for (i = 0; i < level; i++) printf("  ");
    printf("%d\n", tree->data);
    
    printCSTree(tree->firstchild, level + 1);
    printCSTree(tree->nextsibling, level);
}

// 测试孩子兄弟表示法
void testChildSiblingRepresentation() {
    // 创建节点
    CSNode* root = createCSNode(10);
    CSNode* node1 = createCSNode(20);
    CSNode* node2 = createCSNode(30);
    CSNode* node3 = createCSNode(40);
    CSNode* node4 = createCSNode(50);
    CSNode* node5 = createCSNode(60);
    
    // 构建树结构
    addCSChild(root, node1);
    addCSChild(root, node2);
    addCSChild(node1, node3);
    addCSChild(node1, node4);
    addCSChild(node2, node5);
    
    printf("Child-Sibling Representation (Pre-order):\n");
    preOrderTraversal(root);
    printf("\n");
    
    printf("Tree Structure:\n");
    printCSTree(root, 0);
}

// 主函数
int main() {
    printf("Testing Tree Representations:\n\n");
    
    // 测试双亲表示法
    testParentRepresentation();
    printf("\n");
    
    // 测试孩子表示法
    testChildRepresentation();
    printf("\n");
    
    // 测试孩子兄弟表示法
    testChildSiblingRepresentation();
    
    return 0;
}
