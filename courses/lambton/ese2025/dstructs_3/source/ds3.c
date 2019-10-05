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

	int loadarr[N] = {46, 2, 227, 23, 81, 320, 17, 9, 26, 25};

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

	printf("Your original linked list is: ");
	printList(mylisthead);

	/* find the largest element in the list */
	int max_int;
	find_largest(mylisthead, &max_int);

	/* sort the list for presentation */
	mylisthead = bubb_sort(mylisthead, 1U); /* ascending order = 0, descending order = 1 */

	/* announce the results */
	printf("\nYour largest integer is %d\n\n", max_int);

	printf("and your sorted list is: \n");
	ll_t* pW = mylisthead; /* our working pointer */
	while ( pW != NULL)
	{
		printf("%d ", pW -> data);
		pW = pW -> pNext;
	}
	printf("\n\n");

	/* exit successfully */
	free(mylisthead);
	return EXIT_SUCCESS;
}
