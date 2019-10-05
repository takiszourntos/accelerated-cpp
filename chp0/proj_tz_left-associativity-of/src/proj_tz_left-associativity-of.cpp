//============================================================================
// Name        : proj_tz_left-associativity-of.cpp
// Author      : Takis Zourntos
// Version     :
// Copyright   : Copyright (c) 2019 Takis Zourntos
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

int main()
{
	// the << operator takes its right argument (usually a string literal,
	// and "send it" to its left argument (of type std::ostream), and
	// RETURNS std::cout, allowing the operator to be chained together as seen
	// below:
	
	( ( ( (	(std::cout << "Halo Verld!") << std::endl) << "this line is an attempt to illustrate") << std::endl) 
	 << "the left-associativity of the \" << \" operator ") <<  std::endl; // prints Halo Verld!
	
	return 0;
}
