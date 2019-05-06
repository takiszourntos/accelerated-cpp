/*
 * proj_tz_chp1_1-6.cpp
 *
 *  Created on: May 5, 2019
 *      Author: takis
 */


#include <iostream>
#include <string>

int main()
{
	std::cout << "What is your name? ";
	std::string name;
	std::cin >> name;
	std::cout	<< "Hello, " << name
				<< std::endl << "And what is yours? ";
	std::cin >> name;
	std::cout	<< "Hello, " << name
				<< "; nice to meet you, too!" << std::endl;
	// now a series of cins
	std::cout << "Enter a bunch of strings!" << std::endl;
	std::string str1, str2, str3;
	((std::cin >> str1) >> str2) >> str3; // note the left-associative nature of cin (just like cout)
	std::cout << "You entered:" << std::endl;
	std::cout << str1 << std::endl << str2 << std::endl << str3 << std::endl;

	// another operator that is left associative is "+" which can concatenate a string and a string (or string
	// literal or value of type char);
	// in s + t, either s or t may be a string literal or a value of type char, but not both. Both may be
	// variables of type std::string; the result of s + t is a quantity of type std::string
	std::string sum1;
	sum1 = "taking things together: " + str1;
	std::string sum2;
	sum2 = sum1 + " <white space> ";
	std::string sum3;
	sum3 = (((sum2 +  " ") + str2) + " ") +  str3;
	std::cout << sum1 << std::endl;
	std::cout << sum2 << std::endl;
	std::cout << sum3 << std::endl;
	return 0;
}
