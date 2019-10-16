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

	qsort(pS, NS, sizeof(key_t), comp_int); /* sort the array "in place" */


	return 0;
}
