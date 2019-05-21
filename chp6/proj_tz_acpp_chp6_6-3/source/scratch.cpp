/*

 * ex6-3.cpp
 *
 *  Created on: May 21, 2019
 *      Author: takis


#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;		using std::cout;
using std::endl;		using std::copy;

//
// Create the half-open interval integer range [X, Y). Store into first argument.
//
void make_range(vector<int>& int_vec, vector<int>::size_type X, vector<int>::size_type Y)
{
	for (vector<int>::size_type i=X; i!=Y; ++i)
		int_vec.push_back(i);
	return;
}

int main()
{
//	vector<int> u; make_range(u, 10, 100); // form the range: [10,100)
	vector<int> u(10,100);
	vector<int> v;

	//copy(u.begin(),u.end(),v.begin());

	cout	<<  "Here is your vector of integers, concatenated from u and v:" << endl;
	for (vector<int>::const_iterator iter = u.begin(); iter != u.end(); ++iter)
			cout << *iter << endl;
	return 0;
}
*/
