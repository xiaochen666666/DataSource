#include <stdio.h>
#include <stdlib.h>

/*
// 定义树节点结构
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 创建新节点
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入节点到二叉搜索树
TreeNode* insertNode(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    
    return root;
}

// 在二叉搜索树中查找值
TreeNode* searchTree(TreeNode* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    
    if (key < root->data) {
        return searchTree(root->left, key);
    } else {
        return searchTree(root->right, key);
    }
}

// 中序遍历树（用于验证树结构）
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 释放树的内存
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = NULL;
    
    // 插入一些节点
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);
    
    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");
    
    // 查找节点
    int searchKey = 40;
    TreeNode* result = searchTree(root, searchKey);
    if (result != NULL) {
        printf("找到值 %d 在树中\n", searchKey);
    } else {
        printf("未找到值 %d\n", searchKey);
    }
    
    searchKey = 90;
    result = searchTree(root, searchKey);
    if (result != NULL) {
        printf("找到值 %d 在树中\n", searchKey);
    } else {
        printf("未找到值 %d\n", searchKey);
    }
    
    // 释放内存
    freeTree(root);
    
    return 0;
}
*/

 	/*平衡二叉树*/ 
/* 	
// 定义AVL树节点结构
typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// 辅助函数：获取节点高度
int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// 辅助函数：计算平衡因子
int getBalanceFactor(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 辅助函数：获取两个数中的最大值
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 创建新节点
AVLNode* createNode(int value) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 右旋操作
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// 左旋操作
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// 插入节点到AVL树
AVLNode* insertNode(AVLNode* node, int value) {
    // 1. 执行标准的BST插入
    if (node == NULL)
        return createNode(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    else // 不允许重复值
        return node;

    // 2. 更新节点高度
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. 获取平衡因子，检查是否失衡
    int balance = getBalanceFactor(node);

    // 如果节点失衡，有4种情况

    // 左左情况
    if (balance > 1 && value < node->left->data)
        return rightRotate(node);

    // 右右情况
    if (balance < -1 && value > node->right->data)
        return leftRotate(node);

    // 左右情况
    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 右左情况
    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 返回未改变的节点指针
    return node;
}

// 查找最小值节点（用于删除操作）
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// 从AVL树中删除节点
AVLNode* deleteNode(AVLNode* root, int value) {
    // 1. 执行标准BST删除
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        // 找到要删除的节点
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;

            // 没有子节点的情况
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // 有一个子节点的情况
                *root = *temp; // 复制非空子节点的内容

            free(temp);
        } else {
            // 有两个子节点的情况：获取中序后继（右子树的最小值）
            AVLNode* temp = minValueNode(root->right);

            // 复制中序后继的数据到当前节点
            root->data = temp->data;

            // 删除中序后继
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // 如果树只有一个节点，直接返回
    if (root == NULL)
        return root;

    // 2. 更新当前节点的高度
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. 获取平衡因子，检查是否失衡
    int balance = getBalanceFactor(root);

    // 如果节点失衡，有4种情况

    // 左左情况
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // 左右情况
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // 右右情况
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // 右左情况
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 在AVL树中查找值
AVLNode* searchTree(AVLNode* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return searchTree(root->left, key);
    else
        return searchTree(root->right, key);
}

// 中序遍历树
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 前序遍历树（显示树结构）
void preorderTraversal(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 打印树形结构（辅助函数）
void printTreeUtil(AVLNode* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printTreeUtil(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    printTreeUtil(root->left, space);
}

// 打印树形结构
void printTree(AVLNode* root) {
    printTreeUtil(root, 0);
}

// 释放树的内存
void freeTree(AVLNode* root) {
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    AVLNode* root = NULL;
    
    // 插入节点
    printf("插入节点: 10, 20, 30, 40, 50, 25\n");
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);
    
    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("前序遍历结果: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("树形结构:\n");
    printTree(root);
    printf("\n");
    
    // 查找节点
    int searchKey = 30;
    AVLNode* result = searchTree(root, searchKey);
    if (result != NULL) {
        printf("找到值 %d 在树中\n", searchKey);
    } else {
        printf("未找到值 %d\n", searchKey);
    }
    
    searchKey = 35;
    result = searchTree(root, searchKey);
    if (result != NULL) {
        printf("找到值 %d 在树中\n", searchKey);
    } else {
        printf("未找到值 %d\n", searchKey);
    }
    
    // 删除节点
    printf("\n删除节点: 30\n");
    root = deleteNode(root, 30);
    
    printf("删除后的中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("删除后的树形结构:\n");
    printTree(root);
    printf("\n");
    
    // 释放内存
    freeTree(root);
    
    return 0;
}

*/

 /*红黑树*/ 

