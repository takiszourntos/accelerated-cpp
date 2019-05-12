/*
 * palindromes.cpp
 *
 *  Created on: May 12, 2019
 *      Author: takis
 */

#include <string>
#include <list>
#include <iostream>
#include "dictionary.h"

using std::string;				using std::list;
using std::cout;				using std::endl;

int main()
{
	// load the dictionary
	list<string> dict;
	load_dict(dict);

	if (dict.size() == 0)
	{
		cout << "error: dictionary emtpy or cannot open file..." << endl;
		return 1;
	}

	// display the palindromes
	list<string> palindromes;
	find_palin(dict, palindromes); // store the palindromes here
	cout << endl << "Here are the palindromes in the file " << " :" << endl;
	list<string>::const_iterator iter_pd = palindromes.begin();

	// invariant: iter_pd points to the palindrome to be printed
	while (iter_pd != palindromes.end())
	{
		cout << *iter_pd << endl;
		++iter_pd;
	}
	cout << endl;
	return 0;
}

