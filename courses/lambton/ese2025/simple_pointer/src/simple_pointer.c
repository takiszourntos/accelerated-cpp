/*
 ============================================================================
 Name        : simple_pointer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void assign (int *c, int *d)
{
	d=c;
	return;
}

void assign2 (void *ptr1, void *ptr2)
{
	int *c = (int *) ptr1;
	int *d = (int *) ptr2;

	d = c;
	return;
}

int main(void) {
	puts("!!!Hello World!!!\n\n"); /* prints !!!Hello World!!! */

	int *a = malloc(sizeof(int)); // allocate space for pointer a
	int *b = malloc(sizeof(int)); // allocate space for pointer b
	int *c = malloc(sizeof(int)); // allocate space for pointer c

	*a = 6;
	*b = 7; /* will *a also be modified? */
	*c = 8;

	printf ("Initially, pointer a and pointer b are located at:\n");
	printf ("&a = %p and &b = %p\n", &a,  &b);
	printf ("With contents given by %p and %p, respectively,\n",a, b);
	printf ("Dereferenced values are *a=%d and *b=%d\n\n", *a, *b);

	*b = *a; /* this just makes the pointer contents the same, but pointers
				are different variables (with their own memory locations */
	printf ("Now, after *b=*a, the locations of the pointers are:\n");
	printf ("&a = %p and &b = %p\n", &a,  &b);
	printf ("meaning that they are still different variables.\n");
	printf ("With contents given by %p and %p, respectively,\n",a, b);
	printf ("Dereferenced values are *a=%d and *b=%d\n\n", *a, *b);

	b=a; /* pointer assignment: b and a become the same thing, in all respects */
	printf ("However, after the assignment b = a, the pointers point to the same thing same thing:\n");
	printf ("&a = %p and &b = %p\n", &a,  &b);
	printf ("With contents given by %p and %p, respectively,\n",a, b);
	printf ("Dereferenced values are *a=%d and *b=%d\n\n", *a, *b);

	int *a2 = malloc(sizeof(int)); // allocate space for pointer a
	int *b2 = malloc(sizeof(int)); // allocate space for pointer b
	*a2=0;
	*b2=1;

	printf ("Let's try something a little different, with fresh pointers \n");
	printf ("a2 and b2, which are located at:\n");
	printf ("&a2 = %p and &b2 = %p\n\n", &a2,  &b2);
	printf ("With contents given by %p and %p, respectively,\n",a2, b2);
	printf ("Dereferenced values are *a2=%d and *b2=%d\n\n", *a2, *b2);

	assign2(a2,b2);
	printf ("we will do the assignment, but through a function, assign2(),\n");
	printf ("which simply sets d=c; and we have:\n");
	printf ("&a2 = %p and &b2 = %p\n", &a2,  &b2);
	printf ("With contents given by %p and %p, respectively,\n",a2, b2);
	printf ("Dereferenced values are *a2=%d and *b2=%d\n\n", *a2, *b2);

	return EXIT_SUCCESS;
}
