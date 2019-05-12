/*
 * proj_tz_acpp_chp5_framingpic.cpp
 *
 *  Created on: May 12, 2019
 *      Author: takis
 */

#include <iostream>
#include <string>
#include <vector>
#include "framing.h"

using std::cin;			using std::string;
using std::getline;		using std::vector;
using std::cout;		using std::endl;

int main()
{
	string sline;
	vector<string> vlines;

	cout << endl << "Please enter some text, followed by <CTRL><D>:" << endl << endl;
	// get a series of lines from the user
	while (getline(cin, sline))
	{
		vlines.push_back(sline);
	}

	// print the framed version
	cout << endl << "Lovely, now here is framed version: " << endl << endl;
	vector<string> framed_str = frame(vlines);
	vector<string>::const_iterator iter = framed_str.begin();
	vector<string>::const_iterator iter_end = framed_str.end();

	// invariant: iter points to the line being printed
	while (iter != iter_end)
	{
		cout << *iter << endl;
		++iter;
	}
	return 0;
}
