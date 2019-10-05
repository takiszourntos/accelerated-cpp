/*
 * dstructs.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takiss
 */

#include <stdio.h>
#include <stdlib.h>
#include "dstructs.h"

/*
 * createNode():
 *
 * creates a node of type ll_t from the heap, and returns
 * a pointer to this newly created node; sets the node's own
 * pNext pointer to NULL
 *
 */
ll_t* createNode()
{
	/* create a pointer for the new node */
    ll_t *node;

    /* allocate the node from heap */
    node = (ll_t *) malloc(sizeof(ll_t));

    /* make next point to NULL */
    node -> pNext = NULL;//

    /* return the pointer to the new node */
    return node;
}

/*
 * addNode():
 *
 * adds a new node (with node->data = value) to the bottom/back
 * of the list referenced by the pointer, head;
 * if head==NULL, a new list is created
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
 *
 * returns a pointer to the largest element in the list;
 * returns maximum value as second parameter (passed by reference)
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
 * 		0 ----> A ----> B ----> 1
 *                 p2A     p2B     p21
 *
 *		and re-arranges pointers so that:
 *
 *		0 ----> B ----> A ----> 1
 *                 p2B     p2A     p21
 *
 *       	returning p0
 *
 */

ll_t* swap(ll_t* p20, ll_t* p2A)
{
	ll_t	*pr; /* return variable */
	ll_t	*p2B = p2A -> pNext; /* pointer to B */
	ll_t	*p21 = p2B -> pNext; /* what B is pointing to */

	pr = (p20 -> pNext) = p2B; /* 0 -> B */
	p2B -> pNext = p2A; /* B -> A */
	p2A -> pNext = p21; /* A -> 1 */

	/* done */
	return pr;
}

/*
 * print out the linked list
 */
void printList(ll_t* head)
{
	ll_t* pW = head; /* our working pointer */
	while (pW != NULL)
	{
		printf("%d ", pW -> data);
		pW = pW -> pNext;
	}
	printf("\n");
	return;
}

/*
 * bubb_sort():
 * 
 * performs a Bubble Sort on a list (referenced by head pointer parameter)
 *
 */
ll_t* bubb_sort(ll_t *head, bool_t dir)
{
	bool_t 	swaps = 1; /* swapping flag for bubble sort algorithm */
	ll_t	*pW0;
	ll_t	*pW1; /* working pointer */
	ll_t	*pW2; /* working pointer's "child" */
    int		sweep = 1;

	while (swaps)
	{
		swaps = 0;
		/* reset pointers to point to beginning of list */
		pW0 = pW1 = head;
		pW2 = pW1 -> pNext;
		printf("sweep %d\n", sweep);

		while (pW2 != NULL)
		{
		    printf("head->%d, pW1->%d, pW2->%d\n", head->data, pW1->data, pW2->data);
		    printList(head);
		    if ( ((dir==0) && (pW1->data) > (pW2->data)) || ((dir==1) && ((pW1->data) < (pW2->data)) ) ) /* check for proper ordering */
			{
				/* swap underway */
				swaps = 1;
				if (pW1 == head)
				{
					pW1 = swap(pW0, pW1);
					head = pW1;
				}
				else
				{
					pW1 = swap(pW0, pW1);
				}
				pW2 = pW1 -> pNext; /* make sure pW2 is synced with pW1 */
			}
			/* advance pointers through list */
		    pW0 = pW1;
		    pW1 = pW1 -> pNext;
		    pW2 = pW1 -> pNext;
		}
		++sweep;
	}
	return head;
}
