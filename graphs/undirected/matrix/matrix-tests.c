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
        amgraph_add_edge(graph, 1, 2);
        amgraph_add_edge(graph, 1, 3);

        assert(__matrix_get(graph, 1, 2) == 1);
        assert(__matrix_get(graph, 1, 3) == 1);
    }

    { // should convert to string representation correctly
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(6);
        amgraph_add_edge(graph, 1, 2);
        amgraph_add_edge(graph, 1, 3);
        amgraph_add_edge(graph, 1, 4);
        amgraph_add_edge(graph, 2, 1);
        amgraph_add_edge(graph, 2, 3);
        amgraph_add_edge(graph, 3, 1);
        amgraph_add_edge(graph, 3, 2);
        amgraph_add_edge(graph, 3, 4);
        amgraph_add_edge(graph, 3, 5);
        amgraph_add_edge(graph, 4, 1);
        amgraph_add_edge(graph, 4, 3);
        amgraph_add_edge(graph, 4, 5);
        amgraph_add_edge(graph, 5, 3);
        amgraph_add_edge(graph, 5, 4);
        
        char* expected = "    0 1 2 3 4 5\n\
0 [ 0 0 0 0 0 0 ]\n\
1 [ 0 0 1 1 1 0 ]\n\
2 [ 0 1 0 1 0 0 ]\n\
3 [ 0 1 1 0 1 1 ]\n\
4 [ 0 1 0 1 0 1 ]\n\
5 [ 0 0 0 1 1 0 ]";

        char* result = amgraph_to_string(graph);

        assert(strcmp(expected, result) == 0);
    }

    return 0;
}