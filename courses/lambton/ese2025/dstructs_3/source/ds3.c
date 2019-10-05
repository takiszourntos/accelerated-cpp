/*
 * ds2.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takis
 */


#include <stdio.h>
#include <stdlib.h>
#include "dstructs.h"

#define		N		10

int main()
{

	int loadarr[N] = { 23, 46, 227, 81, 320,
                       17,  9,  26, 25, 22  };

	/* create a linked list from loadarr data */
	ll_t* mylisthead;
	mylisthead = (ll_t *) malloc(sizeof(ll_t));
	mylisthead -> data = loadarr[0];
	mylisthead -> pNext = NULL;
	size_t i = 1;
	while (i != N)
	{
		addNode(mylisthead, loadarr[i]);
		++i;
	}

	printf("Your original linked list is: \n");
	ll_t* pW = mylisthead; /* our working pointer */
	while (pW != NULL)
	{
		printf("%d ", pW -> data);
		pW = pW -> pNext;
	}
	printf("\n\n");

	/* find the largest element in the list */
	int max_int;
	ll_t *pLargest = NULL;
	if ((pLargest = find_largest(mylisthead, &max_int))==NULL)
		printf("error: list must contain more than one element");

	/* sort the list for presentation */
	mylisthead = bubb_sort(mylisthead, 0U); /* ascending order = 0, descending order = 1 */


	/* announce the results */
	printf("Your largest integer is %d\n\n", max_int);

	printf("And your sorted list is: \n");
	pW = mylisthead; /* our working pointer */
	while (pW != NULL)
	{
		printf("%d ", pW -> data);
		pW = pW -> pNext;
	}
	printf("\n\n");

	/* exit successfully */
	free(mylisthead);
	return EXIT_SUCCESS;
}
