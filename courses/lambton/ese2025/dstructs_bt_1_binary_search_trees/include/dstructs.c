/*
 * dstructs.c : useful bits for our work on data structures
 *
 *  Created on: Oct. 16, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include "dstructs.h"


/*
 * compare function needed for qsort() in the stdlib
 */
int comp(const void* a, const void *b)
{
	int ia=*((int *) a);
	int ib=*((int *) b);

	if (ia<ib)
		return -1;
	else if (ia>ib)
		return +1;

	return 0; /* default return if ia==ib */
}

/*
 * median finder presumes set is sorted
 *
 * if the set contains an even number of elements, function
 * returns index to element just to left of median
 *
 * returns -1 if set is empty or contains only 1 element
 *
 */
size_t find_sorted_median(key_t *pset, size_t Lset)
{
	size_t i_median=-1;

	if (Lset != 0 )
	{
		i_median = Lset/2-1;
	}

	return i_median; /* set must contain at least two elements */
}

/*
 * function dynamically allocates an array of size given by
 * (iright-ileft)+1, made from another array pointed to by pset
 */
key_t	*form_set(const key_t *pset, size_t ileft, size_t iright)
{
	key_t *pnew = (key_t *) malloc((iright-ileft+1)*sizeof(key_t));

	for (size_t i=ileft; i != (iright+1); ++i)
	{
		pnew[i-ileft] = pset[i];
	}

	return pnew;
}

/*
 * function prints out an array on one line,
 * caller must provide the size of the set (Lset)
 */
void printset(key_t *pset, size_t Lset)
{

	for (size_t i=0; i != Lset; ++i)
	{
		printf("%d ",pset[i]);
	}
	printf("\n");

	return;
}

/*
 * function creates a node for the binary tree, loaded with NULL pointers and un-initialized key
 *
 * user must integrate this new node into the tree and provide an appropriate key value
 *
 */
bt_t* createnode(void)
{
	bt_t	pn = (bt_t *) malloc(sizeof(bt_t)); /* create the node in memory, providing a pointer to it */

	pn->pMama = NULL;
	pn->pL = NULL;
	pn->pR = NULL;

	return pn;
}

bt_t* addnode(bt_t *pHead, key_t val)
{
	bt_t	*pW = pHead; /* our working pointer, initialized to head pointer */
	bt_t	*pnode = createnode(); /* create the node to add */
	pnode->key = val;

	if (pHead==NULL)

	return pHead;
}