/*
// 定义节点颜色
typedef enum { RED, BLACK } Color;

// 定义红黑树节点结构
typedef struct RBNode {
    int data;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

// 创建新节点 
RBNode* createNode(int value) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = value;
    newNode->color = RED; // 新节点总是红色
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// 左旋操作
void leftRotate(RBNode** root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    
    if (y->left != NULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

// 右旋操作
void rightRotate(RBNode** root, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    
    if (x->right != NULL)
        x->right->parent = y;
    
    x->parent = y->parent;
    
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

// 插入修复操作
void fixInsert(RBNode** root, RBNode* z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            
            // 情况1：叔叔节点是红色
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // 情况2：z是右孩子
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                // 情况3：z是左孩子
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            // 对称的情况
            RBNode* y = z->parent->parent->left;
            
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; // 根节点总是黑色
}

// 插入节点到红黑树
void insertNode(RBNode** root, int value) {
    RBNode* z = createNode(value);
    RBNode* y = NULL;
    RBNode* x = *root;
    
    // 标准BST插入
    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;
    
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    
    // 修复红黑树性质
    fixInsert(root, z);
}

// 查找最小值节点
RBNode* minValueNode(RBNode* node) {
    RBNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// 查找节点
RBNode* searchTree(RBNode* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    
    if (key < root->data)
        return searchTree(root->left, key);
    else
        return searchTree(root->right, key);
}

// 中序遍历
void inorderTraversal(RBNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "RED" : "BLACK");
        inorderTraversal(root->right);
    }
}

// 前序遍历
void preorderTraversal(RBNode* root) {
    if (root != NULL) {
        printf("%d(%s) ", root->data, root->color == RED ? "RED" : "BLACK");
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 打印树形结构（辅助函数）
void printTreeUtil(RBNode* root, int space) {
    if (root == NULL)
        return;
    
    space += 10;
    
    printTreeUtil(root->right, space);
    
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d(%s)\n", root->data, root->color == RED ? "R" : "B");
    
    printTreeUtil(root->left, space);
}

// 打印树形结构
void printTree(RBNode* root) {
    printTreeUtil(root, 0);
}

// 释放树的内存
void freeTree(RBNode* root) {
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 验证红黑树性质
int checkRBProperties(RBNode* root, int* blackCount, int pathBlackCount) {
    if (root == NULL) {
        if (*blackCount == -1)
            *blackCount = pathBlackCount;
        return pathBlackCount == *blackCount;
    }
    
    // 检查红色节点的子节点必须是黑色
    if (root->color == RED) {
        if ((root->left != NULL && root->left->color == RED) ||
            (root->right != NULL && root->right->color == RED)) {
            return 0;
        }
    }
    
    // 递归检查左右子树
    int currentBlackCount = pathBlackCount + (root->color == BLACK ? 1 : 0);
    
    return checkRBProperties(root->left, blackCount, currentBlackCount) &&
           checkRBProperties(root->right, blackCount, currentBlackCount);
}

// 验证红黑树
int validateRBTree(RBNode* root) {
    if (root == NULL) return 1;
    
    // 性质2：根节点必须是黑色
    if (root->color != BLACK) {
        printf("错误：根节点不是黑色\n");
        return 0;
    }
    
    int blackCount = -1;
    return checkRBProperties(root, &blackCount, 0);
}

int main() {
    RBNode* root = NULL;
    
    printf("插入节点: 10, 20, 30, 40, 50, 25, 5, 15\n");
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 40);
    insertNode(&root, 50);
    insertNode(&root, 25);
    insertNode(&root, 5);
    insertNode(&root, 15);
    
    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("前序遍历结果: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("树形结构:\n");
    printTree(root);
    printf("\n");
    
    // 验证红黑树性质
    if (validateRBTree(root)) {
        printf("红黑树性质验证通过\n");
    } else {
        printf("红黑树性质验证失败\n");
    }
    
    // 查找节点
    int searchKey = 30;
    RBNode* result = searchTree(root, searchKey);
    if (result != NULL) {
        printf("找到值 %d 在树中，颜色: %s\n", searchKey, 
               result->color == RED ? "RED" : "BLACK");
    } else {
        printf("未找到值 %d\n", searchKey);
    }
    
    searchKey = 35;
    result = searchTree(root, searchKey);
    if (result != NULL) {
        printf("找到值 %d 在树中，颜色: %s\n", searchKey, 
               result->color == RED ? "RED" : "BLACK");
    } else {
        printf("未找到值 %d\n", searchKey);
    }
    
    // 释放内存
    freeTree(root);
    
    return 0;
}
*/

