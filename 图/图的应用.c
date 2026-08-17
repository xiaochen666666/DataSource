#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5       // 图中顶点数量
#define INF INT_MAX

// 图的最小生成树算法
// Prim算法实现
void primMST(int graph[V][V]) {
	int parent[V];     // 记录最小生成树的父节点
	int key[V];        // 记录各顶点权重值
	int mstSet[V];     // 记录顶点是否加入集合
	int i; 

	// 初始化所有键值为无穷大
	for (i = 0; i < V; i++) {
		key[i] = INF;
		mstSet[i] = 0;
	}

	key[0] = 0;        // 从第0个顶点开始
	parent[0] = -1;    // 第一个节点总是根节点

	int count,v;
	for (count = 0; count < V-1; count++) {
		// 选取未处理顶点中键值最小的顶点
		int min = INF, u;
		for (v = 0; v < V; v++)
			if (!mstSet[v] && key[v] < min)
				min = key[v], u = v;

		mstSet[u] = 1;  // 将顶点加入集合

		// 更新相邻顶点的键值
		for (v = 0; v < V; v++)
			if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// 打印结果
	printf("Prim算法生成的最小生成树：\n");
	for (i = 1; i < V; i++)
		printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

// Kruskal算法实现需要的辅助结构
struct Edge {
	int src, dest, weight;
};

int find(int parent[], int i) {
	if (parent[i] == -1)
		return i;
	return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
	parent[x] = y;
}

int compare(const void* a, const void* b) {
	return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal算法
void kruskalMST(struct Edge edges[], int E) {
	struct Edge result[V];
	int e = 0;      // 结果数组索引
	int i = 0;      // 已排序边的索引
	int parent[V];
    
    int v;
	// 初始化父节点数组
	for (v = 0; v < V; v++)
		parent[v] = -1;

	// 按权重排序所有边
	qsort(edges, E, sizeof(edges[0]), compare);

	while (e < V-1 && i < E) {
		struct Edge next_edge = edges[i++];
		int x = find(parent, next_edge.src);
		int y = find(parent, next_edge.dest);

		if (x != y) {  // 不形成环路
			result[e++] = next_edge;
			Union(parent, x, y);
		}
	}

	// 打印结果
	printf("Kruskal算法生成的最小生成树：\n");
	for (i = 0; i < e; i++)
		printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
}

// Dijkstra最短路径算法
void dijkstra(int graph[V][V], int src) {
	int dist[V];     // 最短距离数组
	int visited[V];  // 已处理顶点标记
 
 	int i,count,v;
	for (i = 0; i < V; i++)
		dist[i] = INF, visited[i] = 0;

	dist[src] = 0;

	for (count = 0; count < V-1; count++) {
		int u, min = INF;
		for (v = 0; v < V; v++)
			if (!visited[v] && dist[v] <= min)
				min = dist[v], u = v;

		visited[u] = 1;

		for (v = 0; v < V; v++)
			if (!visited[v] && graph[u][v] && dist[u] != INF
			        && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	printf("Dijkstra最短路径结果（起点%d）:\n", src);
	for (i = 0; i < V; i++)
		printf("%d \t %d\n", i, dist[i]);
}

// Floyd最短路径算法
void floydWarshall(int graph[V][V]) {
	int dist[V][V], i, j, k;

	// 初始化距离矩阵
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

	// 通过每个顶点进行中转
	for (k = 0; k < V; k++) {
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				if (dist[i][k] != INF && dist[k][j] != INF
				        && dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	printf("Floyd算法的最短路径矩阵：\n");
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				printf("INF\t");
			else
				printf("%d\t", dist[i][j]);
		}
		printf("\n");
	}
}

int main() {
	// Prim测试图
	int primGraph[V][V] = { { 0, 2, 0, 6, 0 },
		{ 2, 0, 3, 8, 5 },
		{ 0, 3, 0, 0, 7 },
		{ 6, 8, 0, 0, 9 },
		{ 0, 5, 7, 9, 0 }
	};

	// Kruskal测试数据
	struct Edge edges[] = {
		{0, 1, 2}, {0, 3, 6},
		{1, 2, 3}, {1, 3, 8},
		{1, 4, 5}, {2, 4, 7},
		{3, 4, 9}
	};
	int E = sizeof(edges)/sizeof(edges[0]);

	// Dijkstra测试图
	int dijkstraGraph[V][V] = { {0, 4, 0, 0, 0},
		{4, 0, 8, 0, 0},
		{0, 8, 0, 7, 0},
		{0, 0, 7, 0, 9},
		{0, 0, 0, 9, 0}
	};

	// Floyd测试图（有向图示例）
	int floydGraph[V][V] = { {0,   3,  8, INF, -4},
		{INF, 0, INF, 1, 7},
		{INF, 4, 0, INF, INF},
		{2, INF, -5, 0, INF},
		{INF, INF, INF, 6, 0}
	};

	// 执行算法
	primMST(primGraph);
	kruskalMST(edges, E);
	dijkstra(dijkstraGraph, 0);
	floydWarshall(floydGraph);

	return 0;
}

