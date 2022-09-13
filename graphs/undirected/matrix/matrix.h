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

void amgraph_print(struct AdjacencyMatrixGraph* graph) {
    for (int r = 0; r < graph->size; r++) {
        for (int c = 0; c < graph->size; c++) {
            printf("%d ", __matrix_get(graph, r, c));
        }
        printf("\n");
    }
}

char* amgraph_to_string(struct AdjacencyMatrixGraph* graph) {
    char str[1000]; 
    char* result = malloc(graph->size * graph->size * graph->size * sizeof(char));
    int number_of_zeros = strlen(to_string(graph->size));


    int header_rows_amount = number_of_zeros;
    char header[header_rows_amount][graph->size];
    for (int r = header_rows_amount; r >= 1; r--) {
        for (int i = 0; i < number_of_zeros + 3; i++) strcat(result, " ");
        for (int c = 0; c < graph->size; c++) {

            char* column_number_as_str = to_string(c);
            int length_of_number = strlen(column_number_as_str);
            if (r > length_of_number) {
                strcat(result, " ");
            } else {
                sprintf(str, "%c", column_number_as_str[length_of_number-r]);
                strcat(result, str);
            }
            if (c < graph->size - 1) strcat(result, " ");
        }
        if (r > 1) strcat(result, "\n");
    }

    strcat(result, "\n");


    for (int r = 0; r < graph->size; r++) {
        sprintf(str, "%0*d [ ", number_of_zeros, r);
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



