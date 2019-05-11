#ifndef INC_GRADE_H_
#define INC_GRADE_H_
/*
 * grade.h
 *
 *  Created on: May 10, 2019
 *      Author: takis
 */

#include <vector>
#include "Student_info.h"
//#include <algorithm>

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);

#endif /* INC_GRADE_H_ */
