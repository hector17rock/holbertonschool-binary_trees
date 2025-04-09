#ifndef BINARY_TREES_H
#define BINARY_TREES_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ========== My existing binary tree struct ========== */

struct binary_tree_s
{
  int n;
  struct binary_tree_s *parent;
  struct binary_tree_s *left;
  struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;

/* ========== Add asciinode here ========== */

/**
 * struct asciinode_struct - ASCII tree printing node
 * @left: Pointer to left child
 * @right: Pointer to right child
 * @edge_length: Length of edge to children
 * @height: Height of subtree
 * @lablen: Length of label
 * @parent_dir: -1=left, 0=root, 1=right
 * @label: Node label
 */
typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
  asciinode *left;
  asciinode *right;
  int edge_length;
  int height;
  int lablen;
  int parent_dir;
  char label[11];
};

/**
 * struct ascii_tree_info - Structure to hold state variables
 * @lprofile: Left profile array
 * @rprofile: Right profile array
 * @gap: Gap between elements
 * @print_next: Print position tracker
 */
typedef struct ascii_tree_info
{
	int lprofile[1000];
	int rprofile[1000];
	int gap;
	int print_next;
} ascii_tree_info_t;

/* ========== My Function Prototypes ========== */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value);
void binary_tree_print(const binary_tree_t *tree);
binary_tree_t *binary_tree_insert_left(binary_tree_t *parent, int value);
binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value);
void binary_tree_delete(binary_tree_t *tree);

#endif /* BINARY_TREES_H */

