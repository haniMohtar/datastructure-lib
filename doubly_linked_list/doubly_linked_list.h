#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef int dll_element_t;

typedef struct dll_node {
    dll_element_t data;     // Value stored in the node.
    struct dll_node *next;  // Next node, or NULL at the tail.
    struct dll_node *prev;  // Previous node, or NULL at the head.
} dll_node;

typedef struct {
    dll_node *head;     // First node, or NULL when empty.
    dll_node *tail;     // Last node, or NULL when empty.
    size_t size;        // Current number of nodes in the list.
} doubly_linked_list;

/*
 * Allocates and initializes an empty list on the heap.
 * @return Pointer to the newly created list, or NULL on failure.
 */
doubly_linked_list *dll_create(void);

/*
 * Frees every node and the list structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param list Pointer to the list pointer.
 */
void dll_destroy(doubly_linked_list **list);

/*
 * Inserts an element at the front of the list.
 * @param list Pointer to the list.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int dll_push_front(doubly_linked_list *list, dll_element_t element);

/*
 * Appends an element at the end of the list.
 * @param list Pointer to the list.
 * @param element Value to append.
 * @return 0 on success, -1 on failure.
 */
int dll_push_back(doubly_linked_list *list, dll_element_t element);

/*
 * Removes and retrieves the first element of the list.
 * @param list Pointer to the list.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the list is empty.
 */
int dll_pop_front(doubly_linked_list *list, dll_element_t *result);

/*
 * Removes and retrieves the last element of the list.
 * @param list Pointer to the list.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the list is empty.
 */
int dll_pop_back(doubly_linked_list *list, dll_element_t *result);

/*
 * Inserts an element immediately before the given node.
 * @param list Pointer to the list.
 * @param node Node before which the element is inserted. Must belong to the list.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int dll_insert_before(doubly_linked_list *list, dll_node *node, dll_element_t element);

/*
 * Inserts an element immediately after the given node.
 * @param list Pointer to the list.
 * @param node Node after which the element is inserted. Must belong to the list.
 * @param element Value to insert.
 * @return 0 on success, -1 on failure.
 */
int dll_insert_after(doubly_linked_list *list, dll_node *node, dll_element_t element);

/*
 * Unlinks and frees the given node in O(1).
 * @param list Pointer to the list.
 * @param node Node to delete. Must belong to the list.
 * @return 0 on success, -1 on failure.
 */
int dll_delete_node(doubly_linked_list *list, dll_node *node);

/*
 * Searches for the first node holding the specified value, from head forward.
 * @param list Pointer to the list.
 * @param element Value to search for.
 * @param result Pointer where the found node will be stored.
 * @return 0 on success, -1 if the value is not found or an error occurs.
 */
int dll_find(doubly_linked_list *list, dll_element_t element, dll_node **result);

/*
 * Returns the number of nodes in the list.
 * @param list Pointer to the list.
 * @return Current size, or 0 if the list is NULL.
 */
size_t dll_size(doubly_linked_list *list);

/*
 * Prints every element from head to tail on a single line.
 * @param list Pointer to the list.
 * @return 0 on success, -1 on failure.
 */
int dll_print_forward(doubly_linked_list *list);

/*
 * Prints every element from tail to head on a single line.
 * @param list Pointer to the list.
 * @return 0 on success, -1 on failure.
 */
int dll_print_backward(doubly_linked_list *list);

#endif // DOUBLY_LINKED_LIST_H
