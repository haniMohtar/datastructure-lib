#ifndef BST_H
#define BST_H

#include <stddef.h>

typedef int bst_element_t;

typedef struct bst_node {
    bst_element_t key;          // Value stored in the node.
    struct bst_node *left;      // Subtree of smaller keys.
    struct bst_node *right;     // Subtree of larger keys.
} bst_node;

/*
 * Allocates a leaf node on the heap with both children set to NULL.
 * @param key Value to store.
 * @return Pointer to the new node, or NULL on failure.
 */
bst_node *bst_create_node(bst_element_t key);

/*
 * Frees every node of the tree using a post-order traversal.
 * Sets the caller's root pointer to NULL after destruction.
 * @param root Pointer to the root pointer.
 */
void bst_destroy_tree(bst_node **root);

/*
 * Inserts a key at the correct leaf position. Duplicate keys are rejected.
 * @param root Pointer to the root pointer. Updated if the tree was empty.
 * @param key Value to insert.
 * @return 0 on success, -1 on failure or if the key already exists.
 */
int bst_insert(bst_node **root, bst_element_t key);

/*
 * Searches the tree for a key.
 * @param root Root of the tree.
 * @param key Value to search for.
 * @param result Pointer where the found node will be stored.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int bst_search(bst_node *root, bst_element_t key, bst_node **result);

/*
 * Retrieves the smallest key in the tree.
 * @param root Root of the tree.
 * @param result Pointer where the key will be stored.
 * @return 0 on success, -1 on failure or if the tree is empty.
 */
int bst_find_min(bst_node *root, bst_element_t *result);

/*
 * Retrieves the largest key in the tree.
 * @param root Root of the tree.
 * @param result Pointer where the key will be stored.
 * @return 0 on success, -1 on failure or if the tree is empty.
 */
int bst_find_max(bst_node *root, bst_element_t *result);

/*
 * Returns the height of the tree, counted in nodes along the longest root-to-leaf path.
 * @param root Root of the tree.
 * @return Height, or 0 if the tree is empty.
 */
size_t bst_height(bst_node *root);

/*
 * Visits every key in sorted order (left, root, right).
 * @param root Root of the tree.
 * @param visit Function called once per key.
 * @return 0 on success, -1 on failure.
 */
int bst_traverse_inorder(bst_node *root, void (*visit)(bst_element_t key));

/*
 * Visits every key in root-left-right order.
 * @param root Root of the tree.
 * @param visit Function called once per key.
 * @return 0 on success, -1 on failure.
 */
int bst_traverse_preorder(bst_node *root, void (*visit)(bst_element_t key));

/*
 * Visits every key in left-right-root order.
 * @param root Root of the tree.
 * @param visit Function called once per key.
 * @return 0 on success, -1 on failure.
 */
int bst_traverse_postorder(bst_node *root, void (*visit)(bst_element_t key));

/*
 * Deletes a key, handling leaf, one-child, and two-child cases.
 * @param root Pointer to the root pointer. Updated if the root is removed.
 * @param key Value to delete.
 * @return 0 on success, -1 if the key is not found or an error occurs.
 */
int bst_delete_node(bst_node **root, bst_element_t key);

/*
 * Finds the node with the smallest key larger than the given node's key.
 * @param root Root of the tree.
 * @param node Node whose successor is wanted. Must belong to the tree.
 * @param result Pointer where the successor node will be stored.
 * @return 0 on success, -1 if there is no successor or an error occurs.
 */
int bst_find_successor(bst_node *root, bst_node *node, bst_node **result);

/*
 * Finds the node with the largest key smaller than the given node's key.
 * @param root Root of the tree.
 * @param node Node whose predecessor is wanted. Must belong to the tree.
 * @param result Pointer where the predecessor node will be stored.
 * @return 0 on success, -1 if there is no predecessor or an error occurs.
 */
int bst_find_predecessor(bst_node *root, bst_node *node, bst_node **result);

/*
 * Checks that every node respects the binary search tree ordering.
 * @param root Root of the tree.
 * @return 1 if the tree is a valid BST (an empty tree is valid), 0 otherwise.
 */
int bst_is_valid(bst_node *root);

#endif // BST_H
