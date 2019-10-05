#ifndef DSTRUCTS_DSTRUCTS_H_
#define DSTRUCTS_DSTRUCTS_H_

/*
 * dstructs.h
 *
 *  Created on: Oct. 3, 2019
 *      Author: takis
 */


#include <stdlib.h>

/*************************************************************
 * NODE STRUCT GOES HERE
 *************************************************************/
struct linkedList
{
	int		data;
	struct 	linkedList *pNext;
};
typedef struct linkedList ll_t;

typedef unsigned short int bool_t;


/************************************************************
 * USEFUL LINKED LIST FUNCTIONS
 ************************************************************/

/*
 * createNode():
 *
 * 		creates a node of type ll_t from the heap, and returns
 * 		a pointer to this newly created node; sets the node's own
 * 	    pNext pointer to NULL
 *
 */
ll_t*	createNode();

/*
 * addNode():
 *
 * 		adds a new node (with node->data = value) to the bottom/back
 * 		of the list referenced by the pointer, head;
 * 		if head==NULL, a new list is created
 *
 */
ll_t* 	addNode(ll_t*, int);

/*
 * find_largest():
 * 		returns a pointer to the largest element in the list;
 * 		returns maximum value as second parameter (passed by reference)
 *
 */
ll_t* 	find_largest(const ll_t*, int *);

/*
 * swap():
 *
 * 		swaps locations of A, B in the linked list; needs the
 * 		pointers to each element to be swapped
 *
 */
ll_t*	swap(ll_t*);

/*
 * bubb_sort():
 * 		performs a Bubble Sort on a list (referenced by head pointer parameter)
 *
 */
ll_t*	bubb_sort(ll_t*, bool_t);


#endif /* DSTRUCTS_DSTRUCTS_H_ */
