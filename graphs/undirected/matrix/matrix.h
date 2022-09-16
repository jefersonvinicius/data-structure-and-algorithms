#include "stdlib.h"
#include "string.h"
#include "../../../_utils_/conversions.h"

#define MAX_GRAPH_MATRIX_SIZE 100

struct AdjacencyMatrixGraph {
    int size;
    int *matrix;
};

struct AdjacencyMatrixGraph* create_adj_matrix_graph(int size) {
    struct AdjacencyMatrixGraph* graph = malloc(sizeof(struct AdjacencyMatrixGraph*));
    graph->size = size;
    graph->matrix = malloc(sizeof(int) * size * size);
    for (int i = 0; i < size * size; i++) {
        graph->matrix[i] = 0;
    }

    return graph;
}

int __matrix_get(struct AdjacencyMatrixGraph* graph, int row, int col) {
    return graph->matrix[row * graph->size + col];
}

void __matrix_set(struct AdjacencyMatrixGraph* graph, int row, int col, int value) {
    graph->matrix[row * graph->size + col] = value;
}

void amgraph_add_edge(struct AdjacencyMatrixGraph* graph, int node1, int node2, int weight) {
    __matrix_set(graph, node1, node2, weight);
}




