/*
 * dstructs.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takiss
 */

#include <stdlib.h>
#include "dstructs.h"

/*
 * createNode():
 *
 * 		creates a node of type ll_t from the heap, and returns
 * 		a pointer to this newly created node; sets the node's own
 * 	    pNext pointer to NULL
 *
 */
ll_t* createNode()
{
	/* create a pointer for the new node */
    ll_t 	*node;

    /* allocate the node from heap */
    node = 	(ll_t *) malloc(sizeof(ll_t));

    /* make next point to NULL */
    node -> pNext = NULL;//

    /* return the pointer to the new node */
    return 	node;
}

/*
 * addNode():
 *
 * 		adds a new node (with node->data = value) to the bottom/back
 * 		of the list referenced by the pointer, head;
 * 		if head==NULL, a new list is created
 *
 */
ll_t* addNode(ll_t* head, int value)
{
	/* create two node pointers */
    ll_t *node;
	ll_t *p;

	/* prepare the new node to be added */
    node = createNode();
    node -> data = value; /* set the new element's data field to value */

    if (head == NULL)
    {
        head = node;     /* if the linked list has no nodes to begin with */
    }
    else
    {
        /* search through list until tail node is found */
        p  = head;
        while ((p->pNext) != NULL)
        {
            p = p -> pNext;
        }
        /* set the pointer from NULL to temp */
        p -> pNext = node;
    }
    return head;
}

/*
 * find_largest():
 * 		returns a pointer to the largest element in the list;
 * 		returns maximum value as second parameter (passed by reference)
 *
 */
ll_t*  find_largest(const ll_t *head, int *max)
{
		*max = head -> data;
		int nexti;
		ll_t* pw = head -> pNext; /* working pointer, initialized to head's child pointer */
		while ( (pw -> pNext) != NULL )
		{
			nexti = pw -> data;
			if (*max < nexti)
			{
				*max = nexti;
			}
			pw = pw -> pNext; /* advance the pointer */
		}
		return pw;
}

/*
 * swap():
 *
 * 		swaps locations of adjacent elements A, B in the linked list;
 * 		assumes that initially:
 *
 * 		----> A ----> B ----> 1
 *		 p2A     p2B	 p21
 *
 *		and re-arranges pointers so that:
 *
 *		----> B ----> A ----> 1
 *       p0      p2A     p21
 *
 *       returning p0
 *
 */
ll_t* swap(ll_t* p2A)
{
	ll_t	*p0; /* return variable */
	ll_t	*p2B = p2A -> pNext; /* pointer to B */
	ll_t	*p21 = p2B -> pNext; /* what B is pointing to */

	p0 = p2B;			/* p0 -> B */
	p2B -> pNext = p2A;	/* B -> A */
	p2A -> pNext = p21; /* A -> 1 */

	/* done */
	return p0;
}

/*
 * bubb_sort():
 * 		performs a Bubble Sort on a list (referenced by head pointer parameter)
 *
 */
ll_t* bubb_sort(ll_t *head, bool_t dir)
{
	unsigned short int swaps = 1; /* swapping flag for bubble sort algorithm */
	ll_t	*pW1=head; /* working pointer */
	ll_t	*pW2=head->pNext; /* working pointer's "child" */

	while (swaps)
	{
		swaps = 0; // if a swap occurs, this flag is toggled
		while (pW2 != NULL)
		{
			if ( (pW1->data) > (pW2->data) ) /* check for ascending order */
			{
				if (dir==0)
				{
					/* swap underway */
					swaps = 1;
					if (pW1 == head)
					{
						pW1 = swap(pW1);
						head = pW1;
					}
					else
					{
						pW1 = swap(pW1);
					}
				}
			}
			else if ( (pW1->data) <  (pW2->data) ) /* check for descending order */
			{
				if (dir==1)
				{
					/* swap underway */
					swaps = 1; // a swap is underway...
					if (pW1 == head)
					{
						pW1 = swap(pW1);
						head = pW1;
					}
					else
					{
						pW1 = swap(pW1);
					}				}
			}
			/* advance pointers through list */
			pW1 = pW1 -> pNext;
			pW2 = pW1 -> pNext;
		}
	}
	return head;
}
