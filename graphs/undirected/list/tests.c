#include "assert.h"
#include "stdio.h"
#include "graph.h"
#include "../../../_utils_/asserts.h"

int main() {

    { // should create AdjacencyListGraph correctly
        struct AdjacencyListGraph* graph = create_adjacency_list_graph();
        assert(graph != NULL);
        assert(graph->list != NULL);
        for (int i = 0; i < MAX_GRAPH_SIZE; i++) 
            assert(graph->list[i] == NULL);
    }

    { // should add edge between two points (root)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph();
        alg_add_edge(graph, 0, 2);

        assert(alg_get_vertex_edges(graph, 0)->vertex == 2);
        assert(alg_get_vertex_edges(graph, 2)->vertex == 0);
    }

    { // should add edge between two points (more than one at same vertex)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph();
        alg_add_edge(graph, 0, 2);
        alg_add_edge(graph, 1, 2);
        alg_add_edge(graph, 3, 0);

        assert(alg_get_vertex_edges(graph, 0)->vertex == 2);
        assert(alg_get_vertex_edges(graph, 0)->next->vertex == 3);
        assert(alg_get_vertex_edges(graph, 2)->vertex == 0);
        assert(alg_get_vertex_edges(graph, 2)->next->vertex == 1);
        assert(alg_get_vertex_edges(graph, 3)->vertex == 0);
    }

    { // should make bfs result 
        struct AdjacencyListGraph* graph = create_adjacency_list_graph();
        alg_add_edge(graph, 0, 1);
        alg_add_edge(graph, 0, 2);
        alg_add_edge(graph, 0, 3);
        alg_add_edge(graph, 1, 2);
        alg_add_edge(graph, 2, 3);
        alg_add_edge(graph, 2, 4);
        alg_add_edge(graph, 3, 4);
        alg_add_edge(graph, 4, 5);
        alg_add_edge(graph, 4, 6);

        int* result1 = alg_bfs(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = alg_bfs(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    return 0;
}