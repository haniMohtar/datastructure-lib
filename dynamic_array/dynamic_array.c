#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "dynamic_array.h"

dynamic_array *create_array(size_t initial_capacity) {
    if (initial_capacity > SIZE_MAX / sizeof(element_t)) return NULL;

    dynamic_array *array = malloc(sizeof(dynamic_array));
    if (!array) return NULL;

    array->data = calloc(initial_capacity, sizeof(element_t));

    if (!array->data && initial_capacity > 0) {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = initial_capacity;

    return array;
}

size_t size(dynamic_array *array) {
    return array ? array->size : 0;
}

size_t capacity(dynamic_array *array) {
    return array ? array->capacity : 0;
}

void destroy(dynamic_array **array) {
    if (!array || !*array) return;

    free((*array)->data);
    free(*array);

    *array = NULL;
}

int resize(dynamic_array *array, size_t new_capacity) {
    if (!array) return -1;

    if (new_capacity < array->size) return -1;

    if (new_capacity > SIZE_MAX / sizeof(element_t)) return -1;

    if (new_capacity == 0) {
        free(array->data);
        array->data = NULL;
        array->capacity = 0;
        return 0;
    }

    element_t *temp = realloc(array->data, new_capacity * sizeof(element_t));

    if (!temp) return -1;

    array->data = temp;
    array->capacity = new_capacity;

    return 0;
}

int push_back(dynamic_array *array, element_t element) {
    if (!array) return -1;

    if (size(array) == capacity(array)) {
        size_t new_capacity = capacity(array) == 0
                            ? 1
                            : capacity(array) * GROWTH_FACTOR;

        if (resize(array, new_capacity) == -1) return -1;
    }

    array->data[array->size] = element;
    array->size++;

    return 0;
}

int get(dynamic_array *array, size_t index, element_t *result) {
    if (!array || !result || index >= size(array)) return -1;
    *result = array->data[index];
    return 0;
}

int set(dynamic_array *array, size_t index, element_t element) {
    if (!array || index >= size(array)) return -1;

    array->data[index] = element;
    return 0;
}

int pop_back(dynamic_array *array, element_t *result) {
    if (!array || !result || size(array) == 0) return -1;

    *result = array->data[array->size - 1];
    array->size--;

    return 0;
}

int insert_at(dynamic_array *array, size_t index, element_t element) {
    if (!array) return -1;

    if (index > size(array)) index = size(array);

    if (size(array) == capacity(array)) {
        size_t new_capacity = capacity(array) == 0
                            ? 1
                            : capacity(array) * GROWTH_FACTOR;

        if (resize(array, new_capacity) == -1) return -1;
    }

    memmove(&array->data[index + 1], &array->data[index], (size(array) - index) * sizeof(element_t));

    array->data[index] = element;
    array->size++;

    return 0;
}

int remove_at(dynamic_array *array, size_t index) {
    if (!array || index >= size(array)) return -1;

    memmove(&array->data[index], &array->data[index + 1], (size(array) - index - 1) * sizeof(element_t));

    array->size--;

    return 0;
}

int shrink(dynamic_array *array) {
    if (!array) return -1;

    if (size(array) == capacity(array)) return 0;
    return resize(array, size(array));
}

int find(dynamic_array *array, element_t element, size_t *result) {
    if (!array || !result) return -1;

    for (size_t i = 0; i < size(array); i++) {
        if (array->data[i] == element) {
            *result = i;
            return 0;
        }
    }

    return -1;
}

int clear(dynamic_array *array) {
    if (!array) return -1;

    array->size = 0;

    return 0;
}

int reverse(dynamic_array *array) {
    if (!array) return -1;
    if (size(array) < 2) return 0;

    size_t i = 0, j = size(array) - 1;

    while (i < j) {
        element_t temp = array->data[i];
        array->data[i] = array->data[j];
        array->data[j] = temp;
        i++;
        j--;
    }

    return 0;
}

dynamic_array *copy(dynamic_array *array) {
    if (!array) return NULL;

    dynamic_array *new_array = create_array(capacity(array));
    if (!new_array) return NULL;

    if (size(array) > 0) memcpy(new_array->data, array->data, size(array) * sizeof(element_t));

    new_array->size = size(array);
    
    return new_array;
}

int swap(dynamic_array *first_array, dynamic_array *second_array) {
    if (!first_array || !second_array) return -1;

    dynamic_array temp = *first_array;
    *first_array = *second_array;
    *second_array = temp;

    return 0;
}

int main(void) {
    printf("hello, world\n");
    return 0;
}