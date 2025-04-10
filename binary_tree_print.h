#ifndef BINARY_TREE_PRINT_H
#define BINARY_TREE_PRINT_H

#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 1000
#define INFINITY (1 << 20)

/* Using asciinode type defined in binary_trees.h */

/* Using ascii_tree_info_t type defined in binary_trees.h */

/* Utility functions in binary_tree_print_utils.c */
int _min(int a, int b);
int _max(int a, int b);
asciinode *build_ascii_tree_recursive(const binary_tree_t *t);
void free_ascii_tree(asciinode *node);

/* Compute functions in binary_tree_print_compute.c */
void compute_lprofile(asciinode *node, int x, int y, ascii_tree_info_t *info);
void compute_rprofile(asciinode *node, int x, int y, ascii_tree_info_t *info);
void compute_edge_lengths(asciinode *node, ascii_tree_info_t *info);

/* Main print functions in binary_tree_print.c */
void print_level(asciinode *node, int x, int level, ascii_tree_info_t *info);
void binary_tree_print(const binary_tree_t *tree);

#endif /* BINARY_TREE_PRINT_H */

