#include "limits.h"
#include "node.h"
#include "stdlib.h"
#include <string.h>
#include "queue/linkedlist/queue.h"
#include "stack/linkedlist/stack.h"
#include "sets/disjoint/disjoint.h"
#include "heap/heap.h"
#include "_utils_/debug.h"

#define MAX_GRAPH_SIZE 1000

struct AdjacencyListGraph {
    struct ALGNode** list;
    int is_bidirectional;
    size_t size;
};

struct AdjacencyListGraph* create_adjacency_list_graph(int is_bidirectional) {
    struct AdjacencyListGraph* graph = (struct AdjacencyListGraph*) malloc(sizeof(struct AdjacencyListGraph));
    graph->is_bidirectional = is_bidirectional;
    graph->list = (struct ALGNode**) malloc(sizeof(struct ALGNode*) * MAX_GRAPH_SIZE);
    for (int i = 0; i < MAX_GRAPH_SIZE; i++) graph->list[i] = NULL;
    return graph;
}

void __add_edge(struct AdjacencyListGraph* graph, int a, int b, int weight) {
    if (graph->list[a] == NULL) {
        graph->list[a] = create_alg_node(b, weight);
        graph->list[a]->parent_vertex = a;
    } else {
        struct ALGNode* last = alg_get_last_node(graph->list[a]);
        last->next = create_alg_node(b, weight);
        last->next->parent_vertex = a;
    }
}

void graph_add_edge(struct AdjacencyListGraph* graph, int a, int b, int weight) {
    __add_edge(graph, a, b, weight);
    if (graph->is_bidirectional) {
        __add_edge(graph, b, a, weight);
    }
}

struct ALGNode* graph_get_vertex_edges(struct AdjacencyListGraph* graph, int vertex) {
    return graph->list[vertex];
}

void graph_print_connected_vertex(struct AdjacencyListGraph* graph, int vertex) {
    struct ALGNode* node = graph->list[vertex];
    printf("[%d]", vertex);
    while (node != NULL) {
        printf(" -> [%d](w: %d, p: %d)", node->vertex, node->weight, node->parent_vertex);
        node = node->next;
    }
    printf("\n");
}

void graph_print_all_connections(struct AdjacencyListGraph* graph) {
    for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
        if (graph_get_vertex_edges(graph, i) != NULL) {
            graph_print_connected_vertex(graph, i);
        }
    }
}

int* graph_bfs(struct AdjacencyListGraph* graph, int from) {
    int* result = (int*) malloc(sizeof(int) * MAX_GRAPH_SIZE);
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


int* graph_dfs(struct AdjacencyListGraph* graph, int from) {
    int* result = (int*) malloc(sizeof(int) * MAX_GRAPH_SIZE);
    int result_index = 0;
    int vertexes_visited[MAX_GRAPH_SIZE];
    memset(vertexes_visited, 0, MAX_GRAPH_SIZE);
    struct LklStack* stack = create_lklstack();
    lkls_push(stack, from);
    while (!lkls_is_empty(stack)) {
        int current = lkls_top(stack);
        if (vertexes_visited[current]) {
            lkls_pop(stack);
        } else {
            debug_log("Visiting %d\n", current);
            result[result_index++] = current;
            vertexes_visited[current] = 1;
        }
        struct ALGNode* node = graph->list[current];
        while (node != NULL) {
            if (!vertexes_visited[node->vertex]) {
                lkls_push(stack, current);
                lkls_push(stack, node->vertex);
                break;
            } else {
                node = node->next;
            }
        }
    }

    return result;
}

void __dfs(struct AdjacencyListGraph* graph, int vertex, int* visited, int* result, int* result_index) {
    if (!visited[vertex]) {
        visited[vertex] = 1;
        result[(*result_index)++] = vertex;
        struct ALGNode* node = graph->list[vertex];
        while (node != NULL) {
            __dfs(graph, node->vertex, visited, result, result_index);
            node = node->next;
        }
    }
}

int* graph_dfs_recursive(struct AdjacencyListGraph* graph, int from) {
    int* result = (int*) malloc(sizeof(int) * MAX_GRAPH_SIZE);
    int* vertexes_visited = (int*) malloc(sizeof(int) * MAX_GRAPH_SIZE);
    int result_index = 0;
    memset(vertexes_visited, 0, MAX_GRAPH_SIZE);
    __dfs(graph, from, vertexes_visited, result, &result_index);
    free(vertexes_visited);
    return result;
}

struct SpanTreeResult {
    struct ALGNode** selected;
    int total;
};

int min_span(const void* a, const void* b) {
    return ((struct ALGNode*)a)->weight < ((struct ALGNode*)b)->weight;
}


struct SpanTreeResult graph_span_tree(struct AdjacencyListGraph* graph) {
    struct Heap* heap = create_heap(10000, sizeof(struct ALGNode), min_span);
    int edges_already_added[1000][1000];
    for (int c = 0; c < 1000; c++) for (int r = 0; r < 1000; r++) edges_already_added[r][c] = -1;
    for (int vertex = 0; vertex < MAX_GRAPH_SIZE; vertex++) {
        struct ALGNode* node = graph_get_vertex_edges(graph, vertex);
        while (node != NULL) {
            if (edges_already_added[node->parent_vertex][node->vertex] == 1) {
                node = node->next;
                continue;
            }
            heap_insert(heap, node);
            edges_already_added[node->parent_vertex][node->vertex] = 1;
            edges_already_added[node->vertex][node->parent_vertex] = 1;
        }
    }
    int total = 0;
    struct IntDisjointSet* disjoint_sets = create_int_disjoint_set();
    while (heap_top(heap) != NULL) {
        struct ALGNode* min = (struct ALGNode*) heap_top(heap);
        // printf("VERTEX %d - %d, WEIGHT: %d\n", min->vertex, min->parent_vertex, min->weight);
        if (!int_disjoint_set_has(disjoint_sets, min->parent_vertex, min->vertex)) {
            // printf("SELECTED!\n");
            total += min->weight;
            int_disjoint_set_union(disjoint_sets, min->parent_vertex, min->vertex);
        }
        heap_delete(heap);
    }

    struct SpanTreeResult result = {
        .total = total
    };

    return result;
}