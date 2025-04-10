#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_is_complete - Checks if a binary tree is complete
 * @tree: Pointer to the root node
 *
 * Return: 1 if complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	const binary_tree_t *queue[1024];
	size_t front = 0, rear = 0;
	int found_null = 0;

	if (tree == NULL)
		return (0);

	queue[rear++] = tree;

	while (front < rear)
	{
		const binary_tree_t *current = queue[front++];

		if (current == NULL)
		{
			found_null = 1;
		}
		else
		{
			if (found_null)
				return (0);

			queue[rear++] = current->left;
			queue[rear++] = current->right;
		}
	}

	return (1);
}

