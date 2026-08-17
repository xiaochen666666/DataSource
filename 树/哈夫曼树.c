#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// 哈夫曼树节点结构体
struct MinHeapNode {
    char data;                // 字符
    unsigned freq;            // 频率
    struct MinHeapNode *left, *right; // 左右子节点
};

// 最小堆结构体
struct MinHeap {
    unsigned size;            // 当前堆大小
    unsigned capacity;        // 堆容量
    struct MinHeapNode** array; // 节点指针数组
};

// 创建一个新的哈夫曼树节点
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->left = node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

// 创建一个最小堆
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 交换两个最小堆节点
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// 最小堆化
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 检查堆大小是否为1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 提取最小堆中的最小节点
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 插入节点到最小堆
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// 构建最小堆
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// 打印数组
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// 判断是否是叶子节点
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// 创建并构建最小堆
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    int i; 
    for ( i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// 构建哈夫曼树
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    
    // 第1步：创建最小堆
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // 直到堆中只剩一个节点
    while (!isSizeOne(minHeap)) {
        // 第2步：提取两个频率最小的节点
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // 第3步：创建一个新的内部节点，频率为两个节点频率之和
        // '$'表示内部节点，没有实际字符
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // 第4步：剩下的节点就是哈夫曼树的根节点
    return extractMin(minHeap);
}

// 打印哈夫曼编码
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    // 左子树编码为0
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // 右子树编码为1
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // 如果是叶子节点，打印字符和编码
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

// 哈夫曼编码主函数
void HuffmanCodes(char data[], int freq[], int size) {
    // 构建哈夫曼树
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // 打印哈夫曼编码
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

// 主函数
int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("字符及其哈夫曼编码:\n");
    HuffmanCodes(arr, freq, size);

    return 0;
}
