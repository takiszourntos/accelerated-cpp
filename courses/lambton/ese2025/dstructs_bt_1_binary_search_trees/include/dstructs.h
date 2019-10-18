#ifndef INCLUDE_DSTRUCTS_H_
#define INCLUDE_DSTRUCTS_H_
 /* dstructs.h
 *
 *  Created on: Oct. 16, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>

#define	TRUE	1U
#define FALSE	0U

typedef int	key_t;

struct bst_node
{
	key_t	key;	/* node key value */
	struct bst_node	*pMama;	/* pointer to node's parent */
	struct bst_node	*pL;	/* pointer to node's left child */
	struct bst_node	*pR;	/* pointer to node's right (but sometimes wrong) child */
};
typedef struct bst_node bt_t;

typedef unsigned short int bool_t;

/*
 * compare function needed for qsort() in the stdlib, based on integer comparisons
 */
int comp_int(const void*, const void *);

/*
 * median finder presumes set is sorted
 *
 * if the set contains an even number of elements, function
 * returns index to element just to left of median
 *
 * returns -1 if set is empty or contains only 1 element , otherwise
 * 	        returns the (size_t) array index to the median element
 */
size_t find_sorted_median(key_t*, size_t);

/*
 * function dynamically allocates an array of size given by
 * (iright-ileft)+1, made from another array pointed to by pset
 */
key_t *form_set(const key_t*, size_t , size_t);

/*
 * function prints out an array on one line,
 * caller must provide the size of the set (Lset)
 */
void printset(key_t*, size_t);

/*
 * function creates a "blank" node for the binary tree, loaded with NULL pointers and un-initialized key
 *
 * user must integrate this new node into the tree and provide an appropriate key value
 */

bt_t* createNode(void);

/*
 * function adds a node with parameter val as key data to the appropriate location on the existing tree;
 *
 * if a tree does not yet exist, the created node becomes the root node
 *
 * returns a pointer to the modified (or newly created) binary search tree
 */
bt_t* addNode(bt_t*, key_t);


/*
 * function creates a binary tree by scanning set S in order, placing successive elements into the tree via addNode()
 */
bt_t* createBT(bt_t*, key_t*, size_t);

/*
 * function erects a balanced binary tree from the set provided by the sorted set, S (pS[])
 *
 * PLEASE NOTE: pS[] must be a sorted array for balanced construction!
 *
 * returns a pointer to root node of the resulting binary search tree
 */
bt_t* createBalBT(key_t*, size_t, bt_t*);

/*
 * function performs an in-order tree traversal, identifying key values in order
 */
void inOrderTraversal(bt_t*);


#endif /* INCLUDE_DSTRUCTS_H_ */
