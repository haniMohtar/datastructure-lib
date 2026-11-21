#include <stdio.h>
#include <stddef.h>

#include "dynamic_array.h"

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(cond) do { \
    tests_run++; \
    if (!(cond)) { \
        tests_failed++; \
        printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
    } \
} while (0)

static dynamic_array *make(const da_element_t *values, size_t n) {
    dynamic_array *array = da_create(n);
    for (size_t i = 0; i < n; i++) da_push_back(array, values[i]);
    return array;
}

static int equals(dynamic_array *array, const da_element_t *expected, size_t n) {
    if (da_size(array) != n) return 0;

    for (size_t i = 0; i < n; i++) {
        da_element_t value;
        if (da_get(array, i, &value) != 0 || value != expected[i]) return 0;
    }

    return 1;
}

static void test_create_destroy(void) {
    dynamic_array *a = da_create(4);
    CHECK(a != NULL);
    CHECK(da_size(a) == 0);
    CHECK(da_capacity(a) == 4);

    da_destroy(&a);
    CHECK(a == NULL);
    da_destroy(&a);
    da_destroy(NULL);

    dynamic_array *z = da_create(0);
    CHECK(z != NULL);
    CHECK(da_capacity(z) == 0);
    da_destroy(&z);

    CHECK(da_size(NULL) == 0);
    CHECK(da_capacity(NULL) == 0);
}

static void test_push_back(void) {
    dynamic_array *a = da_create(0);

    CHECK(da_push_back(a, 1) == 0);
    CHECK(da_capacity(a) == 1);
    CHECK(da_push_back(a, 2) == 0);
    CHECK(da_capacity(a) == 2);
    CHECK(da_push_back(a, 3) == 0);
    CHECK(da_capacity(a) == 4);
    CHECK(da_push_back(a, 4) == 0);
    CHECK(da_capacity(a) == 4);
    CHECK(da_push_back(a, 5) == 0);
    CHECK(da_capacity(a) == 8);

    da_element_t expected[] = {1, 2, 3, 4, 5};
    CHECK(equals(a, expected, 5));
    CHECK(da_push_back(NULL, 1) == -1);

    dynamic_array *big = da_create(0);
    for (int i = 0; i < 1000; i++) da_push_back(big, i);
    CHECK(da_size(big) == 1000);

    int ok = 1;
    for (size_t i = 0; i < 1000; i++) {
        da_element_t value;
        if (da_get(big, i, &value) != 0 || value != (da_element_t)i) ok = 0;
    }
    CHECK(ok);

    da_destroy(&a);
    da_destroy(&big);
}

static void test_get_set(void) {
    da_element_t values[] = {10, 20, 30};
    dynamic_array *a = make(values, 3);
    da_element_t out = 0;

    CHECK(da_get(a, 1, &out) == 0);
    CHECK(out == 20);
    CHECK(da_get(a, 3, &out) == -1);
    CHECK(da_get(a, 0, NULL) == -1);
    CHECK(da_get(NULL, 0, &out) == -1);

    CHECK(da_set(a, 0, 99) == 0);
    CHECK(da_get(a, 0, &out) == 0);
    CHECK(out == 99);
    CHECK(da_set(a, 3, 1) == -1);
    CHECK(da_set(NULL, 0, 1) == -1);

    da_destroy(&a);
}

static void test_pop_back(void) {
    da_element_t values[] = {1, 2, 3};
    dynamic_array *a = make(values, 3);
    da_element_t out = 0;

    CHECK(da_pop_back(a, &out) == 0);
    CHECK(out == 3);
    CHECK(da_size(a) == 2);
    CHECK(da_capacity(a) == 3);

    CHECK(da_pop_back(a, &out) == 0);
    CHECK(out == 2);
    CHECK(da_pop_back(a, &out) == 0);
    CHECK(out == 1);
    CHECK(da_pop_back(a, &out) == -1);
    CHECK(da_pop_back(a, NULL) == -1);
    CHECK(da_pop_back(NULL, &out) == -1);

    da_destroy(&a);
}

