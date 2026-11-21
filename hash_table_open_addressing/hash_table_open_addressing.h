#ifndef HASH_TABLE_OPEN_ADDRESSING_H
#define HASH_TABLE_OPEN_ADDRESSING_H

#include <stddef.h>

#define HTO_MAX_LOAD_FACTOR 0.7 // Load factor above which the table grows and rehashes.

typedef int hto_value_t;

typedef enum {
    HTO_EMPTY,      // Slot never used.
    HTO_OCCUPIED,   // Slot holds a live entry.
    HTO_TOMBSTONE   // Slot held an entry that was removed. Keeps probe chains intact.
} hto_state;

typedef struct {
    char *key;          // Owned copy of the key, or NULL if the slot is not occupied.
    hto_value_t value;  // Value mapped to the key.
    hto_state state;    // State of the slot.
} hto_entry;

typedef struct {
    hto_entry *entries; // Array of slots.
    size_t capacity;    // Total number of slots.
    size_t count;       // Number of occupied slots.
    size_t tombstones;  // Number of tombstone slots.
} hash_table_open;

/*
 * Allocates and initializes an empty hash table on the heap.
 * @param initial_capacity Initial number of slots. Must be greater than 0.
 * @return Pointer to the newly created table, or NULL on failure.
 */
hash_table_open *hto_create(size_t initial_capacity);

/*
 * Frees every stored key, the slot array, and the table structure.
 * Sets the caller's pointer to NULL after destruction.
 * @param table Pointer to the table pointer.
 */
void hto_destroy(hash_table_open **table);

/*
 * Computes a hash code for a string using the djb2 algorithm.
 * @param key Null-terminated string.
 * @return Hash code, or 0 if the key is NULL.
 */
size_t hto_hash(const char *key);

/*
 * Computes the slot index to try on a given probe attempt.
 * @param hash Hash code of the key.
 * @param attempt Probe attempt number, starting at 0.
 * @param capacity Total number of slots.
 * @return Slot index in the range [0, capacity), or 0 if capacity is 0.
 */
size_t hto_probe_index(size_t hash, size_t attempt, size_t capacity);

/*
 * Inserts a key-value pair. Overwrites the value if the key already exists.
 * Triggers a rehash when the load factor limit is exceeded.
 * @param table Pointer to the table.
 * @param key Null-terminated key. It is copied.
 * @param value Value to store.
 * @return 0 on success, -1 on failure.
 */
int hto_insert(hash_table_open *table, const char *key, hto_value_t value);

/*
 * Retrieves the value mapped to a key.
 * @param table Pointer to the table.
 * @param key Null-terminated key.
 * @param result Pointer where the value will be stored.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int hto_get(hash_table_open *table, const char *key, hto_value_t *result);

/*
 * Removes a key by marking its slot with a tombstone.
 * @param table Pointer to the table.
 * @param key Null-terminated key.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int hto_remove(hash_table_open *table, const char *key);

/*
 * Reallocates the slot array to a new capacity and reinserts every live entry.
 * Tombstones are discarded.
 * @param table Pointer to the table.
 * @param new_capacity New number of slots. Must hold all current entries.
 * @return 0 on success, -1 on failure.
 */
int hto_resize_rehash(hash_table_open *table, size_t new_capacity);

/*
 * Computes the ratio of occupied slots to total slots.
 * @param table Pointer to the table.
 * @return Load factor, or 0.0 if the table is NULL or has no slots.
 */
double hto_load_factor(hash_table_open *table);

#endif // HASH_TABLE_OPEN_ADDRESSING_H
