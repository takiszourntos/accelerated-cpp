#ifndef INC_STUDENT_INFO_H_
#define INC_STUDENT_INFO_H_
/*
 * Student_info.h
 *
 *  Created on: May 10, 2019
 *      Author: takis
 */

#include <iostream>
#include <ios>
#include <string>
#include <vector>

struct Student_info
{
	std::string name;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);


#endif /* INC_STUDENT_INFO_H_ */
