#include "binary_trees.h"

/**
 * binary_tree_nodes - Counts the nodes with at least 1 child
 * @tree: Pointer to the root node of the tree
 *
 * Return: Number of non-leaf (internal) nodes. If tree is NULL, return 0.
 */
size_t binary_tree_nodes(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	if (tree->left != NULL || tree->right != NULL)
		return (1 + binary_tree_nodes(tree->left) + binary_tree_nodes(tree->right));

	return (0);
}