static void test_insert_at(void) {
    da_element_t values[] = {1, 2, 3};
    dynamic_array *a = make(values, 3);

    CHECK(da_insert_at(a, 0, 0) == 0);
    da_element_t e1[] = {0, 1, 2, 3};
    CHECK(equals(a, e1, 4));
    CHECK(da_capacity(a) == 6);

    CHECK(da_insert_at(a, 2, 9) == 0);
    da_element_t e2[] = {0, 1, 9, 2, 3};
    CHECK(equals(a, e2, 5));

    CHECK(da_insert_at(a, da_size(a), 7) == 0);
    da_element_t e3[] = {0, 1, 9, 2, 3, 7};
    CHECK(equals(a, e3, 6));

    CHECK(da_insert_at(a, 100, 8) == 0);
    da_element_t e4[] = {0, 1, 9, 2, 3, 7, 8};
    CHECK(equals(a, e4, 7));

    dynamic_array *e = da_create(0);
    CHECK(da_insert_at(e, 0, 5) == 0);
    da_element_t e5[] = {5};
    CHECK(equals(e, e5, 1));
    CHECK(da_capacity(e) == 1);

    CHECK(da_insert_at(NULL, 0, 1) == -1);

    da_destroy(&a);
    da_destroy(&e);
}

static void test_remove_at(void) {
    da_element_t values[] = {1, 2, 3, 4, 5};
    dynamic_array *a = make(values, 5);

    CHECK(da_remove_at(a, 0) == 0);
    da_element_t e1[] = {2, 3, 4, 5};
    CHECK(equals(a, e1, 4));

    CHECK(da_remove_at(a, 1) == 0);
    da_element_t e2[] = {2, 4, 5};
    CHECK(equals(a, e2, 3));

    CHECK(da_remove_at(a, 2) == 0);
    da_element_t e3[] = {2, 4};
    CHECK(equals(a, e3, 2));

    CHECK(da_remove_at(a, 2) == -1);
    CHECK(da_capacity(a) == 5);

    da_clear(a);
    CHECK(da_remove_at(a, 0) == -1);
    CHECK(da_remove_at(NULL, 0) == -1);

    da_destroy(&a);
}

static void test_resize(void) {
    da_element_t values[] = {1, 2, 3};
    dynamic_array *a = make(values, 3);

    CHECK(da_resize(a, 2) == -1);
    CHECK(da_size(a) == 3);
    CHECK(da_capacity(a) == 3);

    CHECK(da_resize(a, 10) == 0);
    CHECK(da_capacity(a) == 10);
    CHECK(equals(a, values, 3));

    CHECK(da_resize(a, 0) == -1);

    da_clear(a);
    CHECK(da_resize(a, 0) == 0);
    CHECK(da_capacity(a) == 0);
    CHECK(a->data == NULL);

    CHECK(da_push_back(a, 4) == 0);
    CHECK(da_capacity(a) == 1);
    CHECK(da_resize(NULL, 1) == -1);

    da_destroy(&a);
}

static void test_shrink(void) {
    da_element_t values[] = {1, 2, 3};
    dynamic_array *a = make(values, 3);

    da_resize(a, 8);
    CHECK(da_shrink(a) == 0);
    CHECK(da_capacity(a) == 3);
    CHECK(equals(a, values, 3));
    CHECK(da_shrink(a) == 0);
    CHECK(da_capacity(a) == 3);

    da_clear(a);
    CHECK(da_shrink(a) == 0);
    CHECK(da_capacity(a) == 0);
    CHECK(da_shrink(NULL) == -1);

    da_destroy(&a);
}

