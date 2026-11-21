#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <stddef.h>

typedef struct {
    size_t *parent;     // Parent of each element. A root is its own parent.
    size_t *rank;       // Upper bound on the height of the tree rooted at each element.
    size_t size;        // Number of elements.
    size_t components;  // Current number of disjoint sets.
} disjoint_set;

/*
 * Allocates and initializes a set where every element is in its own component.
 * @param size Number of elements, numbered 0 to size - 1.
 * @return Pointer to the newly created structure, or NULL on failure.
 */
disjoint_set *dsu_create(size_t size);

/*
 * Frees the parent and rank arrays and the structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param dsu Pointer to the structure pointer.
 */
void dsu_destroy(disjoint_set **dsu);

/*
 * Finds the root of an element's set, compressing the path along the way.
 * @param dsu Pointer to the structure.
 * @param element Element to look up.
 * @param result Pointer where the root will be stored.
 * @return 0 on success, -1 on failure or if the element is out of range.
 */
int dsu_find(disjoint_set *dsu, size_t element, size_t *result);

/*
 * Merges the sets containing two elements, attaching the lower-rank root under the higher.
 * Does nothing if they are already in the same set.
 * @param dsu Pointer to the structure.
 * @param first First element.
 * @param second Second element.
 * @return 0 on success, -1 on failure or if an element is out of range.
 */
int dsu_union(disjoint_set *dsu, size_t first, size_t second);

/*
 * Checks whether two elements are in the same set.
 * @param dsu Pointer to the structure.
 * @param first First element.
 * @param second Second element.
 * @return 1 if connected, 0 otherwise (including invalid arguments).
 */
int dsu_connected(disjoint_set *dsu, size_t first, size_t second);

/*
 * Returns the number of disjoint sets.
 * @param dsu Pointer to the structure.
 * @return Current component count, or 0 if the structure is NULL.
 */
size_t dsu_count_components(disjoint_set *dsu);

#endif // DISJOINT_SET_H
