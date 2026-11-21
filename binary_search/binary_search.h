#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stddef.h>

typedef int bs_element_t;

/*
 * Searches a sorted array for a target using an iterative midpoint loop.
 * @param array Pointer to the sorted array.
 * @param size Number of elements in the array.
 * @param target Value to search for.
 * @param result Pointer where the found index will be stored.
 * @return 0 on success, -1 if the target is not found or an error occurs.
 */
int bs_search_iterative(const bs_element_t *array, size_t size, bs_element_t target, size_t *result);

/*
 * Searches a sorted array for a target using recursive interval halving.
 * @param array Pointer to the sorted array.
 * @param size Number of elements in the array.
 * @param target Value to search for.
 * @param result Pointer where the found index will be stored.
 * @return 0 on success, -1 if the target is not found or an error occurs.
 */
int bs_search_recursive(const bs_element_t *array, size_t size, bs_element_t target, size_t *result);

/*
 * Finds the index of the first element greater than or equal to the target.
 * @param array Pointer to the sorted array.
 * @param size Number of elements in the array.
 * @param target Value to compare against.
 * @param result Pointer where the index will be stored. Equals size if every element is smaller.
 * @return 0 on success, -1 on failure.
 */
int bs_lower_bound(const bs_element_t *array, size_t size, bs_element_t target, size_t *result);

/*
 * Finds the index of the first element strictly greater than the target.
 * @param array Pointer to the sorted array.
 * @param size Number of elements in the array.
 * @param target Value to compare against.
 * @param result Pointer where the index will be stored. Equals size if no element is greater.
 * @return 0 on success, -1 on failure.
 */
int bs_upper_bound(const bs_element_t *array, size_t size, bs_element_t target, size_t *result);

#endif // BINARY_SEARCH_H
