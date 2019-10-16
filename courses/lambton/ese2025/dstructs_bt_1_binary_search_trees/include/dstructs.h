/*
 * dstructs.h
 *
 *  Created on: Oct. 16, 2019
 *      Author: takis
 */

#ifndef INCLUDE_DSTRUCTS_H_
#define INCLUDE_DSTRUCTS_H_

typedef int	key_t;

typedef struct bt_struct
{
	key_t	key;	/* node key value */
	bt_t	*pMama;	/* pointer to node's parent */
	bt_t	*pL;	/* pointer to node's left child */
	bt_t	*pR;	/* pointer to node's right (but sometimes wrong) child */
} bt_t;


/*
 * compare function needed for qsort() in the stdlib
 */
int comp(const void*, const void *);

/*
 * median finder presumes set is sorted
 *
 * if the set contains an even number of elements, function
 * returns index to element just to left of median
 *
 * returns -1 if set is empty or contains only 1 element
 *
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
 * function creates a node for the binary tree, loaded with NULL pointers and un-initialized key
 *
 * user must integrate this new node into the tree and provide an appropriate key value
 *
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



#endif /* INCLUDE_DSTRUCTS_H_ */
