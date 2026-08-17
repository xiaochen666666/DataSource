#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadNode {
    int data;
    struct ThreadNode *lchild, *rchild, *parent;
    int ltag, rtag; // 0表示孩子，1表示线索
} ThreadNode, *ThreadTree;

// 辅助函数：创建新节点并设置父指针
ThreadNode* CreateThreadNode(int value, ThreadNode* parent) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = value;
    newNode->lchild = newNode->rchild = NULL;
    newNode->parent = parent;
    newNode->ltag = newNode->rtag = 0;
    return newNode;
}

// 中序线索化递归函数
void InThread(ThreadTree p, ThreadTree *pre) {
    if (p != NULL) {
        InThread(p->lchild, pre);
        
        if (p->lchild == NULL) {
            p->lchild = *pre;
            p->ltag = 1;
        }
        
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rchild = p;
            (*pre)->rtag = 1;
        }
        
        *pre = p;
        InThread(p->rchild, pre);
    }
}

void CreateInThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        InThread(T, &pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}

void InOrderTraverse_Thr(ThreadTree T) {
    ThreadNode* p = T;
    while (p != NULL) {
        while (p->ltag == 0) {
            p = p->lchild;
        }
        
        printf("%d ", p->data);
        
        while (p->rtag == 1 && p->rchild != NULL) {
            p = p->rchild;
            printf("%d ", p->data);
        }
        
        p = p->rchild;
    }
    printf("\n");
}

// 先序线索化递归函数
void PreThread(ThreadTree p, ThreadTree *pre) {
    if (p != NULL) {
        if (p->lchild == NULL) {
            p->lchild = *pre;
            p->ltag = 1;
        }
        
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rchild = p;
            (*pre)->rtag = 1;
        }
        
        *pre = p;
        
        // 只有当左孩子不是线索时才递归处理
        if (p->ltag == 0) {
            PreThread(p->lchild, pre);
        }
        
        // 只有当右孩子不是线索时才递归处理
        if (p->rtag == 0) {
            PreThread(p->rchild, pre);
        }
    }
}

void CreatePreThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        PreThread(T, &pre);
        // 处理最后一个节点的右指针
        if (pre->rchild == NULL) {
            pre->rtag = 1;
        }
    }
}

// 先序线索二叉树遍历
void PreOrderTraverse_Thr(ThreadTree T) {
    ThreadNode* p = T;
    while (p != NULL) {
        printf("%d ", p->data);
        
        if (p->ltag == 0) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    printf("\n");
}

// 后序线索化递归函数
void PostThread(ThreadTree p, ThreadTree *pre) {
    if (p != NULL) {
        PostThread(p->lchild, pre);
        PostThread(p->rchild, pre);
        
        if (p->lchild == NULL) {
            p->lchild = *pre;
            p->ltag = 1;
        }
        
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rchild = p;
            (*pre)->rtag = 1;
        }
        
        *pre = p;
    }
}

void CreatePostThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        PostThread(T, &pre);
    }
}

// 后序线索二叉树遍历
void PostOrderTraverse_Thr(ThreadTree T) {
    if (T == NULL) return;
    
    // 找到后序序列的第一个节点
    ThreadNode* p = T;
    while (1) {
        // 尽可能向左下走
        while (p->ltag == 0) {
            p = p->lchild;
        }
        // 如果有右孩子且不是线索，转向右
        if (p->rtag == 0 && p->rchild != NULL) {
            p = p->rchild;
        } else {
            break; // 找到第一个节点
        }
    }
    
    while (p != NULL) {
        printf("%d ", p->data);
        
        // 如果有后继线索
        if (p->rtag == 1) {
            p = p->rchild;
        } else {
            // 通过父指针找到后继
            ThreadNode* parent = p->parent;
            
            if (parent == NULL) {
                p = NULL; // 根节点，遍历结束
            } 
            // 如果当前节点是父节点的右孩子，或者父节点没有右孩子
            else if (parent->rchild == p || parent->rtag == 1) {
                p = parent;
            } 
            else {
                // 否则转向父节点的右子树
                p = parent->rchild;
                // 找到右子树的后序第一个节点
                while (1) {
                    while (p->ltag == 0) {
                        p = p->lchild;
                    }
                    if (p->rtag == 0 && p->rchild != NULL) {
                        p = p->rchild;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    printf("\n");
}

int main() {
    // 构建二叉树并设置父指针
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    ThreadTree root = CreateThreadNode(1, NULL);
    root->lchild = CreateThreadNode(2, root);
    root->rchild = CreateThreadNode(3, root);
    root->lchild->lchild = CreateThreadNode(4, root->lchild);
    root->lchild->rchild = CreateThreadNode(5, root->lchild);
    
    printf("Original Tree:\n");
    printf("    1\n   / \\\n  2   3\n / \\\n4   5\n\n");
    
    // 测试中序线索化
    printf("InOrder Thread Traverse: ");
    CreateInThread(root);
    InOrderTraverse_Thr(root); // 输出: 4 2 5 1 3
    
    // 重新构建树测试先序线索化
    root = CreateThreadNode(1, NULL);
    root->lchild = CreateThreadNode(2, root);
    root->rchild = CreateThreadNode(3, root);
    root->lchild->lchild = CreateThreadNode(4, root->lchild);
    root->lchild->rchild = CreateThreadNode(5, root->lchild);
    
    printf("PreOrder Thread Traverse: ");
    CreatePreThread(root);
    PreOrderTraverse_Thr(root); // 应输出: 1 2 4 5 3
    
    // 重新构建树测试后序线索化
    root = CreateThreadNode(1, NULL);
    root->lchild = CreateThreadNode(2, root);
    root->rchild = CreateThreadNode(3, root);
    root->lchild->lchild = CreateThreadNode(4, root->lchild);
    root->lchild->rchild = CreateThreadNode(5, root->lchild);
    
    printf("PostOrder Thread Traverse: ");
    CreatePostThread(root);
    PostOrderTraverse_Thr(root); // 应输出: 4 5 2 3 1
    
    return 0;
}
