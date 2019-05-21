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
using std::back_inserter;	using std::inserter;

int main()
{
	vector<int> u(10,100);
	vector<int> v;

	// copy(u.begin(), u.end(), back_inserter(v)); // first fix
	copy(u.begin(), u.end(),
			inserter(v, v.end())); // second fix (front_inserter not available for vector type/container)

	cout	<<  "Here is your vector of integers, concatenated from u and v:" << endl;
	for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
			cout << *iter << endl;
	return 0;
}
