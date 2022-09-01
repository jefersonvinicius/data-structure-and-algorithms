#include "stdlib.h"
#include "string.h"

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

void amgraph_add_edge(struct AdjacencyMatrixGraph* graph, int node1, int node2) {
    __matrix_set(graph, node1, node2, 1);
}

void amgraph_print(struct AdjacencyMatrixGraph* graph) {
    for (int r = 0; r < graph->size; r++) {
        for (int c = 0; c < graph->size; c++) {
            printf("%d ", __matrix_get(graph, r, c));
        }
        printf("\n");
    }
}

char* amgraph_to_string(struct AdjacencyMatrixGraph* graph) {
    char* result = malloc(graph->size * graph->size * graph->size * sizeof(char));
    char str[1000]; 
    
    strcat(result, "    ");
    for (int i = 0; i < graph->size; i++) {
        if (i == graph->size - 1) sprintf(str, "%d", i);
        else sprintf(str, "%d ", i);

        strcat(result, str);
    }
    strcat(result, "\n");

    for (int r = 0; r < graph->size; r++) {
        sprintf(str, "%d [ ", r);
        strcat(result, str);
        for (int c = 0; c < graph->size; c++) {
            sprintf(str, "%d ", __matrix_get(graph, r, c));
            strcat(result, str);

            if (c == graph->size - 1) strcat(result, "]");
        }
        if (r < graph->size - 1) strcat(result, "\n");
    }

    return result;
}



