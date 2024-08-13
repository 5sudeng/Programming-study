#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////
// DFS + Topological Sort + SCC (C Version) //
///////////////////////////////////////////////

// 1. Color 정의
typedef enum {
    WHITE,
    GRAY,
    BLACK
} Color;

// 2. Vertex 정의
typedef struct {
    Color color;
    int pi;
    int discover;       // timestamp for discover
    int finish;         // timestamp for finish
    int* adj;
    int adj_size;
} Vertex;

// 3. Graph 정의
typedef struct {
    Vertex* vertices;
    int numVertices; //vertices 배열의 크기
} Graph;

// 4. Stack 정의
typedef struct {
    int* array;
    int top;
    unsigned capacity;
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    return stack->array[stack->top--];
}

void initializeVertex(Vertex* vertex) {
    vertex->color = WHITE;
    vertex->pi = -1;
}

void DFS_VISIT(Graph* graph, int u, int* time, Stack* finishStack) {
    *time = *time + 1;
    graph->vertices[u].discover = *time;
    graph->vertices[u].color = GRAY;

    for (int i = 0; i < graph->vertices[u].adj_size; i++) {
        int v = graph->vertices[u].adj[i];
        if (graph->vertices[v].color == WHITE) {
            graph->vertices[v].pi = u;
            DFS_VISIT(graph, v, time, finishStack);
        }
    }

    *time = *time + 1;
    graph->vertices[u].finish = *time;
    graph->vertices[u].color = BLACK;
    push(finishStack, u);
}

void DFS(Graph* graph, Stack* finishStack) {
    int time = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        initializeVertex(&(graph->vertices[i]));
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            DFS_VISIT(graph, i, &time, finishStack);
        }
    }
}

void initializeGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    graph->vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));

    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i].adj = NULL;
        graph->vertices[i].adj_size = 0;
    }
}

int main() {
    // [#11] p.21 graph example
    int numVertex = 6;
    Graph graph;
    Stack finishStack;

    initializeGraph(&graph, numVertex);
    finishStack = *createStack(numVertex);

    graph.vertices[0].adj = (int[]){1, 3};
    graph.vertices[0].adj_size = 2;
    graph.vertices[1].adj = (int[]){4};
    graph.vertices[1].adj_size = 1;
    graph.vertices[2].adj = (int[]){4, 5};
    graph.vertices[2].adj_size = 2;
    graph.vertices[3].adj = (int[]){1};
    graph.vertices[3].adj_size = 1;
    graph.vertices[4].adj = (int[]){3};
    graph.vertices[4].adj_size = 1;
    graph.vertices[5].adj = (int[]){5};
    graph.vertices[5].adj_size = 1;

    DFS(&graph, &finishStack);

    for (int i = 0; i < numVertex; i++) {
        printf("Vertex %d: Discover=%d, Finish=%d\n", i, graph.vertices[i].discover, graph.vertices[i].finish);
    }

    // [#11] p.30 graph example
    // int numVertex = 9;
    // Graph graph;
    // Stack finishStack;

    // initializeGraph(&graph, numVertex);
    // finishStack = *createStack(numVertex);

    // graph.vertices[0].adj = (int[]){1, 7};
    // graph.vertices[0].adj_size = 2;
    // graph.vertices[1].adj = (int[]){2, 7};
    // graph.vertices[1].adj_size = 2;
    // graph.vertices[2].adj = (int[]){5};
    // graph.vertices[2].adj_size = 1;
    // graph.vertices[3].adj = (int[]){2, 4};
    // graph.vertices[3].adj_size = 2;
    // graph.vertices[4].adj = (int[]){5};
    // graph.vertices[4].adj_size = 1;
    // graph.vertices[5].adj_size = 0;
    // graph.vertices[6].adj = (int[]){7};
    // graph.vertices[6].adj_size = 1;
    // graph.vertices[7].adj_size = 0;
    // graph.vertices[8].adj_size = 0;

    // DFS(&graph, &finishStack);

    // for (int i = 0; i < numVertex; i++) {
    //     printf("Vertex %d: Discover=%d, Finish=%d\n", i, graph.vertices[i].discover, graph.vertices[i].finish);
    // }

    // printf("Topological Sort: ");
    // while (!isStackEmpty(&finishStack)) {
    //     printf("%d ", pop(&finishStack));
    // }
    // printf("\n");

    free(graph.vertices);
    free(finishStack.array);

    return 0;
}
