#include "limits.h"
#include "node.h"
#include "stdlib.h"

#define MAX_GRAPH_SIZE 1000

struct AdjacencyListGraph {
    struct ALGNode** list;
};

struct AdjacencyListGraph* create_adjacency_list_graph() {
    struct AdjacencyListGraph* graph = (struct AdjacencyListGraph*) malloc(sizeof(struct AdjacencyListGraph*));
    graph->list = malloc(sizeof(struct ALGNode*) * MAX_GRAPH_SIZE);
    for (int i = 0; i < MAX_GRAPH_SIZE; i++) graph->list[i] = NULL;
    return graph;
}

void __alg_add_edge(struct AdjacencyListGraph* graph, int a, int b) {
    if (graph->list[a] == NULL) {
        graph->list[a] = create_alg_node(b);
    } else {
        struct ALGNode* last = alg_get_last_node(graph->list[a]);
        last->next = create_alg_node(b);
    }
}

void alg_add_edge(struct AdjacencyListGraph* graph, int a, int b) {
    __alg_add_edge(graph, a, b);
}

struct ALGNode* alg_get_vertex_edges(struct AdjacencyListGraph* graph, int vertex) {
    return graph->list[vertex];
}