static void test_find(void) {
    da_element_t values[] = {5, 7, 5, 9};
    dynamic_array *a = make(values, 4);
    size_t index = 99;

    CHECK(da_find(a, 5, &index) == 0);
    CHECK(index == 0);
    CHECK(da_find(a, 9, &index) == 0);
    CHECK(index == 3);
    CHECK(da_find(a, 4, &index) == -1);
    CHECK(da_find(a, 5, NULL) == -1);
    CHECK(da_find(NULL, 5, &index) == -1);

    da_clear(a);
    CHECK(da_find(a, 5, &index) == -1);

    da_destroy(&a);
}

static void test_clear(void) {
    da_element_t values[] = {1, 2, 3};
    dynamic_array *a = make(values, 3);

    CHECK(da_clear(a) == 0);
    CHECK(da_size(a) == 0);
    CHECK(da_capacity(a) == 3);

    CHECK(da_push_back(a, 8) == 0);
    da_element_t expected[] = {8};
    CHECK(equals(a, expected, 1));
    CHECK(da_clear(NULL) == -1);

    da_destroy(&a);
}

static void test_reverse(void) {
    da_element_t odd[] = {1, 2, 3, 4, 5};
    dynamic_array *a = make(odd, 5);
    CHECK(da_reverse(a) == 0);
    da_element_t e1[] = {5, 4, 3, 2, 1};
    CHECK(equals(a, e1, 5));
    CHECK(da_capacity(a) == 5);

    da_element_t even[] = {1, 2, 3, 4};
    dynamic_array *b = make(even, 4);
    CHECK(da_reverse(b) == 0);
    da_element_t e2[] = {4, 3, 2, 1};
    CHECK(equals(b, e2, 4));

    da_element_t one[] = {42};
    dynamic_array *c = make(one, 1);
    CHECK(da_reverse(c) == 0);
    CHECK(equals(c, one, 1));

    dynamic_array *d = da_create(0);
    CHECK(da_reverse(d) == 0);
    CHECK(da_size(d) == 0);
    CHECK(da_reverse(NULL) == -1);

    da_destroy(&a);
    da_destroy(&b);
    da_destroy(&c);
    da_destroy(&d);
}

static void test_copy(void) {
    da_element_t values[] = {1, 2, 3};
    dynamic_array *a = make(values, 3);
    dynamic_array *b = da_copy(a);

    CHECK(b != NULL);
    CHECK(equals(b, values, 3));
    CHECK(da_capacity(b) == da_capacity(a));
    CHECK(b->data != a->data);

    da_set(b, 0, 99);
    CHECK(equals(a, values, 3));

    da_push_back(b, 4);
    CHECK(da_size(a) == 3);

    dynamic_array *e = da_create(0);
    dynamic_array *f = da_copy(e);
    CHECK(f != NULL);
    CHECK(da_size(f) == 0);
    CHECK(da_copy(NULL) == NULL);

    da_destroy(&a);
    da_destroy(&b);
    da_destroy(&e);
    da_destroy(&f);
}

static void test_swap(void) {
    da_element_t v1[] = {1, 2, 3};
    da_element_t v2[] = {9};
    dynamic_array *a = make(v1, 3);
    dynamic_array *b = make(v2, 1);

    CHECK(da_swap(a, b) == 0);
    CHECK(equals(a, v2, 1));
    CHECK(equals(b, v1, 3));
    CHECK(da_capacity(a) == 1);
    CHECK(da_capacity(b) == 3);

    CHECK(da_swap(a, a) == 0);
    CHECK(equals(a, v2, 1));

    CHECK(da_swap(a, NULL) == -1);
    CHECK(da_swap(NULL, b) == -1);

    da_destroy(&a);
    da_destroy(&b);
}

int main(void) {
    test_create_destroy();
    test_push_back();
    test_get_set();
    test_pop_back();
    test_insert_at();
    test_remove_at();
    test_resize();
    test_shrink();
    test_find();
    test_clear();
    test_reverse();
    test_copy();
    test_swap();

    printf("%d checks, %d failed\n", tests_run, tests_failed);
    return tests_failed != 0;
}