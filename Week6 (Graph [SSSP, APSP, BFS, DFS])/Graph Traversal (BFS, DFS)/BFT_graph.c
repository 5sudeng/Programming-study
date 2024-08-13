// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX_VERTICES 100

// typedef struct {
//     int vertices[MAX_VERTICES];
//     int adjacencyList[MAX_VERTICES][MAX_VERTICES];
//     int vertexCount;
//     int edgeCount[MAX_VERTICES];
// } Graph;

// typedef struct {
//     int items[MAX_VERTICES];
//     int front;
//     int rear;
// } Queue;

// void initializeGraph(Graph* g, int vertexCount) {
//     g->vertexCount = vertexCount;
//     for (int i = 0; i < vertexCount; i++) {
//         g->vertices[i] = i;
//         g->edgeCount[i] = 0;
//     }
// }

// void addEdge(Graph* g, int v, int w) {
//     g->adjacencyList[v][g->edgeCount[v]++] = w;
//     g->adjacencyList[w][g->edgeCount[w]++] = v; // For undirected graph
// }

// void initializeQueue(Queue* q) {
//     q->front = -1;
//     q->rear = -1;
// }

// bool isQueueEmpty(Queue* q) {
//     return q->rear == -1;
// }

// void enqueue(Queue* q, int value) {
//     if (q->rear == MAX_VERTICES - 1) {
//         printf("Queue is full\n");
//         return;
//     }
//     if (isQueueEmpty(q)) {
//         q->front = 0;
//     }
//     q->items[++q->rear] = value;
// }

// int dequeue(Queue* q) {
//     if (isQueueEmpty(q)) {
//         printf("Queue is empty\n");
//         return -1;
//     }
//     int item = q->items[q->front];
//     if (q->front >= q->rear) {
//         q->front = -1;
//         q->rear = -1;
//     } else {
//         q->front++;
//     }
//     return item;
// }


// void BFS_Helper(Graph* g, int startVertex, bool* visited) {
//     Queue q;
//     initializeQueue(&q);

//     visited[startVertex] = true;
//     enqueue(&q, startVertex);

//     while (!isQueueEmpty(&q)) {
//         int currentVertex = dequeue(&q);
//         printf("%d ", currentVertex);

//         for (int i = 0; i < g->edgeCount[currentVertex]; i++) {
//             int adjVertex = g->adjacencyList[currentVertex][i];
//             if (!visited[adjVertex]) {
//                 visited[adjVertex] = true;
//                 enqueue(&q, adjVertex);
//             }
//         }
//     }
// }

// void BFS(Graph* g, int startNode) {
//     bool visited[MAX_VERTICES] = {false};
//     BFS_Helper(g, startNode, visited);
//     for (int i = 0; i < g->vertexCount; i++) {
//         if (!visited[i]) {
//             BFS_Helper(g, i, visited);
//         }
//     }
//     printf("\n");
// }


// int main() {
//     Graph graph;
//     initializeGraph(&graph, 9); // 9 vertices labeled 0 to 8

//     addEdge(&graph, 1, 2);
//     addEdge(&graph, 1, 3);
//     addEdge(&graph, 2, 8);
//     addEdge(&graph, 3, 4);
//     addEdge(&graph, 3, 5);
//     addEdge(&graph, 4, 5);
//     addEdge(&graph, 6, 7);
//     addEdge(&graph, 6, 8);
//     addEdge(&graph, 7, 8);

//     printf("BFS starting from vertex 1:\n");
//     BFS(&graph, 1);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void queue_init(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        error("Queue overflow");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("Queue underflow");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

typedef struct {
    int n;  // Number of vertices
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void graph_init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "Graph overflow\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "Graph index error\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; // Remove this line for directed graph
}

void BFS_Helper(GraphType* g, int v, bool* visited) {
    int w;
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    printf("%d ", v);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d ", w);
                enqueue(&q, w);
            }
        }
    }
}

