#include "assert.h"
#include "stdio.h"
#include "matrix.h"
#include "../../_utils_/asserts.h"

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

        assert(__matrix_get(graph, 2, 1) == 1);
        assert(__matrix_get(graph, 3, 1) == 1);
    }

    { // should add edge correctly with weight different of 1
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(5);
        amgraph_add_edge(graph, 1, 2, 10);
        amgraph_add_edge(graph, 1, 3, 8);

        assert(__matrix_get(graph, 1, 2) == 10);
        assert(__matrix_get(graph, 1, 3) == 8);
    }

    { // should make bfs result 
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(7);
        amgraph_add_edge(graph, 0, 1, 1);
        amgraph_add_edge(graph, 0, 2, 1);
        amgraph_add_edge(graph, 0, 3, 1);
        amgraph_add_edge(graph, 1, 2, 1);
        amgraph_add_edge(graph, 2, 3, 1);
        amgraph_add_edge(graph, 2, 4, 1);
        amgraph_add_edge(graph, 3, 4, 1);
        amgraph_add_edge(graph, 4, 5, 1);
        amgraph_add_edge(graph, 4, 6, 1);

        int* result1 = amgraph_bfs(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = amgraph_bfs(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    return 0;
}