#include <stdio.h>
#include "singly_linked_list.h"
#include <inttypes.h>
#include <stdlib.h>

singly_linked_list *sll_create(void) {
    singly_linked_list *sll = malloc(sizeof(*sll));
    if (!sll) return NULL;

    sll->head = sll->tail = NULL;

    sll->size = 0;

    return sll;
}

size_t sll_size(singly_linked_list *list) {
    return list->size;
}

int sll_print(singly_linked_list *list) {
    if (!list) return -1;

    sll_node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf(" NULL\n");

    return 0;
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

int sll_pop_front(singly_linked_list *list, sll_element_t *result) {
    if (!list || !result || !list->head) return -1;

    sll_node *old = list->head;
    *result = old->data;

    list->head = old->next;
    if (!list->head) list->tail = NULL;

    free(old);
    list->size--;

    return 0;
}

int sll_pop_back(singly_linked_list *list, sll_element_t *result) {
    if (!list || !result || !list->head) return -1;

    *result = list->tail->data;

    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        sll_node *current = list->head;
        while (current->next != list->tail) current = current->next;

        free(list->tail);
        current->next = NULL;
        list->tail = current;
    }

    list->size--;
    return 0;
}
