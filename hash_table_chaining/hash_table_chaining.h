#ifndef HASH_TABLE_CHAINING_H
#define HASH_TABLE_CHAINING_H

#include <stddef.h>

#include "../singly_linked_list/singly_linked_list.h"

typedef int htc_value_t;

typedef struct {
    singly_linked_list **buckets;   // Array of bucket lists. Each list holds the entries that collide there.
    size_t bucket_count;            // Fixed number of buckets.
    size_t count;                   // Current number of stored key-value pairs.
} hash_table_chaining;

/*
 * Allocates and initializes an empty hash table on the heap.
 * @param bucket_count Number of buckets. Must be greater than 0.
 * @return Pointer to the newly created table, or NULL on failure.
 */
hash_table_chaining *htc_create(size_t bucket_count);

/*
 * Frees every bucket list, every stored key, and the table structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param table Pointer to the table pointer.
 */
void htc_destroy(hash_table_chaining **table);

/*
 * Computes a hash code for a string using the djb2 algorithm.
 * @param key Null-terminated string.
 * @return Hash code, or 0 if the key is NULL.
 */
size_t htc_hash(const char *key);

/*
 * Inserts a key-value pair. Overwrites the value if the key already exists.
 * The key string is copied.
 * @param table Pointer to the table.
 * @param key Null-terminated key.
 * @param value Value to store.
 * @return 0 on success, -1 on failure.
 */
int htc_insert(hash_table_chaining *table, const char *key, htc_value_t value);

/*
 * Retrieves the value mapped to a key.
 * @param table Pointer to the table.
 * @param key Null-terminated key.
 * @param result Pointer where the value will be stored.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int htc_get(hash_table_chaining *table, const char *key, htc_value_t *result);

/*
 * Removes a key and its value.
 * @param table Pointer to the table.
 * @param key Null-terminated key.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int htc_remove(hash_table_chaining *table, const char *key);

/*
 * Checks whether a key is present.
 * @param table Pointer to the table.
 * @param key Null-terminated key.
 * @return 1 if the key is present, 0 otherwise (including NULL arguments).
 */
int htc_contains(hash_table_chaining *table, const char *key);

/*
 * Computes the ratio of stored entries to bucket count.
 * @param table Pointer to the table.
 * @return Load factor, or 0.0 if the table is NULL.
 */
double htc_load_factor(hash_table_chaining *table);

/*
 * Prints every bucket and its entries for debugging.
 * @param table Pointer to the table.
 * @return 0 on success, -1 on failure.
 */
int htc_print(hash_table_chaining *table);

#endif // HASH_TABLE_CHAINING_H
