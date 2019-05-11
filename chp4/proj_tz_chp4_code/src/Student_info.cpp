/*
 * Student_info.cpp
 *
 *  Created on: May 10, 2019
 *      Author: takis
 */

#include "Student_info.h"
#include <iostream>
#include <string>
#include <vector>

using std::istream;			using std::vector;
// using std::cout;			using std::endl;

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
	// read and store the name, midterm and final grades
	is >> s.name >> s.midterm >> s.final;

	read_hw(is, s.homework);
	return is;
}

istream& read_hw(istream& in, vector<double>& hw)
{
	if (in)
	{
		// get rid of previous contents
		hw.clear();

		// read homework grades
		double x;
		while (in >> x) hw.push_back(x);

		// clear the stream so that input will work for next student
		in.clear();
	}
	return in;
}
