#ifndef INSERTION_MERGE_SORT_H
#define INSERTION_MERGE_SORT_H

#include <stddef.h>

typedef int sort_element_t;

/*
 * Sorts the array in ascending order in-place by shifting elements into position.
 * Stable. O(n^2) worst case, O(1) extra space.
 * @param array Pointer to the array.
 * @param size Number of elements in the array.
 * @return 0 on success, -1 on failure.
 */
int sort_insertion(sort_element_t *array, size_t size);

/*
 * Sorts the array in ascending order by recursively splitting and merging.
 * Stable. O(n log n) time, allocates an auxiliary buffer.
 * @param array Pointer to the array.
 * @param size Number of elements in the array.
 * @return 0 on success, -1 on failure (including allocation failure).
 */
int sort_merge(sort_element_t *array, size_t size);

/*
 * Merges two sorted sequences into one sorted target buffer.
 * @param left Pointer to the first sorted sequence.
 * @param left_size Number of elements in the first sequence.
 * @param right Pointer to the second sorted sequence.
 * @param right_size Number of elements in the second sequence.
 * @param target Buffer with room for left_size + right_size elements.
 * @return 0 on success, -1 on failure.
 */
int sort_merge_arrays(const sort_element_t *left, size_t left_size,
                      const sort_element_t *right, size_t right_size,
                      sort_element_t *target);

/*
 * Checks whether the array is in non-decreasing order.
 * @param array Pointer to the array.
 * @param size Number of elements in the array.
 * @return 1 if sorted (including size 0 or 1), 0 otherwise or if the array is NULL.
 */
int sort_is_sorted(const sort_element_t *array, size_t size);

#endif // INSERTION_MERGE_SORT_H
