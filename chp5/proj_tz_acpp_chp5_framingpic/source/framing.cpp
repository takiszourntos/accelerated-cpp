/*
 * framing.cpp
 *
 *  Created on: May 12, 2019
 *      Author: takis
 */

#include<vector>
#include<string>
#include "framing.h"

using std::vector;			using std::string;
using std::max;

string::size_type width(const vector<string>& vec)
{
	string::size_type maxlen = 0;
	for (vector<string>::size_type i; i != vec.size(); ++i)
			maxlen = max(maxlen, vec[i].size());

	return maxlen;
}

vector<string> frame(const vector<string>& lines)
{
	vector<string> ret;
	string::size_type maxlen = width(lines);
	string border(maxlen + 4, '*');

	// write the top border
	ret.push_back(border);

	// write each interior row, bordered by an asterisk and a space
	for (vector<string>::size_type i=0; i != lines.size(); ++i)
	{
		ret.push_back("* " + lines[i]
						+ string(maxlen - lines[i].size(), ' ') + " *");
	}

	// write the bottom border
	ret.push_back(border);
	return ret;
}
