#include "assert.h"
#include "stdio.h"
#include "graph.h"
#include "../../_utils_/asserts.h"

int main() {

    { // should create AdjacencyListGraph correctly
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        assert(graph != NULL);
        assert(graph->list != NULL);
        for (int i = 0; i < MAX_GRAPH_SIZE; i++) 
            assert(graph->list[i] == NULL);
    }

    { // should add edge between two points (bidirectional)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        algraph_add_edge(graph, 0, 2, 10);

        assert(alg_get_vertex_edges(graph, 0)->vertex == 2);
        assert(alg_get_vertex_edges(graph, 0)->weight == 10);
        assert(alg_get_vertex_edges(graph, 2)->vertex == 0);
        assert(alg_get_vertex_edges(graph, 2)->weight == 10);
    }

    { // should add edge between two points (no bidirectional)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(0);
        algraph_add_edge(graph, 0, 2, 10);

        assert(alg_get_vertex_edges(graph, 0)->vertex == 2);
        assert(alg_get_vertex_edges(graph, 0)->weight == 10);
        assert(alg_get_vertex_edges(graph, 2) == NULL);
    }

    { // should add edge between two points (more than one at same vertex)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        algraph_add_edge(graph, 0, 2, 10);
        algraph_add_edge(graph, 1, 2, 11);
        algraph_add_edge(graph, 3, 0, 12);

        assert(alg_get_vertex_edges(graph, 0)->vertex == 2);
        assert(alg_get_vertex_edges(graph, 0)->next->vertex == 3);
        assert(alg_get_vertex_edges(graph, 2)->vertex == 0);
        assert(alg_get_vertex_edges(graph, 2)->next->vertex == 1);
        assert(alg_get_vertex_edges(graph, 3)->vertex == 0);
    }

    { // should make bfs result 
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        algraph_add_edge(graph, 0, 1, 10);
        algraph_add_edge(graph, 0, 2, 11);
        algraph_add_edge(graph, 0, 3, 12);
        algraph_add_edge(graph, 1, 2, 13);
        algraph_add_edge(graph, 2, 3, 14);
        algraph_add_edge(graph, 2, 4, 15);
        algraph_add_edge(graph, 3, 4, 16);
        algraph_add_edge(graph, 4, 5, 17);
        algraph_add_edge(graph, 4, 6, 18);

        int* result1 = algraph_bfs(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = algraph_bfs(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    { // should make dfs result 
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        algraph_add_edge(graph, 0, 1, 10);
        algraph_add_edge(graph, 0, 2, 11);
        algraph_add_edge(graph, 0, 3, 12);
        algraph_add_edge(graph, 1, 2, 13);
        algraph_add_edge(graph, 2, 3, 14);
        algraph_add_edge(graph, 2, 4, 15);
        algraph_add_edge(graph, 3, 4, 16);
        algraph_add_edge(graph, 4, 5, 17);
        algraph_add_edge(graph, 4, 6, 18);

        int* result1 = algraph_dfs(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = algraph_dfs(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    { // should make dfs result recursive
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        algraph_add_edge(graph, 0, 1, 10);
        algraph_add_edge(graph, 0, 2, 11);
        algraph_add_edge(graph, 0, 3, 12);
        algraph_add_edge(graph, 1, 2, 13);
        algraph_add_edge(graph, 2, 3, 14);
        algraph_add_edge(graph, 2, 4, 15);
        algraph_add_edge(graph, 3, 4, 16);
        algraph_add_edge(graph, 4, 5, 17);
        algraph_add_edge(graph, 4, 6, 18);

        int* result1 = algraph_dfs_recursive(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = algraph_dfs_recursive(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    { // min spanning tree
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        algraph_add_edge(graph, 1, 2, 25);
        algraph_add_edge(graph, 2, 3, 9);
        algraph_add_edge(graph, 3, 4, 10);
        algraph_add_edge(graph, 4, 5, 12);
        algraph_add_edge(graph, 5, 6, 18);
        algraph_add_edge(graph, 6, 5, 18);
        algraph_add_edge(graph, 5, 7, 16);
        algraph_add_edge(graph, 4, 7, 11);
        algraph_add_edge(graph, 2, 7, 6);
    }

    return 0;
}