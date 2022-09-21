#include "assert.h"
#include "stdio.h"
#include "matrix.h"

int main() {

    { // should create graph correctly
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(5);
        for (int i = 0; i < graph->size * graph->size; i++) {
            assert(graph->matrix[i] == 0);
        }
    }

    { // should add edge correctly
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(5);
        amgraph_add_edge(graph, 1, 2, 1);
        amgraph_add_edge(graph, 1, 3, 1);

        assert(__matrix_get(graph, 1, 2) == 1);
        assert(__matrix_get(graph, 1, 3) == 1);

        assert(__matrix_get(graph, 2, 1) == 0);
        assert(__matrix_get(graph, 3, 1) == 0);
    }

    { // should add edge correctly with weight different of 1
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(5);
        amgraph_add_edge(graph, 1, 2, 10);
        amgraph_add_edge(graph, 1, 3, 8);

        assert(__matrix_get(graph, 1, 2) == 10);
        assert(__matrix_get(graph, 1, 3) == 8);
    }

    return 0;
}