/*B树*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEYS 3  // B树的阶数，最大键值数为2t-1

typedef struct BTreeNode {
    int keys[MAX_KEYS];          // 键值数组
    struct BTreeNode* children[MAX_KEYS + 1]; // 子节点指针数组
    int num_keys;                // 当前键值数量
    bool is_leaf;                // 是否为叶子节点
} BTreeNode;

// 创建新节点
BTreeNode* createNode(bool is_leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;
    for (int i = 0; i <= MAX_KEYS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// 分裂子节点
void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* newChild = createNode(child->is_leaf);
    newChild->num_keys = MAX_KEYS / 2;
    
    // 复制后半部分键值到新节点
    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newChild->keys[i] = child->keys[i + MAX_KEYS / 2 + 1];
    }
    
    // 如果不是叶子节点，复制子节点指针
    if (!child->is_leaf) {
        for (int i = 0; i <= MAX_KEYS / 2; i++) {
            newChild->children[i] = child->children[i + MAX_KEYS / 2 + 1];
        }
    }
    
    child->num_keys = MAX_KEYS / 2;
    
    // 为父节点腾出空间
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;
    
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    
    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->num_keys++;
}

// 插入键值（非满节点）
void insertNonFull(BTreeNode* node, int key) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        // 叶子节点，直接插入
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // 找到合适的子节点
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        // 如果子节点已满，先分裂
        if (node->children[i]->num_keys == MAX_KEYS) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// 插入键值
BTreeNode* insert(BTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = key;
        root->num_keys = 1;
        return root;
    }
    
    // 如果根节点已满，需要分裂
    if (root->num_keys == MAX_KEYS) {
        BTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        
        // 决定插入到哪个子节点
        int i = 0;
        if (key > newRoot->keys[0]) {
            i++;
        }
        insertNonFull(newRoot->children[i], key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// 查找键值
bool search(BTreeNode* root, int key) {
    if (root == NULL) return false;
    
    int i = 0;
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }
    
    if (i < root->num_keys && key == root->keys[i]) {
        return true;
    }
    
    if (root->is_leaf) {
        return false;
    }
    
    return search(root->children[i], key);
}

// 打印B树
void printBTree(BTreeNode* root, int level) {
    if (root != NULL) {
        printf("Level %d: ", level);
        for (int i = 0; i < root->num_keys; i++) {
            printf("%d ", root->keys[i]);
        }
        printf("\n");
        
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                printBTree(root->children[i], level + 1);
            }
        }
    }
}

// 释放B树内存
void freeBTree(BTreeNode* root) {
    if (root != NULL) {
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                freeBTree(root->children[i]);
            }
        }
        free(root);
    }
}

// B树测试
void testBTree() {
    printf("=== B树测试 ===\n");
    BTreeNode* root = NULL;
    
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 25};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        printf("插入: %d\n", keys[i]);
        root = insert(root, keys[i]);
        printBTree(root, 0);
        printf("\n");
    }
    
    // 测试查找
    printf("查找 12: %s\n", search(root, 12) ? "找到" : "未找到");
    printf("查找 100: %s\n", search(root, 100) ? "找到" : "未找到");
    
    freeBTree(root);
} 


#define MAX_KEYS 3  // B+树的阶数

typedef struct BPlusTreeNode {
    int keys[MAX_KEYS];          // 键值数组
    void* pointers[MAX_KEYS + 1]; // 指针数组（子节点或数据）
    int num_keys;                // 当前键值数量
    bool is_leaf;                // 是否为叶子节点
    struct BPlusTreeNode* next;  // 叶子节点的下一个节点（用于范围查询）
} BPlusTreeNode;

// 创建新节点
BPlusTreeNode* createBPlusNode(bool is_leaf) {
    BPlusTreeNode* newNode = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;
    newNode->next = NULL;
    for (int i = 0; i <= MAX_KEYS; i++) {
        newNode->pointers[i] = NULL;
    }
    return newNode;
}

// 分裂叶子节点
void splitLeafNode(BPlusTreeNode* leaf, BPlusTreeNode** new_leaf) {
    *new_leaf = createBPlusNode(true);
    
    int split_index = MAX_KEYS / 2;
    (*new_leaf)->num_keys = MAX_KEYS - split_index;
    
    // 复制后半部分键值和数据
    for (int i = 0; i < (*new_leaf)->num_keys; i++) {
        (*new_leaf)->keys[i] = leaf->keys[split_index + i];
        (*new_leaf)->pointers[i] = leaf->pointers[split_index + i];
    }
    
    leaf->num_keys = split_index;
    (*new_leaf)->next = leaf->next;
    leaf->next = *new_leaf;
}

// 分裂内部节点
void splitInternalNode(BPlusTreeNode* node, BPlusTreeNode** new_node, int* promote_key) {
    *new_node = createBPlusNode(false);
    
    int split_index = MAX_KEYS / 2;
    *promote_key = node->keys[split_index];
    (*new_node)->num_keys = MAX_KEYS - split_index - 1;
    
    // 复制后半部分键值和指针
    for (int i = 0; i < (*new_node)->num_keys; i++) {
        (*new_node)->keys[i] = node->keys[split_index + 1 + i];
        (*new_node)->pointers[i] = node->pointers[split_index + 1 + i];
    }
    (*new_node)->pointers[(*new_node)->num_keys] = node->pointers[MAX_KEYS];
    
    node->num_keys = split_index;
}

// 插入键值到B+树
BPlusTreeNode* insertBPlus(BPlusTreeNode* root, int key, void* data) {
    if (root == NULL) {
        root = createBPlusNode(true);
        root->keys[0] = key;
        root->pointers[0] = data;
        root->num_keys = 1;
        return root;
    }
    
    // 查找插入位置
    BPlusTreeNode* current = root;
    BPlusTreeNode* parent = NULL;
    int parent_index = 0;
    
    while (!current->is_leaf) {
        parent = current;
        int i = 0;
        while (i < current->num_keys && key >= current->keys[i]) {
            i++;
        }
        current = (BPlusTreeNode*)current->pointers[i];
        parent_index = i;
    }
    
    // 在叶子节点中插入
    int insert_pos = 0;
    while (insert_pos < current->num_keys && key > current->keys[insert_pos]) {
        insert_pos++;
    }
    
    // 移动键值为新键值腾出空间
    for (int i = current->num_keys; i > insert_pos; i--) {
        current->keys[i] = current->keys[i - 1];
        current->pointers[i] = current->pointers[i - 1];
    }
    
    current->keys[insert_pos] = key;
    current->pointers[insert_pos] = data;
    current->num_keys++;
    
    // 如果叶子节点已满，需要分裂
    if (current->num_keys == MAX_KEYS) {
        BPlusTreeNode* new_leaf;
        splitLeafNode(current, &new_leaf);
        
        if (parent == NULL) {
            // 创建新的根节点
            BPlusTreeNode* new_root = createBPlusNode(false);
            new_root->keys[0] = new_leaf->keys[0];
            new_root->pointers[0] = current;
            new_root->pointers[1] = new_leaf;
            new_root->num_keys = 1;
            return new_root;
        } else {
            // 在父节点中插入
            int promote_key = new_leaf->keys[0];
            
            // 在父节点中找到插入位置
            int insert_pos_parent = 0;
            while (insert_pos_parent < parent->num_keys && promote_key > parent->keys[insert_pos_parent]) {
                insert_pos_parent++;
            }
            
            // 移动键值和指针
            for (int i = parent->num_keys; i > insert_pos_parent; i--) {
                parent->keys[i] = parent->keys[i - 1];
                parent->pointers[i + 1] = parent->pointers[i];
            }
            
            parent->keys[insert_pos_parent] = promote_key;
            parent->pointers[insert_pos_parent + 1] = new_leaf;
            parent->num_keys++;
            
            // 检查父节点是否需要分裂
            if (parent->num_keys == MAX_KEYS) {
                // 需要处理内部节点分裂（简化实现）
            }
        }
    }
    
    return root;
}

// 查找键值
void* searchBPlus(BPlusTreeNode* root, int key) {
    if (root == NULL) return NULL;
    
    BPlusTreeNode* current = root;
    while (!current->is_leaf) {
        int i = 0;
        while (i < current->num_keys && key >= current->keys[i]) {
            i++;
        }
        current = (BPlusTreeNode*)current->pointers[i];
    }
    
    for (int i = 0; i < current->num_keys; i++) {
        if (current->keys[i] == key) {
            return current->pointers[i];
        }
    }
    
    return NULL;
}

// 范围查询
void rangeQuery(BPlusTreeNode* root, int start, int end) {
    if (root == NULL) return;
    
    // 找到起始键值所在的叶子节点
    BPlusTreeNode* current = root;
    while (!current->is_leaf) {
        int i = 0;
        while (i < current->num_keys && start >= current->keys[i]) {
            i++;
        }
        current = (BPlusTreeNode*)current->pointers[i];
    }
    
    printf("范围查询 %d 到 %d: ", start, end);
    
    // 遍历叶子节点链表
    while (current != NULL) {
        for (int i = 0; i < current->num_keys; i++) {
            if (current->keys[i] >= start && current->keys[i] <= end) {
                printf("%d ", current->keys[i]);
            }
            if (current->keys[i] > end) {
                return;
            }
        }
        current = current->next;
    }
    printf("\n");
}

// 打印B+树
void printBPlusTree(BPlusTreeNode* root, int level) {
    if (root != NULL) {
        printf("Level %d: ", level);
        for (int i = 0; i < root->num_keys; i++) {
            printf("%d ", root->keys[i]);
        }
        printf("\n");
        
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                printBPlusTree((BPlusTreeNode*)root->pointers[i], level + 1);
            }
        }
    }
}

// 释放B+树内存
void freeBPlusTree(BPlusTreeNode* root) {
    if (root != NULL) {
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                freeBPlusTree((BPlusTreeNode*)root->pointers[i]);
            }
        }
        free(root);
    }
}

// B+树测试
void testBPlusTree() {
    printf("\n=== B+树测试 ===\n");
    BPlusTreeNode* root = NULL;
    
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 25};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        printf("插入: %d\n", keys[i]);
        int* data = malloc(sizeof(int));
        *data = keys[i] * 10; // 示例数据
        root = insertBPlus(root, keys[i], data);
        printBPlusTree(root, 0);
        printf("\n");
    }
    
    // 测试查找
    printf("查找 12: ");
    int* result = (int*)searchBPlus(root, 12);
    if (result != NULL) {
        printf("找到，数据: %d\n", *result);
    } else {
        printf("未找到\n");
    }
    
    // 范围查询
    rangeQuery(root, 5, 20);
    
    freeBPlusTree(root);
}

int main() {
    testBTree();
    testBPlusTree();
    return 0;
}
