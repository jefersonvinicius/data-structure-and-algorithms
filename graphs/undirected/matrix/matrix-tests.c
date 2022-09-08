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

    { // should convert to string representation correctly (size less than 10)
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
        printf("%s\n", result);

        assert(strcmp(expected, result) == 0);
    }

    { // should convert to string representation correctly (size greater than 10)
        struct AdjacencyMatrixGraph* graph = create_adj_matrix_graph(12);
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
        
        char* expected = "                         1 1\n\
     0 1 2 3 4 5 6 7 8 9 0 1 \n\
00 [ 0 0 0 0 0 0 0 0 0 0 0 0 ]\n\
01 [ 0 0 1 1 1 0 0 0 0 0 0 0 ]\n\
02 [ 0 1 0 1 0 0 0 0 0 0 0 0 ]\n\
03 [ 0 1 1 0 1 1 0 0 0 0 0 0 ]\n\
04 [ 0 1 0 1 0 1 0 0 0 0 0 0 ]\n\
05 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
06 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
07 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
08 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
09 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
10 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
11 [ 0 0 0 1 1 0 0 0 0 0 0 0 ]\n\
";

        char* result = amgraph_to_string(graph);

        printf("%s\n", result);

        assert(strcmp(expected, result) == 0);
    }

    return 0;
}