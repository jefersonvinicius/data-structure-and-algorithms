#include "limits.h"
#include "node.h"
#include "stdlib.h"
#include <string.h>
#include "../../../queue/linkedlist/queue.h"
#include "../../../_utils_/debug.h"

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
    __alg_add_edge(graph, b, a);
}

struct ALGNode* alg_get_vertex_edges(struct AdjacencyListGraph* graph, int vertex) {
    return graph->list[vertex];
}

void print_connected_vertex(struct AdjacencyListGraph* graph, int vertex) {
    struct ALGNode* node = graph->list[vertex];
    printf("[%d]", vertex);
    while (node != NULL) {
        printf(" -> %d", node->vertex);
        node = node->next;
    }
    printf("\n");
}

int* alg_bfs(struct AdjacencyListGraph* graph, int from) {
    int* result = malloc(sizeof(int) * MAX_GRAPH_SIZE);
    int result_index = 0;
    int vertexes_visited[MAX_GRAPH_SIZE], vertexes_already_pending[MAX_GRAPH_SIZE];
    memset(vertexes_visited, 0, MAX_GRAPH_SIZE); memset(vertexes_already_pending, 0, MAX_GRAPH_SIZE);
    struct LklQueue* pending = create_lkl_queue();    

    lklq_enqueue(pending, from);
    while (!lklq_is_empty(pending)) {
        int current = pending->front->data;
        debug_log("Visiting: %d\n", current);

        lklq_dequeue(pending);
        vertexes_visited[current] = 1;

        struct ALGNode* node = graph->list[current];
        while (node != NULL) {
            if (vertexes_visited[node->vertex] != 1 && vertexes_already_pending[node->vertex] != 1) {
                debug_log("Adding %d to pending list\n", node->vertex);
                lklq_enqueue(pending, node->vertex);
                vertexes_already_pending[node->vertex] = 1;
            }
            node = node->next;
        }
        

        result[result_index] = current;
        result_index++;
    }
    
    free(pending);
    return result;
}