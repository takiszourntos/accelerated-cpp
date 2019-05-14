/*
**************************************************************************************
* palindrome.cpp:                                                                    *
*                                                                                    *
* this program finds all the palindromes in a dictionary, found in a file ./dict.txt *
*                     (dictionary found at: https://github.com/dwyl)                 *
* author: Takis Zourntos                                                             *
* date: May 2019                                                                     *
**************************************************************************************
 */

#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "dictionary.h"

using std::string;				using std::list;
using std::cout;				using std::endl;
using std::max;

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

	// display the palindromes, while you're at it, find the longest palindrome
	list<string> palindromes; // store the palindromes here
	find_palin(dict, palindromes);
	cout << endl << "Here are the palindromes in the file ./dict.txt:" << endl;
	list<string>::const_iterator iter_pd = palindromes.begin();
	list<string>::size_type maxlen = 0;
	list<string>::size_type currentlen = 0;
	string max_palindrome="";
	// invariant: iter_pd points to the palindrome to be printed
	while (iter_pd != palindromes.end())
	{
		currentlen = (*iter_pd).size();
		if (currentlen > maxlen)
		{
			maxlen = currentlen;
			max_palindrome = *iter_pd;
		}
		cout << *iter_pd << endl;
		++iter_pd;
	}
	cout << endl;
	cout << "And, by the way, the longest palindrome is " << max_palindrome << " at length of " << maxlen << " characters." << endl;
	return 0;
}

