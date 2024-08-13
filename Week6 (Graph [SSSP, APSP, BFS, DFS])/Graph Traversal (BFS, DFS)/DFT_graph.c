#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int vertex;
  struct Node* next;
} Node;


typedef struct Graph {
  int totalVertices;
  int* visited;
  Node** adjLists;
} Graph;

/*
adjlist 예시
0: 1 -> 2
1: 0 -> 2 -> 3
2: 0 -> 1 -> 4
3: 1
4: 2
*/

Node* createNode(int v) {
  Node* newNode = malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}



void DFS(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (!graph->visited[i]) {
            DFS(graph, i);
            // printf("\n"); // Uncomment if you want to distinguish between different connected components
        }
    }
}


Graph* createGraph(int v) {
  Graph* graph = malloc(sizeof(Graph));
  graph->totalVertices = v;
  graph->adjLists = malloc(v * sizeof(Node*));
  graph->visited = malloc(v * sizeof(int));

  for (int i = 0; i < v; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}



void addEdge(Graph* graph, int src, int dest) {
    // dest를 src의 인접 리스트에 정렬된 상태로 추가
    Node* newNode = createNode(dest);
    if (graph->adjLists[src] == NULL || graph->adjLists[src]->vertex > dest) {
        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;
    } else {
        Node* current = graph->adjLists[src];
        while (current->next != NULL && current->next->vertex < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // src를 dest의 인접 리스트에 정렬된 상태로 추가 (무방향 그래프의 경우)
    newNode = createNode(src);
    if (graph->adjLists[dest] == NULL || graph->adjLists[dest]->vertex > src) {
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    } else {
        Node* current = graph->adjLists[dest];
        while (current->next != NULL && current->next->vertex < src) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}



void displayGraph(Graph* graph) {
  int v;
  for (v = 1; v < graph->totalVertices; v++) {
    Node* temp = graph->adjLists[v];
    printf("%d ", v);
    while (temp) {
      printf("%d ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
  printf("\n");
}



int main() {
    int vertices = 9;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 8);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);
    addEdge(graph, 6, 7);
    addEdge(graph, 6, 8);
    addEdge(graph, 7, 8);

    // printf("\nThe Adjacency List of the Graph is:");
    // displayGraph(graph);
    printf("DFS traversal of the graph: \n");
    DFS(graph, 1);


    return 0;
}


// 만약 add, vertex 따로 준다면
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct Node {
//   int vertex;
//   struct Node* next;
// } Node;

// typedef struct Graph {
//   int totalVertices;
//   int* visited;
//   Node** adjLists;
// } Graph;

// Node* createNode(int v) {
//   Node* newNode = malloc(sizeof(Node));
//   newNode->vertex = v;
//   newNode->next = NULL;
//   return newNode;
// }

// void DFS(Graph* graph, int startVertex) {
//     Node* adjList = graph->adjLists[startVertex];
//     Node* temp = adjList;

//     graph->visited[startVertex] = 1;
//     printf("%d ", startVertex);

//     while (temp != NULL) {
//         int connectedVertex = temp->vertex;
//         if (graph->visited[connectedVertex] == 0) {
//             DFS(graph, connectedVertex);
//         }
//         temp = temp->next;
//     }
//     for (int i = 1; i < graph->totalVertices; ++i) {
//         if (!graph->visited[i]) {
//             DFS(graph, i);
//             // printf("\n"); // Uncomment if you want to distinguish between different connected components
//         }
//     }
// }

// Graph* createGraph(int v) {
//   Graph* graph = malloc(sizeof(Graph));
//   graph->totalVertices = v + 1; // Adjust for 1-based index
//   graph->adjLists = malloc((v + 1) * sizeof(Node*));
//   graph->visited = malloc((v + 1) * sizeof(int));

//   for (int i = 0; i <= v; i++) {
//     graph->adjLists[i] = NULL;
//     graph->visited[i] = 0;
//   }
//   return graph;
// }

// void addEdge(Graph* graph, int src, int dest) {
//     Node* newNode = createNode(dest);
//     if (graph->adjLists[src] == NULL || graph->adjLists[src]->vertex > dest) {
//         newNode->next = graph->adjLists[src];
//         graph->adjLists[src] = newNode;
//     } else {
//         Node* current = graph->adjLists[src];
//         while (current->next != NULL && current->next->vertex < dest) {
//             current = current->next;
//         }
//         newNode->next = current->next;
//         current->next = newNode;
//     }

//     newNode = createNode(src);          //undirected graph일 경우 추가
//     if (graph->adjLists[dest] == NULL || graph->adjLists[dest]->vertex > src) {
//         newNode->next = graph->adjLists[dest];
//         graph->adjLists[dest] = newNode;
//     } else {
//         Node* current = graph->adjLists[dest];
//         while (current->next != NULL && current->next->vertex < src) {
//             current = current->next;
//         }
//         newNode->next = current->next;
//         current->next = newNode;
//     }
// }

// void displayGraph(Graph* graph) {
//   int v;
//   for (v = 1; v < graph->totalVertices; v++) {
//     Node* temp = graph->adjLists[v];
//     printf("%d ", v);
//     while (temp) {
//       printf("%d ", temp->vertex);
//       temp = temp->next;
//     }
//     printf("\n");
//   }
//   printf("\n");
// }

// int main() {
//     int vertices[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 정점
//     int edges[][2] = {
//         {1, 2}, {1, 3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}
//     }; // 간선
//     int numVertices = sizeof(vertices) / sizeof(vertices[0]);
//     int numEdges = sizeof(edges) / sizeof(edges[0]);

//     Graph* graph = createGraph(numVertices);

//     for (int i = 0; i < numEdges; i++) {
//         addEdge(graph, edges[i][0], edges[i][1]);
//     }

//     // printf("\nThe Adjacency List of the Graph is:");
//     // displayGraph(graph);
//     printf("DFS traversal of the graph: \n");
//     DFS(graph, 1);

//     return 0;
// }
