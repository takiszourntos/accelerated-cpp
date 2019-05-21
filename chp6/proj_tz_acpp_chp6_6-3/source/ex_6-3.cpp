/*
 * ex6-3.cpp
 *
 *  Created on: May 21, 2019
 *      Author: takis
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::vector;			using std::cout;
using std::endl;			using std::copy;
using std::back_inserter;

int main()
{
	vector<int> u(10,100);
	vector<int> v;

	copy(u.begin(), u.end(), back_inserter(v));

	cout	<<  "Here is your vector of integers, concatenated from u and v:" << endl;
	for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
			cout << *iter << endl;
	return 0;
}
