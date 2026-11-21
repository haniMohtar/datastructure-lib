#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stddef.h>

#include "../dynamic_array/dynamic_array.h"

typedef da_element_t heap_element_t;

typedef struct {
    dynamic_array *array;   // Complete binary tree stored level by level. This is a min-heap.
} heap;

/*
 * Allocates and initializes an empty min-heap on the heap.
 * @param initial_capacity Initial number of allocated slots.
 * @return Pointer to the newly created heap, or NULL on failure.
 */
heap *heap_create(size_t initial_capacity);

/*
 * Frees the underlying array and the heap structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param h Pointer to the heap pointer.
 */
void heap_destroy(heap **h);

/*
 * Inserts an element and sifts it up to its correct position.
 * @param h Pointer to the heap.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int heap_push(heap *h, heap_element_t element);

/*
 * Removes and retrieves the smallest element, then sifts the replacement down.
 * @param h Pointer to the heap.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the heap is empty.
 */
int heap_pop(heap *h, heap_element_t *result);

/*
 * Retrieves the smallest element without removing it.
 * @param h Pointer to the heap.
 * @param result Pointer where the value will be stored.
 * @return 0 on success, -1 on failure or if the heap is empty.
 */
int heap_peek(heap *h, heap_element_t *result);

/*
 * Builds a valid heap from an unordered array in O(n) using bottom-up heapify.
 * The values are copied.
 * @param values Pointer to the source values.
 * @param count Number of values.
 * @return Pointer to the newly created heap, or NULL on failure.
 */
heap *heap_build(const heap_element_t *values, size_t count);

/*
 * Sorts an array in ascending order in-place using heap sort.
 * @param array Pointer to the array.
 * @param size Number of elements in the array.
 * @return 0 on success, -1 on failure.
 */
int heap_sort(heap_element_t *array, size_t size);

/*
 * Checks whether the heap has no elements.
 * @param h Pointer to the heap.
 * @return 1 if the heap is empty or NULL, 0 otherwise.
 */
int heap_is_empty(heap *h);

/*
 * Returns the number of elements in the heap.
 * @param h Pointer to the heap.
 * @return Current size, or 0 if the heap is NULL.
 */
size_t heap_size(heap *h);

#endif // BINARY_HEAP_H
