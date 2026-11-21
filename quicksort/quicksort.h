#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>

typedef int qs_element_t;

/*
 * Sorts the array in ascending order in-place by recursive partitioning.
 * Uses the Lomuto partition scheme.
 * @param array Pointer to the array.
 * @param size Number of elements in the array.
 * @return 0 on success, -1 on failure.
 */
int qs_quicksort(qs_element_t *array, size_t size);

/*
 * Same as qs_quicksort, but picks a random pivot before each partition.
 * Call srand() once beforehand to vary the sequence.
 * @param array Pointer to the array.
 * @param size Number of elements in the array.
 * @return 0 on success, -1 on failure.
 */
int qs_quicksort_random(qs_element_t *array, size_t size);

/*
 * Partitions array[low..high] using a single sweep and a boundary index.
 * The last element is the pivot.
 * @param array Pointer to the array.
 * @param low First index of the range.
 * @param high Last index of the range (inclusive).
 * @param result Pointer where the final pivot index will be stored.
 * @return 0 on success, -1 on failure.
 */
int qs_partition_lomuto(qs_element_t *array, size_t low, size_t high, size_t *result);

/*
 * Partitions array[low..high] using two pointers converging from both ends.
 * @param array Pointer to the array.
 * @param low First index of the range.
 * @param high Last index of the range (inclusive).
 * @param result Pointer where the partition split index will be stored.
 * @return 0 on success, -1 on failure.
 */
int qs_partition_hoare(qs_element_t *array, size_t low, size_t high, size_t *result);

/*
 * Swaps two elements in place.
 * @param first Pointer to the first element.
 * @param second Pointer to the second element.
 * @return 0 on success, -1 on failure.
 */
int qs_swap(qs_element_t *first, qs_element_t *second);

#endif // QUICKSORT_H
