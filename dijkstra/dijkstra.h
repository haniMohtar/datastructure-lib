#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include "../graph/graph.h"
#include "../binary_heap/binary_heap.h"

#define DJ_INFINITY INT_MAX     // Distance of a vertex that cannot be reached.
#define DJ_NO_PARENT SIZE_MAX   // Parent of the source and of unreachable vertices.

/*
 * Solves single-source shortest paths on a graph with non-negative weights.
 * @param g Pointer to the graph.
 * @param source Starting vertex.
 * @param distances Array of vertex_count entries that receives the shortest distances.
 * @param parents Array of vertex_count entries that receives each vertex's predecessor.
 * @return 0 on success, -1 on failure or if a negative weight is found.
 */
int dj_dijkstra(graph *g, size_t source, int *distances, size_t *parents);

/*
 * Tries to improve the distance to a vertex through another vertex.
 * @param distances Array of current distances.
 * @param parents Array of current predecessors.
 * @param from Vertex being expanded.
 * @param to Neighbor being relaxed.
 * @param weight Weight of the edge from to to.
 * @param result Pointer where 1 is stored if the distance improved, otherwise 0.
 * @return 0 on success, -1 on failure.
 */
int dj_relax_edge(int *distances, size_t *parents, size_t from, size_t to, int weight, int *result);

/*
 * Rebuilds the shortest path from the source to a destination using the parents array.
 * @param parents Array filled in by dj_dijkstra.
 * @param source Starting vertex used for dj_dijkstra.
 * @param destination Target vertex.
 * @param path Buffer that receives the vertices in order from source to destination.
 * @param path_capacity Number of slots in the path buffer.
 * @param result Pointer where the number of vertices in the path will be stored.
 * @return 0 on success, -1 if the destination is unreachable, the buffer is too small, or an error occurs.
 */
int dj_reconstruct_path(const size_t *parents, size_t source, size_t destination,
                        size_t *path, size_t path_capacity, size_t *result);

/*
 * Prints the shortest distance from the source to every vertex.
 * @param distances Array filled in by dj_dijkstra.
 * @param count Number of vertices.
 * @return 0 on success, -1 on failure.
 */
int dj_print_distances(const int *distances, size_t count);

#endif // DIJKSTRA_H
