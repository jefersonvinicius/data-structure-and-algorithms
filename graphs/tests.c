#include "assert.h"
#include "stdio.h"
#include "graph.h"
#include "_utils_/asserts.h"

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
        graph_add_edge(graph, 0, 2, 10);
        assert(graph_get_vertex_edges(graph, 0)->vertex == 2);
        assert(graph_get_vertex_edges(graph, 0)->vertex == 2);
        assert(graph_get_vertex_edges(graph, 0)->parent_vertex == 0);
        assert(graph_get_vertex_edges(graph, 0)->next == NULL);
        assert(graph_get_vertex_edges(graph, 2)->vertex == 0);
        assert(graph_get_vertex_edges(graph, 2)->weight == 10);
        assert(graph_get_vertex_edges(graph, 2)->parent_vertex == 2);
        assert(graph_get_vertex_edges(graph, 2)->next == NULL);
        graph_add_edge(graph, 0, 3, 10);
        assert(graph_get_vertex_edges(graph, 3)->parent_vertex == 3);
        assert(graph_get_vertex_edges(graph, 0)->next->parent_vertex == 0);
    }

    { // should add edge between two points (no bidirectional)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(0);
        graph_add_edge(graph, 0, 2, 10);

        assert(graph_get_vertex_edges(graph, 0)->vertex == 2);
        assert(graph_get_vertex_edges(graph, 0)->weight == 10);
        assert(graph_get_vertex_edges(graph, 2) == NULL);
    }

    { // should add edge between two points (more than one at same vertex)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 0, 2, 10);
        graph_add_edge(graph, 1, 2, 11);
        graph_add_edge(graph, 3, 0, 12);

        assert(graph_get_vertex_edges(graph, 0)->vertex == 2);
        assert(graph_get_vertex_edges(graph, 0)->next->vertex == 3);
        assert(graph_get_vertex_edges(graph, 2)->vertex == 0);
        assert(graph_get_vertex_edges(graph, 2)->next->vertex == 1);
        assert(graph_get_vertex_edges(graph, 3)->vertex == 0);
    }

    { // should make bfs result 
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 0, 1, 10);
        graph_add_edge(graph, 0, 2, 11);
        graph_add_edge(graph, 0, 3, 12);
        graph_add_edge(graph, 1, 2, 13);
        graph_add_edge(graph, 2, 3, 14);
        graph_add_edge(graph, 2, 4, 15);
        graph_add_edge(graph, 3, 4, 16);
        graph_add_edge(graph, 4, 5, 17);
        graph_add_edge(graph, 4, 6, 18);

        int* result1 = graph_bfs(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = graph_bfs(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    { // should make dfs result 
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 0, 1, 10);
        graph_add_edge(graph, 0, 2, 11);
        graph_add_edge(graph, 0, 3, 12);
        graph_add_edge(graph, 1, 2, 13);
        graph_add_edge(graph, 2, 3, 14);
        graph_add_edge(graph, 2, 4, 15);
        graph_add_edge(graph, 3, 4, 16);
        graph_add_edge(graph, 4, 5, 17);
        graph_add_edge(graph, 4, 6, 18);

        int* result1 = graph_dfs(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = graph_dfs(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    { // should make dfs result recursive
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 0, 1, 10);
        graph_add_edge(graph, 0, 2, 11);
        graph_add_edge(graph, 0, 3, 12);
        graph_add_edge(graph, 1, 2, 13);
        graph_add_edge(graph, 2, 3, 14);
        graph_add_edge(graph, 2, 4, 15);
        graph_add_edge(graph, 3, 4, 16);
        graph_add_edge(graph, 4, 5, 17);
        graph_add_edge(graph, 4, 6, 18);

        int* result1 = graph_dfs_recursive(graph, 0);
        int expected1[] = {0,1,2,3,4,5,6};
        assert_array(result1, expected1, 7);

        int* result2 = graph_dfs_recursive(graph, 1);
        int expected2[] = {1,0,2,3,4,5,6};
        assert_array(result2, expected2, 7);
    }

    { // min spanning tree
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 1, 2, 25);
        graph_add_edge(graph, 2, 3, 9);
        graph_add_edge(graph, 3, 4, 10);
        graph_add_edge(graph, 4, 5, 12);
        graph_add_edge(graph, 5, 6, 18);
        graph_add_edge(graph, 6, 1, 5);
        graph_add_edge(graph, 5, 7, 16);
        graph_add_edge(graph, 4, 7, 11);
        graph_add_edge(graph, 2, 7, 6);
        struct SpanTreeResult result = graph_span_tree(graph);
        assert(result.total == 60);
    }

    { // min spanning tree (without cycle)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 1, 2, 25);
        graph_add_edge(graph, 2, 3, 20);
        graph_add_edge(graph, 3, 4, 17);
        struct SpanTreeResult result = graph_span_tree(graph);
        assert(result.total == 62);
    }

    { // min spanning tree (small graph with cycle)
        struct AdjacencyListGraph* graph = create_adjacency_list_graph(1);
        graph_add_edge(graph, 1, 2, 2);
        graph_add_edge(graph, 2, 3, 3);
        graph_add_edge(graph, 3, 1, 6);
        struct SpanTreeResult result = graph_span_tree(graph);
        assert(result.total == 5);
    }

    return 0;
}