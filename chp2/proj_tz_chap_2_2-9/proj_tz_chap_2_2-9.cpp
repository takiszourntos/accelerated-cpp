/*
 * proj_tz_chap_2_2-9.cpp
 *
 * 	program asks user for two numbers, then tells user which is larger
 *
 *  Created on: May 6, 2019
 *      Author: takis
 */

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	cout 	<< "Hi, please enter two numbers," << endl
			<< "and I'll tell you which is the" << endl
			<< "larger of the two... no kidding!" << endl;
	float first, second;
	cin >> first >> second;
	cout << endl << "processing..." << endl;
	(first > second) ? 	(cout << "the first one!") :
						(second > first) ? 	(cout << "the second one!") :
											(cout << "they're equal, yo! (I'm no fool!)");
	cout << endl;
}



