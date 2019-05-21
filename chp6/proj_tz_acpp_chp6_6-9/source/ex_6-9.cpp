/*
 * ex_6-9.cpp: concatenate all the elements of a vector<string> into one gigantic string,
 * 				and use a library algorithm to do so...
 *
 *  Created on: May 21, 2019
 *      Author: takis
 */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <iterator>
#include <numeric>

using std::cout;				using std::cin;
using std::endl;				using std::string;
using std::vector;				using std::copy;
using std::accumulate;
//using std::back_inserter;

int main()
{
	vector<string> whole_lotta;

	// inhale some date from the user
	cout << endl << "Enter some text to concatenate, followed by <CTRL><D>, please!" << endl << endl;
	//vector<string>::iterator iter=whole_lotta.begin();
	string token;
	// invariant: iter points to the token being added to whole_lotta
	while (cin >> token)
	{
		whole_lotta.push_back(token);
	}

	// here is the massive concatenation!!!
	string massive_string;
	// string massive_alternative;
	massive_string = accumulate(whole_lotta.begin(), whole_lotta.end(), massive_string); // concatenate using accumlate()
	// cannot be done: seems you cannot mix types with copy... too much ambiguity? Should work, IMHO
	// copy(whole_lotta.begin(), whole_lotta.end(), back_inserter(massive_alternative)); // contatenate using copy()

	// display results
	cout << endl << "Here is your massive string:" << endl << endl
		 << massive_string << endl << endl;
//		 << "And here is the Alternative Version: " << endl << endl
//		 << massive_alternative << endl << endl;

	return 0;
}
