#include "singly_linked_list.h"
#include <stdlib.h>

singly_linked_list *sll_create(void) {
    singly_linked_list *sll = malloc(sizeof(*sll));
    if (!sll) return NULL;

    sll->head = sll->tail = NULL;

    sll->size = 0;

    return sll;
}

void sll_destroy(singly_linked_list **list) {
    if (!list || !(*list)) return;

    sll_node *current = (*list)->head;
    while (current != NULL) {
        sll_node *next = current->next;
        free(current);
        current = next;
    }

    free(*list);
    *list = NULL;
}

int sll_push_front(singly_linked_list *list, sll_element_t element) {
    if (!list) return -1;
    
    sll_node *nd = malloc(sizeof(*nd));
    if (!nd) return -1;

    nd->data = element;
    nd->next = list->head;
    list->head = nd;

    if (!list->tail) list->tail = nd;

    list->size++;

    return 0;
}

int sll_push_back(singly_linked_list *list, sll_element_t element) {
    if (!list) return -1;

    sll_node *nd = malloc(sizeof(*nd));
    if (!nd) return -1;

    nd->data = element;
    nd->next = NULL;
    
    if (!list->tail) {
        list->head = nd;
    } else {
        list->tail->next = nd;
    }

    list->tail = nd;
    list->size++;

    return 0;
}