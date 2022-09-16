#include "limits.h"
#include "node.h"
#include "stdlib.h"

#define MAX_GRAPH_SIZE INT_MAX

struct AdjacencyListGraph {
    struct ALGNode* list[MAX_GRAPH_SIZE];
};

struct AdjacencyListGraph* create_adjacency_list_graph() {
    struct AdjacencyListGraph* graph = (struct AdjacencyListGraph*) malloc(sizeof(struct AdjacencyListGraph*));
    // graph->list = malloc(sizeof(struct ALGNode*) * MAX_GRAPH_SIZE);
    // for (int i = 0; i < MAX_GRAPH_SIZE; i++) graph->list[i] = NULL;
    return graph;
}

void __alg_add_edge(struct AdjacencyListGraph* graph, int a, int b) {
    printf("ADDING INTO %p\n", graph->list[a]);
    if (graph->list[a] == NULL) {
        graph->list[a] = create_alg_node(b);
    } else {
        printf("HERE\n");
        struct ALGNode* last = get_last_node(graph->list[a]);
        printf("---> %p\n", last);
        last->next = create_alg_node(b);
        printf("HERE2\n");
    }
}

void alg_add_edge(struct AdjacencyListGraph* graph, int a, int b) {
    __alg_add_edge(graph, a, b);
    __alg_add_edge(graph, b, a);
}

struct ALGNode* alg_get_vertex_edges(struct AdjacencyListGraph* graph, int vertex) {
    return graph->list[vertex];
}