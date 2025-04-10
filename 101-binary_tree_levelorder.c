#include "binary_trees.h"
#include <stdlib.h>

/**
 * queue_push - Pushes a node to the end of the queue
 * @queue: The queue array
 * @size: Pointer to the size of the queue
 * @node: The node to enqueue
 */
void queue_push(binary_tree_t **queue, size_t *size, binary_tree_t *node)
{
	queue[*size] = node;
	(*size)++;
}

/**
 * binary_tree_levelorder - Goes through a binary tree using
 * level-order traversal
 * @tree: Pointer to the root node
 * @func: Function to call for each node's value
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	binary_tree_t *queue[1024];
	size_t front = 0, rear = 0;

	if (tree == NULL || func == NULL)
		return;

	queue[rear++] = (binary_tree_t *)tree;

	while (front < rear)
	{
		const binary_tree_t *current = queue[front++];

		func(current->n);

		if (current->left != NULL)
			queue_push(queue, &rear, current->left);
		if (current->right != NULL)
			queue_push(queue, &rear, current->right);
	}
}

