#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

/* ---------- 辅助函数 ---------- */

/* 二分查找（标准），用于对照 */
int binary_search(const int *a, int n, int key) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == key) return mid;
        if (a[mid] < key) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

/* ---------- 分块查找核心 ---------- */

/* 
 * 根据块大小 B（建议 B≈sqrt(n)）构建索引数组 idx。
 * 返回块的数量（即 idx 的长度），并通过 *idx_out 参数返回指向索引数组的指针。
 * 备注：调用者在不再使用时需要 free(idx)。
 */
int build_index(const int *a, int n, int B, int **idx_out) {
    if (B <= 0) B = 1;
    int block_cnt = (n + B - 1) / B;               // 向上取整
    int *idx = (int *)malloc(block_cnt * sizeof(int));
    if (!idx) {
        perror("malloc idx");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < block_cnt; ++i) {
        int end = (i + 1) * B;
        if (end > n) end = n;
        // 由于数组整体有序，块的最大值就是该块最后一个元素
        idx[i] = a[end - 1];
    }
    *idx_out = idx;
    return block_cnt;
}

/* 
 * 分块查找
 *   a      : 已排序的原数组
 *   n      : 原数组长度
 *   B      : 块大小（与 build_index 使用的保持一致）
 *   idx    : 索引数组（由 build_index 生成）
 *   block_cnt : 索引数组长度
 *   key    : 待查找的目标值
 * 返回 key 在 a 中的下标，未找到返回 -1。
 */
int block_search(const int *a, int n, int B,
                 const int *idx, int block_cnt, int key) {
    // 1?? 在索引数组上二分定位块
    int left = 0, right = block_cnt - 1;
    int block_id = -1;               // 目标可能所在的块号
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (idx[mid] >= key) {
            block_id = mid;          // 可能在该块或更左侧块
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (block_id == -1) return -1;   // 所有块的最大值都小于 key

    // 2?? 在块内部线性搜索（块大小一般不大，线性足够快）
    int start = block_id * B;
    int end   = start + B;
    if (end > n) end = n;            // 处理最后一个不完整块

    for (int i = start; i < end; ++i) {
        if (a[i] == key) return i;
    }
    return -1;
}

/* ---------- 演示程序 ---------- */

int main(void) {
    const int N = 1000000;                  // 1e6 个有序整数
    int *data = malloc(N * sizeof(int));
    if (!data) {
        perror("malloc data");
        return EXIT_FAILURE;
    }

    // 构造递增数组：data[i] = i*2（保证唯一且有序）
    for (int i = 0; i < N; ++i) {
        data[i] = i * 2;
    }

    // 选取块大小 B≈sqrt(N)
    int B = (int)sqrt(N);
    int *idx = NULL;
    int block_cnt = build_index(data, N, B, &idx);

    // 随机挑选若干查询键，包含存在和不存在的情况
    const int TESTS = 10;
    int keys[TESTS];
    srand((unsigned)time(NULL));
    for (int i = 0; i < TESTS; ++i) {
        // 50% 概率在数组中，50% 概率在数组外
        if (rand() % 2) {
            // 在数组中：随机取一个索引再映射回原值
            int idx_rand = rand() % N;
            keys[i] = data[idx_rand];
        } else {
            // 在数组外：取奇数（数组全为偶数）
            keys[i] = rand() % (2 * N) | 1;   // 确保为奇数
        }
    }

    printf("块大小 B = %d, 块数 = %d\n", B, block_cnt);
    printf("=== 查询结果 ===\n");
    for (int i = 0; i < TESTS; ++i) {
        int key = keys[i];
        int pos_block = block_search(data, N, B, idx, block_cnt, key);
        int pos_bin   = binary_search(data, N, key);
        printf("key = %6d | block_search = %4d | binary_search = %4d\n",
               key, pos_block, pos_bin);
    }

    free(data);
    free(idx);
    return 0;
}

