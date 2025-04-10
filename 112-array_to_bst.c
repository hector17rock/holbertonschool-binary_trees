#include "binary_trees.h"

/**
 * array_to_bst - Builds a BST from an array
 * @array: Pointer to the array of integers
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the BST, or NULL on failure
 */
bst_t *array_to_bst(int *array, size_t size)
{
	bst_t *root = NULL;
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	for (i = 0; i < size; i++)
		bst_insert(&root, array[i]);

	return (root);
}

