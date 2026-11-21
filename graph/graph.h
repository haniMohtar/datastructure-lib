#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

#include "../singly_linked_list/singly_linked_list.h"

typedef struct {
    size_t to;      // Destination vertex.
    int weight;     // Edge weight. Use 1 for unweighted graphs.
} graph_edge;

typedef struct {
    singly_linked_list **adjacency; // One list of outgoing edges per vertex.
    size_t vertex_count;            // Current number of vertices.
    int directed;                   // Non-zero if edges are one-way.
} graph;

/*
 * Allocates and initializes a graph with no edges on the heap.
 * @param vertex_count Initial number of vertices.
 * @param directed Non-zero for a directed graph, 0 for undirected.
 * @return Pointer to the newly created graph, or NULL on failure.
 */
graph *graph_create(size_t vertex_count, int directed);

/*
 * Frees every adjacency list and the graph structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param g Pointer to the graph pointer.
 */
void graph_destroy(graph **g);

/*
 * Adds a new vertex with no edges.
 * @param g Pointer to the graph.
 * @param result Pointer where the index of the new vertex will be stored.
 * @return 0 on success, -1 on failure.
 */
int graph_add_vertex(graph *g, size_t *result);

/*
 * Adds an edge. For an undirected graph, the reverse edge is added as well.
 * @param g Pointer to the graph.
 * @param from Source vertex.
 * @param to Destination vertex.
 * @param weight Edge weight.
 * @return 0 on success, -1 on failure or if a vertex is out of range.
 */
int graph_add_edge(graph *g, size_t from, size_t to, int weight);

/*
 * Removes an edge. For an undirected graph, the reverse edge is removed as well.
 * @param g Pointer to the graph.
 * @param from Source vertex.
 * @param to Destination vertex.
 * @return 0 on success, -1 if the edge does not exist or an error occurs.
 */
int graph_remove_edge(graph *g, size_t from, size_t to);

/*
 * Checks whether an edge exists.
 * @param g Pointer to the graph.
 * @param from Source vertex.
 * @param to Destination vertex.
 * @return 1 if the edge exists, 0 otherwise (including invalid arguments).
 */
int graph_has_edge(graph *g, size_t from, size_t to);

/*
 * Retrieves the adjacency list of a vertex.
 * The list is owned by the graph and must not be destroyed by the caller.
 * @param g Pointer to the graph.
 * @param vertex Vertex whose neighbors are wanted.
 * @param result Pointer where the list pointer will be stored.
 * @return 0 on success, -1 on failure or if the vertex is out of range.
 */
int graph_get_neighbors(graph *g, size_t vertex, singly_linked_list **result);

/*
 * Prints every vertex and its adjacency list.
 * @param g Pointer to the graph.
 * @return 0 on success, -1 on failure.
 */
int graph_print(graph *g);

#endif // GRAPH_H
