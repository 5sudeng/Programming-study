# Graph Traversals (DFT, BFT)

## Depth-First Traversal (DFT; 깊이 우선 탐색)
- 최대한 깊이 이동한 다음, 더이상 갈 수 없을 때 옆으로 이동
    - `preorder`: 나를 방문하고 자녀 탐색 (e.g. directory listing) &rarr; 아래 코드들은 `preorder` 구현
    - `inorder`: 자녀 탐색 중에 나를 방문 (e.g. flatten BST to sorted list)
    - `postorder`: 자녀 탐색 끝나고 나를 방문 (e.g. file size calculation)
- `stack`을 이용하거나, recursively 수행
- cycle이 있을 수 있으므로 `visited` 변수로 이미 방문한 노드 관리
- disconnected nodes가 있을 수 있으므로 모든 노드에 대해 for-loop 사용
- $O(V+E)$ with adjacency list

``` C
// C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a node in the adjacency list
struct Node {
	int data;
	struct Node* next;
};

// Structure for the adjacency list
struct List {
	struct Node* head;
};

// Structure for the graph
struct Graph {
	int vertices;
	struct List* array;
};

// Function to create a new node
struct Node* createNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));

	for (int i = 0; i < vertices; i++) {
		graph->array[i].head = NULL;
	}

	return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Uncomment the following code to make the graph undirected
	/*
	newNode = createNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
	*/
}

// Function to perform Depth First Search (DFS) from a given vertex
void DFS(struct Graph* graph, int vertex, bool visited[]) {
	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;
	while (currentNode) {
		int adjacentVertex = currentNode->data;
		if (!visited[adjacentVertex]) {
			DFS(graph, adjacentVertex, visited);
		}
		currentNode = currentNode->next;
	}
}

// Function to perform DFS traversal from a given vertex in a specified order
void DFSTraversal(struct Graph* graph, int* order, int orderSize) {
	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	for (int i = 0; i < graph->vertices; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < orderSize; i++) {
		if (!visited[order[i]]) {
			DFS(graph, order[i], visited);
		}
	}

	free(visited);
}

int main() {
	int vertices = 4;
	struct Graph* graph = createGraph(vertices);

	addEdge(graph, 2, 0);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 1);
	addEdge(graph, 3, 3);
	addEdge(graph, 1, 3);

	int order[] = {2, 0, 1, 3};
	int orderSize = sizeof(order) / sizeof(order[0]);

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
```

``` C++
// C++
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
    map<int, bool> visited;
    map<int, list<int> > adj;

    // Function to add an edge to graph
    void addEdge(int v, int w);

    // DFS traversal of the vertices reachable from v
    void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
    // Add w to v’s list.
    adj[v].push_back(w);
}

void Graph::DFS(int v)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}
```

## Breath-First Traversal (BFT; 너비 우선 탐색)
- 최대한 넓게 이동한 다음, 더이상 갈 수 없을 때 아래로 이동
- `queue`를 이용하여 방문할 노드 관리

``` C
// C
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in adjacency list
struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data)
{
    struct Node* newNode
        = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adjList[], int u, int v)
{
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void bfs(struct Node* adjList[], int vertices,
         int startNode, int visited[])
{
    // Create a queue for BFS
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    visited[startNode] = 1;
    queue[rear++] = startNode;

    // Iterate over the queue
    while (front != rear) {
        // Dequeue a vertex from queue and print it
        int currentNode = queue[front++];
        printf("%d ", currentNode);

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent has not been visited, mark it visited and enqueue it
        struct Node* temp = adjList[currentNode];
        while (temp != NULL) {
            int neighbor = temp->data;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int vertices = 5;
    struct Node* adjList[vertices];
    for (int i = 0; i < vertices; ++i)
        adjList[i] = NULL;

    // Add edges to the graph
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 4);

    // Mark all the vertices as not visited
    int visited[vertices];
    for (int i = 0; i < vertices; ++i)
        visited[i] = 0;

    // Perform BFS traversal starting from vertex 0
    printf(
        "Breadth First Traversal starting from vertex 0: ");
    bfs(adjList, vertices, 0, visited);

    return 0;
}
```

``` C++
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void bfs(vector<vector<int> >& adjList, int startNode, vector<bool>& visited)
{
    // Create a queue for BFS
    queue<int> q;

    // Mark the current node as visited and enqueue it
    visited[startNode] = true;
    q.push(startNode);

    // Iterate over the queue
    while (!q.empty()) {
        // Dequeue a vertex from queue and print it
        int currentNode = q.front(); q.pop();
        cout << currentNode << " ";

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent has not been visited, mark it visited and enqueue it
        for (int neighbor : adjList[currentNode]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void addEdge(vector<vector<int> >& adjList, int u, int v)
{
    adjList[u].push_back(v);
}

int main()
{
    int vertices = 5;
    vector<vector<int> > adjList(vertices);

    // Add edges to the graph
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 4);

    // Mark all the vertices as not visited
    vector<bool> visited(vertices, false);

    // Perform BFS traversal starting from vertex 0
    cout << "Breadth First Traversal starting from vertex "
            "0: ";
    bfs(adjList, 0, visited);

    return 0;
}
```

## References
- [text](https://www.geeksforgeeks.org/c-program-for-depth-first-search-or-dfs-for-a-graph/)
- [text](https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/?ref=previous_article)
- [text](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)