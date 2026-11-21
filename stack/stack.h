#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#include "../dynamic_array/dynamic_array.h"

typedef da_element_t stack_element_t;

typedef struct {
    dynamic_array *array;   // Underlying array. The top of the stack is its last element.
} stack;

/*
 * Allocates and initializes an empty stack on the heap.
 * @param initial_capacity Initial number of allocated slots.
 * @return Pointer to the newly created stack, or NULL on failure.
 */
stack *stack_create(size_t initial_capacity);

/*
 * Frees the underlying array and the stack structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param s Pointer to the stack pointer.
 */
void stack_destroy(stack **s);

/*
 * Pushes an element onto the top of the stack.
 * @param s Pointer to the stack.
 * @param element Value to push.
 * @return 0 on success, -1 on failure.
 */
int stack_push(stack *s, stack_element_t element);

/*
 * Removes and retrieves the top element of the stack.
 * @param s Pointer to the stack.
 * @param result Pointer where the removed value will be stored.
 * @return 0 on success, -1 on failure or if the stack is empty.
 */
int stack_pop(stack *s, stack_element_t *result);

/*
 * Retrieves the top element without removing it.
 * @param s Pointer to the stack.
 * @param result Pointer where the top value will be stored.
 * @return 0 on success, -1 on failure or if the stack is empty.
 */
int stack_peek(stack *s, stack_element_t *result);

/*
 * Checks whether the stack has no elements.
 * @param s Pointer to the stack.
 * @return 1 if the stack is empty or NULL, 0 otherwise.
 */
int stack_is_empty(stack *s);

/*
 * Returns the number of elements on the stack.
 * @param s Pointer to the stack.
 * @return Current size, or 0 if the stack is NULL.
 */
size_t stack_size(stack *s);

#endif // STACK_H
