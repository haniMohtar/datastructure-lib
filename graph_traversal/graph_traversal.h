#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include <stddef.h>

#include "../graph/graph.h"
#include "../stack/stack.h"
#include "../queue/queue.h"

/*
 * Visits vertices reachable from the start in breadth-first order.
 * @param g Pointer to the graph.
 * @param start Starting vertex.
 * @param visit Function called once per visited vertex.
 * @return 0 on success, -1 on failure.
 */
int gt_bfs(graph *g, size_t start, void (*visit)(size_t vertex));

/*
 * Computes the fewest edges between two vertices of an unweighted graph.
 * @param g Pointer to the graph.
 * @param source Starting vertex.
 * @param destination Target vertex.
 * @param result Pointer where the edge count will be stored.
 * @return 0 on success, -1 if the destination is unreachable or an error occurs.
 */
int gt_bfs_shortest_path(graph *g, size_t source, size_t destination, size_t *result);

/*
 * Visits vertices reachable from the start in depth-first order using recursion.
 * @param g Pointer to the graph.
 * @param start Starting vertex.
 * @param visit Function called once per visited vertex.
 * @return 0 on success, -1 on failure.
 */
int gt_dfs_recursive(graph *g, size_t start, void (*visit)(size_t vertex));

/*
 * Visits vertices reachable from the start in depth-first order using an explicit stack.
 * @param g Pointer to the graph.
 * @param start Starting vertex.
 * @param visit Function called once per visited vertex.
 * @return 0 on success, -1 on failure.
 */
int gt_dfs_iterative(graph *g, size_t start, void (*visit)(size_t vertex));

/*
 * Checks whether a path exists between two vertices.
 * @param g Pointer to the graph.
 * @param source Starting vertex.
 * @param destination Target vertex.
 * @return 1 if a path exists, 0 otherwise (including invalid arguments).
 */
int gt_has_path(graph *g, size_t source, size_t destination);

/*
 * Labels every vertex with the id of its connected component.
 * Intended for undirected graphs.
 * @param g Pointer to the graph.
 * @param labels Array of vertex_count entries that receives each vertex's component id.
 * @param result Pointer where the number of components will be stored.
 * @return 0 on success, -1 on failure.
 */
int gt_connected_components(graph *g, size_t *labels, size_t *result);

#endif // GRAPH_TRAVERSAL_H