void BFS(GraphType* g, int startNode) {
    bool visited[MAX_VERTICES] = {FALSE};
    BFS_Helper(g, startNode, visited);
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            BFS_Helper(g, i, visited);
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    for (int i = 0; i < 9; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 8);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 8);

    printf("BFS starting from vertex 1:\n");
    BFS(g, 1);
    printf("\n");

    free(g);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define TRUE 1
// #define FALSE 0
// #define MAX_QUEUE_SIZE 50
// #define MAX_VERTICES 50

// typedef int element;
// typedef struct {
//     element queue[MAX_QUEUE_SIZE];
//     int front, rear;
// } QueueType;

// void error(const char* message) {
//     fprintf(stderr, "%s\n", message);
//     exit(1);
// }

// void queue_init(QueueType* q) {
//     q->front = q->rear = 0;
// }

// int is_empty(QueueType* q) {
//     return (q->front == q->rear);
// }

// int is_full(QueueType* q) {
//     return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
// }

// void enqueue(QueueType* q, element item) {
//     if (is_full(q)) {
//         error("Queue overflow");
//     }
//     q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
//     q->queue[q->rear] = item;
// }

// element dequeue(QueueType* q) {
//     if (is_empty(q)) {
//         error("Queue underflow");
//     }
//     q->front = (q->front + 1) % MAX_QUEUE_SIZE;
//     return q->queue[q->front];
// }

// typedef struct {
//     int n;  // Number of vertices
//     int adj_mat[MAX_VERTICES][MAX_VERTICES];
// } GraphType;

// void graph_init(GraphType* g) {
//     int r, c;
//     g->n = 0;
//     for (r = 0; r < MAX_VERTICES; r++) {
//         for (c = 0; c < MAX_VERTICES; c++) {
//             g->adj_mat[r][c] = 0;
//         }
//     }
// }

// void insert_vertex(GraphType* g, int v) {
//     if (v >= MAX_VERTICES) {
//         fprintf(stderr, "Graph overflow\n");
//         return;
//     }
//     g->n++;
// }


// void insert_edge(GraphType* g, int start, int end) {
//     if (start >= MAX_VERTICES || end >= MAX_VERTICES) {
//         fprintf(stderr, "Graph index error\n");
//         return;
//     }
//     g->adj_mat[start][end] = 1;
//     // g->adj_mat[end][start] = 1; // Remove this line for directed graph
// }

// void BFS_Helper(GraphType* g, int v, bool* visited) {
//     int w;
//     QueueType q;

//     queue_init(&q);
//     visited[v] = TRUE;
//     printf("%d ", v);
//     enqueue(&q, v);
//     while (!is_empty(&q)) {
//         v = dequeue(&q);
//         for (w = 1; w < g->n; w++) {
//             if (g->adj_mat[v][w] && !visited[w]) {
//                 visited[w] = TRUE;
//                 printf("%d ", w);
//                 enqueue(&q, w);
//             }
//         }
//     }
// }

// void BFS(GraphType* g, int startNode) {
//     bool visited[MAX_VERTICES] = {FALSE};
//     BFS_Helper(g, startNode, visited);
//     for (int i = 1; i < g->n; i++) {
//         if (!visited[i]) {
//             BFS_Helper(g, i, visited);
//         }
//     }
// }

// int main(void) {
//     int vertices[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 정점 번호를 0부터 시작하도록 조정
//     int edges[][2] = {
//         {1, 2}, {1, 3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}
//     }; // 간선
//     int numVertices = sizeof(vertices) / sizeof(vertices[0]);
//     int numEdges = sizeof(edges) / sizeof(edges[0]);
   
//     GraphType* g = (GraphType*)malloc(sizeof(GraphType));
//     graph_init(g);

//     for (int i = 0; i < numVertices+1; i++) {
//         insert_vertex(g, vertices[i]);
//     }

//     for (int i = 0; i < numEdges; i++) {
//         insert_edge(g, edges[i][0], edges[i][1]);
//     }

//     printf("BFS starting from vertex 1:\n");
//     BFS(g, 1);
//     printf("\n");

//     free(g);
//     return 0;
// }
