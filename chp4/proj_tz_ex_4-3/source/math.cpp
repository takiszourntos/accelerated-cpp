/*
 * math.cpp
 *
 *  Created on: May 11, 2019
 *      Author: takis
 */

#include "math.h"
#include <ios>

using std::streamsize;

streamsize squaress(const int x)
{
	streamsize y;
	y = x*x;
	return y;
}

streamsize find_width(const int num)
{
	streamsize num_digits = 1; 	// an integer quantity must be at least 0,
								// and zero is represented by a single digit
	int quotient=num/10;

	// invariant: num_digits is the number of digits in num (an integer)
	while (quotient != 0)
	{
		quotient = quotient / 10;
		++num_digits; // make our invariant true!
	}

	return num_digits;
}

