#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMBERS 2000

typedef struct {
    int id;
    int rank;
    int parent;
} subset;

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct {
    Edge *edges;
    int num_edges;
} Graph;

int find(subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void union_sets(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int cmpfunc(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

Graph *read_graph(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file: %s\n", filename);
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_edges = 0;
    graph->edges = (Edge *)malloc(MAX_MEMBERS * sizeof(Edge));

    int src, dest;
    while (fscanf(fp, "%d %d", &src, &dest) != EOF) {
        graph->edges[graph->num_edges].src = src;
        graph->edges[graph->num_edges].dest = dest;
        graph->num_edges++;
    }

    fclose(fp);
    return graph;
}

void print_mst(Edge *mst, int num_edges) {
    int total_weight = 0;
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < num_edges; i++) {
        printf("( %d , %d )\n", mst[i].src, mst[i].dest);
        total_weight += mst[i].weight;
    }
    //printf("Total weight: %d\n", total_weight);
}

void kruskal_mst(Graph *graph) {
    int num_vertices = MAX_MEMBERS;
    subset *subsets = (subset *)malloc(num_vertices * sizeof(subset));

    for (int i = 0; i < num_vertices; i++) {
        subsets[i].id = i;
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    Edge *mst = (Edge *)malloc((num_vertices - 1) * sizeof(Edge));
    int mst_index = 0;

    qsort(graph->edges, graph->num_edges, sizeof(Edge), cmpfunc);

    for (int i = 0; i < graph->num_edges; i++) {
        int x = find(subsets, graph->edges[i].src);
        int y = find(subsets, graph->edges[i].dest);
        if (x != y) {
            mst[mst_index] = graph->edges[i];
            mst_index++;
            union_sets(subsets, x, y);
        }
        if (mst_index == num_vertices - 1) {
            break;
        }
    }

    print_mst(mst, mst_index);

    free(mst);
    free(subsets);
}

int main() {
Graph *membership_graph = read_graph("/Users/anishbanerjee/Desktop/Algorithm Laboratory/membership.txt");
Graph *email_graph = read_graph("/Users/anishbanerjee/Desktop/Algorithm Laboratory/connectivity.txt");
    // Create a new graph by merging membership and email graphs
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_edges = 0;
    graph->edges = (Edge *)malloc(MAX_MEMBERS * sizeof(Edge));

    for (int i = 0; i < membership_graph->num_edges; i++) {
        int src = membership_graph->edges[i].src;
        int dest = membership_graph->edges[i].dest;
        int weight = 1;

        for (int j = 0; j < email_graph->num_edges; j++) {
            if ((email_graph->edges[j].src == src && email_graph->edges[j].dest == dest) ||
                (email_graph->edges[j].src == dest && email_graph->edges[j].dest == src)) {
                weight = 0;
                break;
            }
        }

        graph->edges[graph->num_edges].src = src;
        graph->edges[graph->num_edges].dest = dest;
        graph->edges[graph->num_edges].weight = weight;
        graph->num_edges++;
    }

    kruskal_mst(graph);

    free(membership_graph->edges);
    free(membership_graph);
    free(email_graph->edges);
    free(email_graph);
    free(graph->edges);
    free(graph);

    return 0;
}
