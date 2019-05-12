/*
 * load_dict.cpp
 *
 *  Created on: May 12, 2019
 *      Author: takis
 */

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "dictionary.h"

using std::string;				using std::list;
using std::ifstream;			using std::cout;
using std::endl;				using std::vector;

void load_dict(list<string>& data)
{
	ifstream infile("dict.txt");
	//list<string> data;

	// open the dictionary
	if (!infile)
	{
		cout << "error: unable to open file..." << endl;
		return;
	}

	// load the dictionary until we run out of strings
	string token;
	while (infile >> token)
	{
		data.push_back(token);
	}

	// close the file
	infile.close();
	return;
}

void find_palin(const list<string>& data, list<string>& pd )
{
	list<string>::const_iterator iter=data.begin(); // need read access to database only
	list<string> ret;

	string s_fwd, s_bwd;
	// invariant: iter points to the word being checked for palindromeness
	while (iter != data.end())
	{
		// get a word
		s_fwd = *iter;

		// create its reverse version
		list<string>::size_type token_len = s_fwd.size();
		list<string>::size_type i = 0;
		// invariant: s_bwd[i] is the character we're processing
		while (i != token_len)
		{
			s_bwd += (*iter)[token_len-1-i]; // build s_bwd through concatenation
			++i;
		}

		// check for palindromeness
		if (s_fwd == s_bwd) // is the word a palindrome?
		{
			ret.push_back(s_fwd);
		}
		s_bwd=""; // empty the reverse string

		// make the invariant true
		++iter;
	}
	pd = ret;
	return;
}

