#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

#define GROWTH_FACTOR 2 // Determines how much the array's capacity grows when resized.

typedef int element_t;

typedef struct {
    element_t *data;    // Array that stores the elements.
    size_t size;        // Current number of elements stored in the array.
    size_t capacity;    // Maximum number of elements that can be stored.
} dynamic_array;

/*
 * Allocates and initializes a dynamic array on the heap.
 * @param initial_capacity Initial number of allocated slots.
 * @return Pointer to the newly created array, or NULL on failure.
 */
dynamic_array *create_array(size_t initial_capacity);

/*
 * Frees the internal buffer and the array structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param array Pointer to the dynamic array pointer.
 */
void destroy(dynamic_array **array);

/*
 * Appends an element to the end of the array.
 * Automatically increases capacity when the array is full.
 * @param array Pointer to the dynamic array.
 * @param element Value to append.
 * @return 0 on success, -1 on failure.
 */
int push_back(dynamic_array *array, element_t element);

/*
 * Retrieves an element at the specified index.
 * @param array Pointer to the dynamic array.
 * @param index Index of the element to retrieve.
 * @param result Pointer where the retrieved value will be stored.
 * @return 0 on success, -1 on failure.
 */
int get(dynamic_array *array, size_t index, element_t *result);

/*
 * Replaces the element at the specified index.
 * @param array Pointer to the dynamic array.
 * @param index Index of the element to modify.
 * @param element New value to store.
 * @return 0 on success, -1 on failure.
 */
int set(dynamic_array *array, size_t index, element_t element);

/*
 * Returns the current number of elements stored in the array.
 * @param array Pointer to the dynamic array.
 * @return Current size, or 0 if the array is NULL.
 */
size_t size(dynamic_array *array);

/*
 * Returns the current allocated capacity of the array.
 * @param array Pointer to the dynamic array.
 * @return Current capacity, or 0 if the array is NULL.
 */
size_t capacity(dynamic_array *array);

/*
 * Removes and retrieves the last element of the array.
 * Does not reduce the allocated capacity.
 * @param array Pointer to the dynamic array.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure.
 */
int pop_back(dynamic_array *array, element_t *result);

/*
 * Inserts an element at the specified index.
 * Shifts subsequent elements one position to the right.
 * Automatically increases capacity when necessary.
 * @param array Pointer to the dynamic array.
 * @param index Position at which the element will be inserted.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int insert_at(dynamic_array *array, size_t index, element_t element);

/*
 * Removes the element at the specified index.
 * Shifts subsequent elements one position to the left.
 * Does not reduce the allocated capacity.
 * @param array Pointer to the dynamic array.
 * @param index Index of the element to remove.
 * @return 0 on success, -1 on failure.
 */
int remove_at(dynamic_array *array, size_t index);

/*
 * Changes the allocated capacity of the array.
 * Preserves existing elements when possible.
 * Fails if new_capacity is smaller than the current size.
 * @param array Pointer to the dynamic array.
 * @param new_capacity Desired capacity.
 * @return 0 on success, -1 on failure.
 */
int resize(dynamic_array *array, size_t new_capacity);

/*
 * Reduces the allocated capacity to match the current size.
 * @param array Pointer to the dynamic array.
 * @return 0 on success, -1 on failure.
 */
int shrink(dynamic_array *array);

/*
 * Searches for the first occurrence of a specified element.
 * @param array Pointer to the dynamic array.
 * @param element Value to search for.
 * @param result Pointer where the found index will be stored.
 * @return 0 on success, -1 if the element is not found or an error occurs.
 */
int find(dynamic_array *array, element_t element, size_t *result);

/*
 * Removes all elements from the array without freeing its allocated buffer.
 * Sets the array's size to zero.
 * @param array Pointer to the dynamic array.
 * @return 0 on success, -1 on failure.
 */
int clear(dynamic_array *array);

/*
 * Reverses the order of elements in-place using a two-pointer swap strategy.
 * Does not change the array's size or capacity.
 * @param array Pointer to the dynamic array.
 * @return 0 on success, -1 on failure.
 */
int reverse(dynamic_array *array);

/*
 * Creates a deep copy of an existing dynamic array.
 * Allocates a new structure and an independent internal buffer.
 * @param array Pointer to the source dynamic array.
 * @return Pointer to the copied array, or NULL on failure.
 */
dynamic_array *copy(dynamic_array *array);

/*
 * Swaps the internal buffers, sizes, and capacities of two arrays.
 * Does not allocate or free memory.
 * @param first_array Pointer to the first dynamic array.
 * @param second_array Pointer to the second dynamic array.
 * @return 0 on success, -1 on failure.
 */
int swap(dynamic_array *first_array, dynamic_array *second_array);

#endif // DYNAMIC_ARRAY_H