/*
 * proj_tz_chap_2_2-0.cpp
 *
 *  Created on: May 6, 2019
 *      Author: takis
 */

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	cout << "What is your name, friend? " << endl;
	string name;
	cin >> name;

	// determine parameters for greeting, a rectangular array of rows and columns,
	// in which there is a border of asterisks, padding, and the greeting (centered)
	const string greeting = "Hello Friend " + name + " !";
	const unsigned int pad = 1; // the number of empty rows or columns
	const unsigned int rows = 2 + 2*pad + 1; // 2-star rows, 2*pad space rows, 1 row for greeting
	const string::size_type len = greeting.size(); // store the number of characters in greeting
	const string::size_type cols = 2 + 2*pad + len; // 2 asterisks, 2*pad spaces, and greeting

	cout << endl;
	for (unsigned int r = 0; r != rows; ++r)
	{
		// write a single row
		unsigned int c = 0;
		while (c != cols)
		{
			if ((r == pad + 1) && (c == pad + 1)) // are we at the greeting point?
			{
				cout << greeting;
				c += len;
			}
			else
			{
				if ( (r == 0) || (r == rows - 1) || (c == 0) || (c == cols - 1)) // border?
				{
					cout << "*";
				}
				else
				{
					cout << " "; // if not border or greeting point, write filler
				}
				++c;
			}
		}
		cout << endl; // don't forget to return after writing a row!
	}
	cout << endl;
	return 0;
}
