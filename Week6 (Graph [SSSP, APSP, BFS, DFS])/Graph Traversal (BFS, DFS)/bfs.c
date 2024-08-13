#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//////////////////
// BFS w/ queue //
//////////////////

// 1. Color 정의
typedef enum {
    WHITE,
    GRAY,
    BLACK
} Color;

// 2. Vertex 정의
typedef struct {
    Color color;
    int dist;
    int pi;
    int* adj;
    int adj_size;
} Vertex;

// 3. Graph 정의
typedef struct {
    Vertex* vertices;
    int numVertices;
} Graph;

// 큐 구현
typedef struct {
    int* array;
    int front;
    int rear;
    unsigned capacity;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == -1;
}

void enqueue(Queue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;

    queue->rear++;
    queue->array[queue->rear] = item;
}

int dequeue(Queue* queue) {
    int item = queue->array[queue->front];

    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;

    return item;
}

void initializeVertex(Vertex* vertex) {
    vertex->color = WHITE;
    vertex->dist = INT_MAX;
    vertex->pi = -1;
}

void BFS(Graph* graph, int s) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (i != s) {
            initializeVertex(&(graph->vertices[i]));
        }
    }

    graph->vertices[s].color = GRAY;
    graph->vertices[s].dist = 0;
    graph->vertices[s].pi = -1;

    Queue* Q = createQueue(graph->numVertices);
    enqueue(Q, s);

    while (!isEmpty(Q)) {
        int u = dequeue(Q);

        for (int i = 0; i < graph->vertices[u].adj_size; i++) {
            int v = graph->vertices[u].adj[i];
            if (graph->vertices[v].color == WHITE) {
                graph->vertices[v].color = GRAY;
                graph->vertices[v].dist = graph->vertices[u].dist + 1;
                graph->vertices[v].pi = u;
                enqueue(Q, v);
            }
        }

        graph->vertices[u].color = BLACK;
    }

    free(Q->array);
    free(Q);
}

int main() {
    // [#11] p.9 graph example
    int numVertex = 9;
    Graph graph;
    graph.numVertices = numVertex;
    graph.vertices = (Vertex*)malloc(numVertex * sizeof(Vertex));

    for (int i = 0; i < numVertex; i++) {
        graph.vertices[i].adj_size = 0;
    }

    graph.vertices[0].adj = (int[]){1, 2, 5};
    graph.vertices[0].adj_size = 3;
    graph.vertices[1].adj = (int[]){0, 3, 4};
    graph.vertices[1].adj_size = 3;
    graph.vertices[2].adj = (int[]){0, 3};
    graph.vertices[2].adj_size = 2;
    graph.vertices[3].adj = (int[]){1, 2, 7};
    graph.vertices[3].adj_size = 3;
    graph.vertices[4].adj = (int[]){1, 5, 7};
    graph.vertices[4].adj_size = 3;
    graph.vertices[5].adj = (int[]){0, 4, 6, 8};
    graph.vertices[5].adj_size = 4;
    graph.vertices[6].adj = (int[]){5, 7, 8};
    graph.vertices[6].adj_size = 3;
    graph.vertices[7].adj = (int[]){3, 4, 6};
    graph.vertices[7].adj_size = 3;
    graph.vertices[8].adj = (int[]){5, 6};
    graph.vertices[8].adj_size = 2;

    BFS(&graph, 1);

    for (int i = 0; i < numVertex; ++i) {
        printf("Vertex %d: Distance=%d, Parent=%d\n", i, graph.vertices[i].dist, graph.vertices[i].pi);
    }

    free(graph.vertices);

    return 0;
}
