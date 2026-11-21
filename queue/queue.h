#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "../singly_linked_list/singly_linked_list.h"

typedef sll_element_t queue_element_t;

/* ---------- Circular buffer queue (fixed capacity) ---------- */

typedef struct {
    queue_element_t *data;  // Ring buffer that stores the elements.
    size_t capacity;        // Fixed number of slots in the buffer.
    size_t front;           // Index of the front element.
    size_t size;            // Current number of elements in the queue.
} ring_queue;

/*
 * Allocates and initializes an empty circular queue on the heap.
 * @param capacity Fixed number of slots. Must be greater than 0.
 * @return Pointer to the newly created queue, or NULL on failure.
 */
ring_queue *rq_create(size_t capacity);

/*
 * Frees the buffer and the queue structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param queue Pointer to the queue pointer.
 */
void rq_destroy(ring_queue **queue);

/*
 * Adds an element at the rear of the queue, wrapping around the buffer.
 * @param queue Pointer to the queue.
 * @param element Value to add.
 * @return 0 on success, -1 on failure or if the queue is full.
 */
int rq_enqueue(ring_queue *queue, queue_element_t element);

/*
 * Removes and retrieves the front element of the queue.
 * @param queue Pointer to the queue.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the queue is empty.
 */
int rq_dequeue(ring_queue *queue, queue_element_t *result);

/*
 * Retrieves the front element without removing it.
 * @param queue Pointer to the queue.
 * @param result Pointer where the front value will be stored.
 * @return 0 on success, -1 on failure or if the queue is empty.
 */
int rq_front(ring_queue *queue, queue_element_t *result);

/*
 * Checks whether the queue has no elements.
 * @param queue Pointer to the queue.
 * @return 1 if the queue is empty or NULL, 0 otherwise.
 */
int rq_is_empty(ring_queue *queue);

/*
 * Checks whether the queue has reached its capacity.
 * @param queue Pointer to the queue.
 * @return 1 if the queue is full, 0 otherwise (including NULL).
 */
int rq_is_full(ring_queue *queue);

/*
 * Returns the number of elements in the queue.
 * @param queue Pointer to the queue.
 * @return Current size, or 0 if the queue is NULL.
 */
size_t rq_size(ring_queue *queue);

/* ---------- Linked list queue (unbounded) ---------- */

typedef struct {
    singly_linked_list *list;   // Underlying list. Front is the head, rear is the tail.
} list_queue;

/*
 * Allocates and initializes an empty linked list queue on the heap.
 * @return Pointer to the newly created queue, or NULL on failure.
 */
list_queue *lq_create(void);

/*
 * Frees every node and the queue structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param queue Pointer to the queue pointer.
 */
void lq_destroy(list_queue **queue);

/*
 * Adds an element at the rear of the queue.
 * @param queue Pointer to the queue.
 * @param element Value to add.
 * @return 0 on success, -1 on failure.
 */
int lq_enqueue(list_queue *queue, queue_element_t element);

/*
 * Removes and retrieves the front element of the queue.
 * @param queue Pointer to the queue.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the queue is empty.
 */
int lq_dequeue(list_queue *queue, queue_element_t *result);

/*
 * Retrieves the front element without removing it.
 * @param queue Pointer to the queue.
 * @param result Pointer where the front value will be stored.
 * @return 0 on success, -1 on failure or if the queue is empty.
 */
int lq_front(list_queue *queue, queue_element_t *result);

/*
 * Checks whether the queue has no elements.
 * @param queue Pointer to the queue.
 * @return 1 if the queue is empty or NULL, 0 otherwise.
 */
int lq_is_empty(list_queue *queue);

/*
 * Returns the number of elements in the queue.
 * @param queue Pointer to the queue.
 * @return Current size, or 0 if the queue is NULL.
 */
size_t lq_size(list_queue *queue);

#endif // QUEUE_H
