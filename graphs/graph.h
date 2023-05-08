#include "limits.h"
#include "node.h"
#include "stdlib.h"
#include "math.h"
#include <string.h>
#include "queue/queue.h"
#include "heap/heap.h"
#include "pair/pair.h"
#include "stack/linkedlist/stack.h"
#include "sets/disjoint/disjoint.h"
#include "heap/heap.h"
#include "array/array.h"
#include "_utils_/debug.h"
#include "_utils_/conversions.h"

#define MAX_GRAPH_SIZE 1000

enum GraphBidirectionalFlag {
    NotBidirectional = 0,
    IsBidirectional = 1
};

struct AdjacencyListGraph {
    struct ALGNode** list;
    enum GraphBidirectionalFlag is_bidirectional;
    size_t size;
};

struct AdjacencyListGraph* create_adjacency_list_graph(enum GraphBidirectionalFlag is_bidirectional) {
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
    if (graph->is_bidirectional == IsBidirectional) {
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

    lklq_enqueue(pending, &from);
    while (!lklq_is_empty(pending)) {
        int current = *((int*) lklq_front(pending));
        debug_log("Visiting: %d\n", current);

        lklq_dequeue(pending);
        vertexes_visited[current] = 1;

        struct ALGNode* node = graph->list[current];
        while (node != NULL) {
            if (vertexes_visited[node->vertex] != 1 && vertexes_already_pending[node->vertex] != 1) {
                debug_log("Adding %d to pending list\n", node->vertex);
                lklq_enqueue(pending, &node->vertex);
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

struct KruskalResult {
    struct Array* selected_nodes;
    int total;
};

int min_span(const void* a, const void* b) {
    return ((struct ALGNode*)a)->weight < ((struct ALGNode*)b)->weight;
}

struct KruskalResult graph_kruskal(struct AdjacencyListGraph* graph) {
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
    struct Array* selected_nodes = create_array(sizeof(struct ALGNode));
    while (heap_top(heap) != NULL) {
        struct ALGNode* min = (struct ALGNode*) heap_top(heap);
        if (!int_disjoint_set_has(disjoint_sets, min->parent_vertex, min->vertex)) {
            total += min->weight;
            array_push(selected_nodes, min);
            int_disjoint_set_union(disjoint_sets, min->parent_vertex, min->vertex);
        }
        heap_delete(heap);
    }

    struct KruskalResult result = {
        .total = total,
        .selected_nodes = selected_nodes
    };

    return result;
}

struct DijkstraResult { double* distances; };

int cmp_pairs(struct Pair* a, struct Pair* b) {
   int a_weight = *((int*)a->left);
   int b_weight = *((int*)b->left);
   return a_weight < b_weight;
}

struct Pair* __make_vertex_pair(struct AdjacencyListGraph* graph, int vertex) {
    return make_pair(&graph_get_vertex_edges(graph, vertex)->weight, intp(vertex));
}

struct DijkstraResult graph_dijkstra(struct AdjacencyListGraph* graph, int initial_vertex) {
    double distances[MAX_GRAPH_SIZE]; for(int i=0;i<MAX_GRAPH_SIZE;i++) distances[i]=INFINITY;
    int visited[MAX_GRAPH_SIZE]; memset(visited, 0, sizeof(visited));
    distances[initial_vertex] = 0;
    struct Heap* heap = create_heap(MAX_GRAPH_SIZE, sizeof(struct Pair), cmp_pairs);
    heap_insert(heap, __make_vertex_pair(graph, initial_vertex));
    while (!heap_is_empty(heap)) {
        struct Pair* pair = (struct Pair*) heap_top(heap);
        int current_vertex = *((int*) pair->right);
        heap_delete(heap);
        if (visited[current_vertex]) continue;
        visited[current_vertex] = 1;
        struct ALGNode* node = graph_get_vertex_edges(graph, current_vertex);
        while (node != NULL) {
            if (distances[current_vertex] + node->weight < distances[node->vertex]) 
                distances[node->vertex] = distances[current_vertex] + node->weight;
            
            if (!visited[node->vertex])
                heap_insert(heap, __make_vertex_pair(graph, node->vertex));
            node = node->next;
        }
    }
    free(heap);
    struct DijkstraResult result = { .distances = distances };
    return result;
}