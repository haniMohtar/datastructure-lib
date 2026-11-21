#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

typedef int sll_element_t;

typedef struct sll_node {
    sll_element_t data;     // Value stored in the node.
    struct sll_node *next;  // Next node, or NULL at the tail.
} sll_node;

typedef struct {
    sll_node *head;     // First node, or NULL when empty.
    sll_node *tail;     // Last node, or NULL when empty.
    size_t size;        // Current number of nodes in the list.
} singly_linked_list;

/*
 * Allocates and initializes an empty list on the heap.
 * @return Pointer to the newly created list, or NULL on failure.
 */
singly_linked_list *sll_create(void);

/*
 * Frees every node and the list structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param list Pointer to the list pointer.
 */
void sll_destroy(singly_linked_list **list);

/*
 * Inserts an element at the front of the list in O(1).
 * @param list Pointer to the list.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int sll_push_front(singly_linked_list *list, sll_element_t element);

/*
 * Appends an element at the end of the list in O(1) using the tail pointer.
 * @param list Pointer to the list.
 * @param element Value to append.
 * @return 0 on success, -1 on failure.
 */
int sll_push_back(singly_linked_list *list, sll_element_t element);

/*
 * Removes and retrieves the first element of the list.
 * @param list Pointer to the list.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the list is empty.
 */
int sll_pop_front(singly_linked_list *list, sll_element_t *result);

/*
 * Removes and retrieves the last element of the list.
 * @param list Pointer to the list.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the list is empty.
 */
int sll_pop_back(singly_linked_list *list, sll_element_t *result);

/*
 * Inserts an element immediately after the given node.
 * @param list Pointer to the list.
 * @param node Node after which the element is inserted. Must belong to the list.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int sll_insert_after(singly_linked_list *list, sll_node *node, sll_element_t element);

/*
 * Removes the first node holding the specified value.
 * @param list Pointer to the list.
 * @param element Value to remove.
 * @return 0 on success, -1 if the value is not found or an error occurs.
 */
int sll_delete_value(singly_linked_list *list, sll_element_t element);

/*
 * Searches for the first node holding the specified value.
 * @param list Pointer to the list.
 * @param element Value to search for.
 * @param result Pointer where the found node will be stored.
 * @return 0 on success, -1 if the value is not found or an error occurs.
 */
int sll_find(singly_linked_list *list, sll_element_t element, sll_node **result);

/*
 * Returns the number of nodes in the list.
 * @param list Pointer to the list.
 * @return Current size, or 0 if the list is NULL.
 */
size_t sll_size(singly_linked_list *list);

/*
 * Checks whether the list has no nodes.
 * @param list Pointer to the list.
 * @return 1 if the list is empty or NULL, 0 otherwise.
 */
int sll_is_empty(singly_linked_list *list);

/*
 * Reverses the list in-place by flipping the direction of every link.
 * @param list Pointer to the list.
 * @return 0 on success, -1 on failure.
 */
int sll_reverse(singly_linked_list *list);

/*
 * Prints every element from head to tail on a single line.
 * @param list Pointer to the list.
 * @return 0 on success, -1 on failure.
 */
int sll_print(singly_linked_list *list);

#endif // SINGLY_LINKED_LIST_H
