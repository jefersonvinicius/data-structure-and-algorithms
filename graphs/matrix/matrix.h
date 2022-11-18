#include "stdlib.h"
#include "string.h"
#include "../../_utils_/conversions.h"
#include "../../_utils_/debug.h"
#include "../../queue/linkedlist/queue.h"

#define MAX_GRAPH_MATRIX_SIZE 100

struct AdjacencyMatrixGraph {
    int size;
    int *matrix;
};

struct AdjacencyMatrixGraph* create_adj_matrix_graph(int size) {
    struct AdjacencyMatrixGraph* graph = malloc(sizeof(struct AdjacencyMatrixGraph*));
    graph->size = size;
    graph->matrix = malloc(sizeof(int) * size * size);
    for (int i = 0; i < size * size; i++) {
        graph->matrix[i] = 0;
    }
    return graph;
}

int __matrix_get(struct AdjacencyMatrixGraph* graph, int row, int col) {
    return graph->matrix[row * graph->size + col];
}

void __matrix_set(struct AdjacencyMatrixGraph* graph, int row, int col, int value) {
    graph->matrix[row * graph->size + col] = value;
}

void amgraph_add_edge(struct AdjacencyMatrixGraph* graph, int node1, int node2, int weight) {
    __matrix_set(graph, node1, node2, weight);
    __matrix_set(graph, node2, node1, weight);
}

int amgraph_get_edge(struct AdjacencyMatrixGraph* graph, int node1, int node2) {
    return __matrix_get(graph, node1, node2);
}


int* amgraph_bfs(struct AdjacencyMatrixGraph* graph, int from) {
    int* result = malloc(sizeof(int) * graph->size);
    int result_index = 0;
    int vertexes_visited[graph->size+1], vertexes_already_pending[graph->size+1];
    memset(vertexes_visited, 0, graph->size+1); memset(vertexes_already_pending, 0, graph->size+1);
    struct LklQueue* pending = create_lkl_queue();    

    lklq_enqueue(pending, from);
    while (!lklq_is_empty(pending)) {
        int current = pending->front->data;
        if (vertexes_visited[current] == 1) continue;

        debug_log("Visiting: %d\n", current);
        lklq_dequeue(pending);
        vertexes_visited[current] = 1;

        for (int vertex = 0; vertex < graph->size; vertex++) {
            int edge_weight = amgraph_get_edge(graph, current, vertex);
            if (vertex != current && edge_weight != 0 && 
                vertexes_visited[vertex] != 1 && vertexes_already_pending[vertex] != 1) {
                debug_log("Adding %d to pending list\n", vertex);
                lklq_enqueue(pending, vertex);
                vertexes_already_pending[vertex] = 1;
            }
        }
        
        result[result_index] = current;
        result_index++;
    }
    
    free(pending);
    return result;
}

