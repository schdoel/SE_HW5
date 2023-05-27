// Bellman-Ford Algorithm
// Author: Neeraj Mishra

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int source, destination, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

void FinalSolution(int* dist, int n) {
    printf("\nVertex\tDistance from Source Vertex\n");
    for (int i = 0; i < n; ++i) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void BellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int* StoreDistance = (int*)malloc(V * sizeof(int));

    // Initialize distances to infinity except for the source vertex
    for (int i = 0; i < V; i++)
        StoreDistance[i] = INT_MAX;

    StoreDistance[source] = 0;

    // Perform V-1 relaxations
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;

            if (StoreDistance[u] != INT_MAX && StoreDistance[u] + weight < StoreDistance[v])
                StoreDistance[v] = StoreDistance[u] + weight;
        }
    }

    // Check for negative edge cycle
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;

        if (StoreDistance[u] != INT_MAX && StoreDistance[u] + weight < StoreDistance[v]) {
            printf("This graph contains a negative edge cycle\n");
            free(StoreDistance);
            return;
        }
    }

    FinalSolution(StoreDistance, V);
    free(StoreDistance);
}

int main() {
    int V, E, S;  // V = number of vertices, E = number of edges, S is source vertex

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    printf("Enter your source vertex number: ");
    scanf("%d", &S);

    struct Graph* graph = createGraph(V, E);

    for (int i = 0; i < E; i++) {
        printf("\nEnter edge %d properties (source, destination, weight respectively): ", i + 1);
        scanf("%d%d%d", &graph->edge[i].source, &graph->edge[i].destination, &graph->edge[i].weight);
    }

    BellmanFord(graph, S);

    free(graph->edge);
    free(graph);

    return 0;
}
