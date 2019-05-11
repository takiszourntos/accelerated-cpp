/*
 * proj_tz_ex_4-3.cpp
 *
 *  Created on: May 11, 2019
 *      Author: takis
 */



#include <iostream>
#include <string>
#include <ios>
#include <iomanip>
#include "math.h"

using std::cout;			using std::endl;
using std::string;			using std::streamsize;
using std::setw;


int main()
{
	const int max_i = 10000;
	const streamsize pad = 1;
	const streamsize dw_1 = find_width(max_i) + pad; // finds the desired setw() parameter based on max_i
	const streamsize dw_2 = find_width(squaress(max_i)) + pad; // same thing for the square of max_i

	cout << "Squares from 0 up to (but not including) " << max_i << ":" << endl;
	for (int i=0; i != max_i; ++i)
	{
		cout << setw(dw_1) << i << setw(dw_2) << squaress(i) << endl << setw(0);
	}

	return 0;
}
