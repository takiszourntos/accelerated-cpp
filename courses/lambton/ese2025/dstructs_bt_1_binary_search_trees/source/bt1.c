/*
 * bt1.c : binary search tree program (demonstration code)
 *
 *  Created on: Oct. 16, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include "dstructs.h"

int main(void)
{
	key_t  pS[]={6,4,7,3,2,1,8,5,0,9};
	size_t NS = sizeof(pS)/sizeof(key_t);


//	bt_t *pBT=NULL;
//	pBT = createBT(pBT, pS, NS);
//	printf("Your Binary Search Tree contains the elements: \n");
//	inOrderTraversal(pBT);
//	printf("\n\n");

	/* attempt to create a more balanced tree */
	qsort(pS, NS, sizeof(key_t), comp_int); /* sort the array "in place" */
	bt_t *pBTbal=createBalBT(pS, NS);
	printf("Your Binary Search Tree contains the elements: \n");
	inOrderTraversal(pBTbal);
	printf("\n\n");



	return 0;
}
