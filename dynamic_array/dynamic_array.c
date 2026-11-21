#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "dynamic_array.h"

dynamic_array *da_create(size_t initial_capacity) {
    if (initial_capacity > SIZE_MAX / sizeof(da_element_t)) return NULL;

    dynamic_array *array = malloc(sizeof(dynamic_array));
    if (!array) return NULL;

    array->data = calloc(initial_capacity, sizeof(da_element_t));

    if (!array->data && initial_capacity > 0) {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = initial_capacity;

    return array;
}

size_t da_size(dynamic_array *array) {
    return array ? array->size : 0;
}

size_t da_capacity(dynamic_array *array) {
    return array ? array->capacity : 0;
}

void da_destroy(dynamic_array **array) {
    if (!array || !*array) return;

    free((*array)->data);
    free(*array);

    *array = NULL;
}

int da_resize(dynamic_array *array, size_t new_capacity) {
    if (!array) return -1;

    if (new_capacity < array->size) return -1;

    if (new_capacity > SIZE_MAX / sizeof(da_element_t)) return -1;

    if (new_capacity == 0) {
        free(array->data);
        array->data = NULL;
        array->capacity = 0;
        return 0;
    }

    da_element_t *temp = realloc(array->data, new_capacity * sizeof(da_element_t));

    if (!temp) return -1;

    array->data = temp;
    array->capacity = new_capacity;

    return 0;
}

int da_push_back(dynamic_array *array, da_element_t element) {
    if (!array) return -1;

    if (da_size(array) == da_capacity(array)) {
        size_t new_capacity = da_capacity(array) == 0
                            ? 1
                            : da_capacity(array) * DA_GROWTH_FACTOR;

        if (da_resize(array, new_capacity) == -1) return -1;
    }

    array->data[array->size] = element;
    array->size++;

    return 0;
}

int da_get(dynamic_array *array, size_t index, da_element_t *result) {
    if (!array || !result || index >= da_size(array)) return -1;
    *result = array->data[index];
    return 0;
}

int da_set(dynamic_array *array, size_t index, da_element_t element) {
    if (!array || index >= da_size(array)) return -1;

    array->data[index] = element;
    return 0;
}

int da_pop_back(dynamic_array *array, da_element_t *result) {
    if (!array || !result || da_size(array) == 0) return -1;

    *result = array->data[array->size - 1];
    array->size--;

    return 0;
}

int da_insert_at(dynamic_array *array, size_t index, da_element_t element) {
    if (!array) return -1;

    if (index > da_size(array)) index = da_size(array);

    if (da_size(array) == da_capacity(array)) {
        size_t new_capacity = da_capacity(array) == 0
                            ? 1
                            : da_capacity(array) * DA_GROWTH_FACTOR;

        if (da_resize(array, new_capacity) == -1) return -1;
    }

    memmove(&array->data[index + 1], &array->data[index], (da_size(array) - index) * sizeof(da_element_t));

    array->data[index] = element;
    array->size++;

    return 0;
}

int da_remove_at(dynamic_array *array, size_t index) {
    if (!array || index >= da_size(array)) return -1;

    memmove(&array->data[index], &array->data[index + 1], (da_size(array) - index - 1) * sizeof(da_element_t));

    array->size--;

    return 0;
}

int da_shrink(dynamic_array *array) {
    if (!array) return -1;

    if (da_size(array) == da_capacity(array)) return 0;
    return da_resize(array, da_size(array));
}

int da_find(dynamic_array *array, da_element_t element, size_t *result) {
    if (!array || !result) return -1;

    for (size_t i = 0; i < da_size(array); i++) {
        if (array->data[i] == element) {
            *result = i;
            return 0;
        }
    }

    return -1;
}

int da_clear(dynamic_array *array) {
    if (!array) return -1;

    array->size = 0;

    return 0;
}

int da_reverse(dynamic_array *array) {
    if (!array) return -1;
    if (da_size(array) < 2) return 0;

    size_t i = 0, j = da_size(array) - 1;

    while (i < j) {
        da_element_t temp = array->data[i];
        array->data[i] = array->data[j];
        array->data[j] = temp;
        i++;
        j--;
    }

    return 0;
}

dynamic_array *da_copy(dynamic_array *array) {
    if (!array) return NULL;

    dynamic_array *new_array = da_create(da_capacity(array));
    if (!new_array) return NULL;

    if (da_size(array) > 0) memcpy(new_array->data, array->data, da_size(array) * sizeof(da_element_t));

    new_array->size = da_size(array);

    return new_array;
}

int da_swap(dynamic_array *first_array, dynamic_array *second_array) {
    if (!first_array || !second_array) return -1;

    dynamic_array temp = *first_array;
    *first_array = *second_array;
    *second_array = temp;

    return 0;
}