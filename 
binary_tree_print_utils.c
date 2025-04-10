#include "binary_tree_print.h"

/**
 * _min - Returns the minimum of two integers
 * @a: First integer
 * @b: Second integer
 *
 * Return: The smaller of the two integers
 */
int _min(int a, int b)
{
	return ((a < b) ? a : b);
}

/**
 * _max - Returns the maximum of two integers
 * @a: First integer
 * @b: Second integer
 *
 * Return: The larger of the two integers
 */
int _max(int a, int b)
{
	return ((a > b) ? a : b);
}

/**
 * build_ascii_tree_recursive - Recursively builds an ASCII tree
 * @t: Pointer to the binary tree node
 *
 * Return: Pointer to the created ASCII tree node
 */
asciinode *build_ascii_tree_recursive(const binary_tree_t *t)
{
	asciinode *node;

	if (t == NULL)
		return (NULL);

	node = malloc(sizeof(asciinode));
	if (node == NULL)
		return (NULL);

	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);

	if (node->left != NULL)
		node->left->parent_dir = -1;
	if (node->right != NULL)
		node->right->parent_dir = 1;

	sprintf(node->label, "%03d", t->n);
	node->lablen = strlen(node->label);

	return (node);
}

/**
 * free_ascii_tree - Frees the memory allocated for the ASCII tree
 * @node: Pointer to the ASCII tree node
 */
void free_ascii_tree(asciinode *node)
{
	if (node == NULL)
		return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

