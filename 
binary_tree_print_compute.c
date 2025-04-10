#include "binary_tree_print.h"

/**
 * compute_lprofile - Computes the left profile of the ASCII tree
 * @node: Pointer to the ASCII tree node
 * @x: X coordinate
 * @y: Y coordinate
 * @info: Pointer to the ASCII tree info structure
 */
void compute_lprofile(asciinode *node, int x, int y,
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
void compute_rprofile(asciinode *node, int x, int y,
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
void compute_edge_lengths(asciinode *node, ascii_tree_info_t *info)
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

