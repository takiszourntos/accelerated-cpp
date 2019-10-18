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
 * compare function needed for qsort() in the stdlib, based on integer comparisons
 */
int comp_int(const void* a, const void *b)
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
 */
size_t find_sorted_median(key_t *pset, size_t Lset)
{
	size_t i_median=-1;

	if (Lset != 0 )
	{
		//i_median = Lset/2-1;
		i_median = Lset/2; /* seems to create trees with one fewer levels */
	}

	return i_median; /* set must contain at least two elements */
}

/*
 * function dynamically allocates an array of size given by
 * (iright-ileft)+1, made from another array pointed to by pset
 */
key_t *form_set(const key_t *pset, size_t ileft, size_t iright)
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
 * function creates a "blank" node for the binary tree, loaded with NULL pointers and un-initialized key
 *
 * user must integrate this new node into the tree and provide an appropriate key value
 */
bt_t* createNode(void)
{
	bt_t *pn;
	pn = malloc(sizeof(bt_t)); /* create the node in memory, providing a pointer to it */

	pn->pMama = NULL;
	pn->pL = NULL;
	pn->pR = NULL;

	return pn;
}

/*
 * function adds a node with parameter val as key data to the appropriate location on the existing tree (pointed to by pHead)
 *
 * if a tree does not yet exist, the created node becomes the root node
 *
 * returns a pointer to the modified (or newly created) binary search tree
 */
bt_t* addNode(bt_t *pHead, key_t val)
{
	bt_t	*pW = pHead; /* our working pointer, initialized to head pointer */
	bt_t	*pNode = createNode(); /* create the node to add */
	pNode->key = val; /* set key of new node to be added to tree */

	if (pHead==NULL)
	{
		pHead = pNode; /* if no structure yet exists, new node is root  */
		printf("BT: HEAD adding %d ...\n",pHead->key);
	}
	else
	{
		bool_t wentleft;
		bt_t *pParent; /* storage for pointer to parent node */
		key_t valW; /* key value of working pointer */
		while (pW != NULL)
		{
			pParent = pW; /* save this before pW moves on */
			valW = pW->key;
			if (val < valW)
			{
				printf("BT: moving LEFT ... parent key is %d\n", valW);
				pW=pW->pL;
				wentleft=TRUE;
			}
			else if (val > valW)
			{
				printf("BT: moving RIGHT ... parent key is %d\n", valW);
				pW=pW->pR;
				wentleft=FALSE;
			}
			else /* identical keys are not allowed! */
			{
				exit(EXIT_FAILURE);
			}
		}
		//pW = pNode; /* attach node */
		if (wentleft)
		{
			pParent->pL = pNode; /* set the node's left pointer */
		}
		else /* must have gone right */
		{
			pParent->pR = pNode; /* set the node's right pointer */
		}
		pNode->pMama = pParent;
		printf("BT: just attached pNode with value %d\n",val);
	}

	return pHead;
}

/*
 * function creates a binary tree by scanning set S in order, placing successive elements into the tree via addNode()
 */
bt_t* createBT(bt_t* pHead, key_t* pS, size_t NS)
{

	pHead = addNode(pHead, pS[0]);
	for (size_t i = 1; i != NS; ++i)
	{
		//printf("element i=%lu of S, adding %d ...\n", i, pS[i]);
		addNode(pHead, pS[i]);
	}

	return pHead;
}


/*
 * function erects a balanced binary tree from the set provided by the sorted set, S (pS[])
 *
 * PLEASE NOTE: pS[] must be a sorted array for balanced construction!
 *
 * returns a pointer to root node of the resulting binary search tree
 */
bt_t* createBalBT(key_t* pS, size_t NS, bt_t* pParent)
{
	bt_t* pHead=NULL; /* the pointer to the BT that is returned */

	if (NS==0) /* no elements in the set S, pointed to by pS */
	{
		return pHead;
	}
	else if (NS == 1) /* just one element in the set S */
	{
		bt_t* pNode = createNode();
		pNode -> key = pS[0];
		pNode -> pMama = pParent;
		pHead = pNode;
		printf("cBBT: created a single node with key %d\n", pS[0]);
		return pHead;
	}
	else /* at least two elements in the set S */
	{
		key_t iM = find_sorted_median(pS, NS);
		key_t* pSleft = form_set(pS, 0, iM-1);
		size_t NSleft = iM;
		key_t* pSright = form_set(pS, iM+1, NS-1);
		size_t NSright = NS-iM-1;
		bt_t* pNode = createNode();
		pNode->key = pS[iM];
		pNode -> pMama = pParent;
		pHead = pNode;
		printf("cBBT: created a parent node with key %d\n", pS[iM]);
		printf("cBBT: going left...  (parent key is %d)\n", pS[iM]);
		pNode->pL = createBalBT(pSleft, NSleft, pHead);
		printf("cBBT: going right... (parent key is %d)\n", pS[iM]);
		pNode->pR = createBalBT(pSright, NSright, pHead);
	}

	return pHead;
}

/*
 * function performs an in-order tree traversal, identifying key values in order
 */
void inOrderTraversal(bt_t *pT)
{
	if (pT != NULL)
	{
		inOrderTraversal(pT->pL);
		printf("%d ", pT->key);
		inOrderTraversal(pT->pR);
	}

	return;
}




















