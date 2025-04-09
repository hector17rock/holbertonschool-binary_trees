#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 1000
#define INFINITY (1 << 20)
/**
 * _min - Returns the minimum of two integers
 * @a: First integer
 * @b: Second integer
 *
 * Return: The smaller of the two integers
 */
static int _min(int a, int b)
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
static int _max(int a, int b)
{
	return ((a > b) ? a : b);
}
/**
 * build_ascii_tree_recursive - Recursively builds an ASCII tree
 * @t: Pointer to the binary tree node
 *
 * Return: Pointer to the created ASCII tree node
 */
static asciinode *build_ascii_tree_recursive(const binary_tree_t *t)
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
static void free_ascii_tree(asciinode *node)
{
	if (node == NULL)
		return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

/**
 * compute_lprofile - Computes the left profile of the ASCII tree
 * @node: Pointer to the ASCII tree node
 * @x: X coordinate
 * @y: Y coordinate
 * @info: Pointer to the ASCII tree info structure
 */
static void compute_lprofile(asciinode *node, int x, int y,
		ascii_tree_info_t *info)
{
	int i, isleft;

	if (node == NULL)
		return;

	isleft = (node->parent_dir == -1);
	info->lprofile[y] = _min(info->lprofile[y],
			x - ((node->lablen - isleft) / 2));

	if (node->left != NULL)
	{
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
			info->lprofile[y + i] = _min(info->lprofile[y + i], x - i);
	}

	compute_lprofile(node->left,
			x - node->edge_length - 1,
			y + node->edge_length + 1,
			info);
	compute_lprofile(node->right,
			x + node->edge_length + 1,
			y + node->edge_length + 1,
			info);
}

/**
 * compute_rprofile - Computes the right profile of the ASCII tree
 * @node: Pointer to the ASCII tree node
 * @x: X coordinate
 * @y: Y coordinate
 * @info: Pointer to the ASCII tree info structure
 */
static void compute_rprofile(asciinode *node, int x, int y,
		ascii_tree_info_t *info)
{
	int i, notleft;

	if (node == NULL)
		return;

	notleft = (node->parent_dir != -1);
	info->rprofile[y] = _max(info->rprofile[y],
			x + ((node->lablen - notleft) / 2));

	if (node->right != NULL)
	{
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
			info->rprofile[y + i] = _max(info->rprofile[y + i], x + i);
	}

	compute_rprofile(node->left,
			x - node->edge_length - 1,
			y + node->edge_length + 1,
			info);
	compute_rprofile(node->right,
			x + node->edge_length + 1,
			y + node->edge_length + 1,
			info);
}

/**
 * compute_edge_lengths - Computes the edge lengths for the ASCII tree
 * @node: Pointer to the ASCII tree node
 * @info: Pointer to the ASCII tree info structure
 */
static void compute_edge_lengths(asciinode *node, ascii_tree_info_t *info)
{
	int i, hmin, delta;

	if (node == NULL)
		return;

	compute_edge_lengths(node->left, info);
	compute_edge_lengths(node->right, info);

	if (node->left == NULL && node->right == NULL)
	{
		node->edge_length = 0;
	}
	else
	{
		if (node->left != NULL)
		{
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
				info->rprofile[i] = -INFINITY;
			compute_rprofile(node->left, 0, 0, info);
			hmin = node->left->height;
		}
		else
		{
			hmin = 0;
		}

		if (node->right != NULL)
		{
			for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
				info->lprofile[i] = INFINITY;
			compute_lprofile(node->right, 0, 0, info);
			hmin = _min(node->right->height, hmin);
		}
		else
		{
			hmin = 0;
		}

		delta = 4;
		for (i = 0; i < hmin; i++)
		{
			delta = _max(delta,
					info->gap + 1 + info->rprofile[i] - info->lprofile[i]);
		}

		if (((node->left != NULL && node->left->height == 1) ||
					(node->right != NULL && node->right->height == 1)) &&
				delta > 4)
			delta--;

		node->edge_length = ((delta + 1) / 2) - 1;
	}

	node->height = 1;
	if (node->left != NULL)
		node->height = _max(node->height,
				node->left->height + node->edge_length + 1);
	if (node->right != NULL)
		node->height = _max(node->height,
				node->right->height + node->edge_length + 1);
}

/**
 * print_level - Prints a level of the ASCII tree
 * @node: Pointer to the ASCII tree node
 * @x: X coordinate
 * @level: Level to print
 * @info: Pointer to the ASCII tree info structure
 */
static void print_level(asciinode *node, int x, int level,
		ascii_tree_info_t *info)
{
	int i, isleft;

	if (node == NULL)
		return;

	isleft = (node->parent_dir == -1);
	if (level == 0)
	{
		for (i = 0;
				i < (x - info->print_next - ((node->lablen - isleft) / 2));
				i++)
			printf(" ");
		info->print_next += i;
		printf("%s", node->label);
		info->print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->left != NULL)
		{
			for (i = 0; i < (x - info->print_next - level); i++)
				printf(" ");
			info->print_next += i;
			printf("/");
			info->print_next++;
		}

		if (node->right != NULL)
		{
			for (i = 0; i < (x - info->print_next + level); i++)
				printf(" ");
			info->print_next += i;
			printf("\\");
			info->print_next++;
		}
	}
	else
	{
		print_level(node->left,
				x - node->edge_length - 1,
				level - node->edge_length - 1,
				info);
		print_level(node->right,
				x + node->edge_length + 1,
				level - node->edge_length - 1,
				info);
	}
}

/**
 * binary_tree_print - Prints a binary tree in ASCII
 * @tree: Pointer to the root node of the tree
 */
void binary_tree_print(const binary_tree_t *tree)
{
	asciinode *proot;
	int i, xmin;
	ascii_tree_info_t info;

	if (tree == NULL)
		return;
	/* Initialize the info structure */
	info.gap = 3;
	proot = build_ascii_tree_recursive(tree);
	compute_edge_lengths(proot, &info);

	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		info.lprofile[i] = INFINITY;

	compute_lprofile(proot, 0, 0, &info);
	xmin = 0;

	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		xmin = _min(xmin, info.lprofile[i]);

	for (i = 0; i < proot->height; i++)
	{
		info.print_next = 0;
		print_level(proot, -xmin, i, &info);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT)
	{
		printf("(Tree is taller than %d, may not print properly)\n",
				MAX_HEIGHT);
	}

	free_ascii_tree(proot);
}

