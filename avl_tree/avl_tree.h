#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stddef.h>

typedef int avl_element_t;

typedef struct avl_node {
    avl_element_t key;          // Value stored in the node.
    int height;                 // Height of the subtree rooted here. A leaf has height 1.
    struct avl_node *left;      // Subtree of smaller keys.
    struct avl_node *right;     // Subtree of larger keys.
} avl_node;

/*
 * Allocates a leaf node on the heap with height 1 and both children set to NULL.
 * @param key Value to store.
 * @return Pointer to the new node, or NULL on failure.
 */
avl_node *avl_create_node(avl_element_t key);

/*
 * Frees every node of the tree.
 * Sets the caller's root pointer to NULL after destruction.
 * @param root Pointer to the root pointer.
 */
void avl_destroy_tree(avl_node **root);

/*
 * Returns the height of a node.
 * @param node Pointer to the node.
 * @return Height, or 0 if the node is NULL.
 */
int avl_get_height(avl_node *node);

/*
 * Computes the height of the left subtree minus the height of the right subtree.
 * @param node Pointer to the node.
 * @return Balance factor, or 0 if the node is NULL.
 */
int avl_get_balance_factor(avl_node *node);

/*
 * Rotates the subtree left to fix a right-heavy imbalance.
 * @param node Root of the subtree. Its right child must not be NULL.
 * @return New root of the subtree, or NULL on failure.
 */
avl_node *avl_rotate_left(avl_node *node);

/*
 * Rotates the subtree right to fix a left-heavy imbalance.
 * @param node Root of the subtree. Its left child must not be NULL.
 * @return New root of the subtree, or NULL on failure.
 */
avl_node *avl_rotate_right(avl_node *node);

/*
 * Inserts a key, updates heights, and rebalances with rotations as needed.
 * Duplicate keys are rejected.
 * @param root Pointer to the root pointer. Updated if the root changes.
 * @param key Value to insert.
 * @return 0 on success, -1 on failure or if the key already exists.
 */
int avl_insert(avl_node **root, avl_element_t key);

/*
 * Deletes a key and rebalances every ancestor on the way back to the root.
 * @param root Pointer to the root pointer. Updated if the root changes.
 * @param key Value to delete.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int avl_delete_node(avl_node **root, avl_element_t key);

/*
 * Visits every key in sorted order (left, root, right).
 * @param root Root of the tree.
 * @param visit Function called once per key.
 * @return 0 on success, -1 on failure.
 */
int avl_traverse_inorder(avl_node *root, void (*visit)(avl_element_t key));

#endif // AVL_TREE_H
