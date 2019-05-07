/*
 * student_grades.cpp
 *
 * 	This program is based on the main program of Chapter 3,
 * 	which I am developing here, partially from memory, in order
 * 	to improve my C++ skills.
 *
 * 	The program reads in the student's name, test and exam grades,
 * 	and then all homework grades (a series of grades, of an unspecified number).
 *
 * 	A summary of the grades is provided, including the median and average
 * 	of all homework.
 *
 * 	The summary includes a list of name, test and exam grades, followed by
 * 	the median and averages of homework, followed by a final grade, computed
 * 	according to some formula.
 *
 * 	Main feature of this program is to explore C++ containers, sorting,
 * 	typedef, loop invariants.
 *
 *
 *  Created on: May 7, 2019
 *      Author: takis
 */


#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <vector>
#include <algorithm>

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector; using std::sort;
using std::streamsize; using std::setprecision;

int main()
{
	// get student's name
	string first_name, family_name;
	cout 	<< "Please enter your first name, "
				"followed by your family name."
			<<	endl;
	cin >> first_name >> family_name;

	// get test and final exam scores, to three significant digits
	double test_score, exam_score;
	cout 	<< "Thank you, " + first_name + "!" << endl
			<< "Now, please enter your mid-term test score, followed by your exam score, in percent."
			<< endl;
	cin >> test_score >> exam_score;

	// get the homework grades from the student, storing in a container of type vector<double>
	vector<double> homework_grades; // define a vector container of grades, note the funky C++ notation,
									// not to be found in regular C; it specifies that items in the
									// container will all be of type double
	cout 	<< 	"Now please enter all homework grades,"
			<< 	"followed by an end-of-file, i.e., " << endl
			<<	"<CTRL><D> on Linux, <CTRL><Z> on other platforms." << endl;
 	double hwkgrade; // temporary storage for each grade
 	double sum=0;
 	// invariant is:
 	// 			"homework_grades contains each grade read so far, and sum
 	//			contains the cumulative sum of the grades so far..."
 	// N.B.: statements within the while loop are merely chosen to
 	//		 make the invariant true by the time execution reaches "}"
 	//
 	while (cin >> hwkgrade)
	{
 		homework_grades.push_back(hwkgrade);
 		sum += hwkgrade;
	}

 	// compute average and median grades
	typedef vector<double>::size_type vec_sz;
	vec_sz size = homework_grades.size();
	if (size==0)
	{
		cout << "There are no homework grades, invalid! Exiting..." << endl;
		return 1;
	}
	const double average=sum/size;
	double median;
	sort(homework_grades.begin(),homework_grades.end()); // sort homework_grades in non-decreasing order
	const vec_sz mid = size/2;
	median = ((size % 2)==0) ? (homework_grades[mid-1]+homework_grades[mid])/2
							 :	homework_grades[mid];

	// summarize results, to three digits of precision
	streamsize prec = cout.precision(); // store the default cout precision
	cout 	<< "Your average and median homwork scores are as follows." << endl
			<< setprecision(3)
			<< "Your average is " << average << " and your median is " << median << "." << endl
			<< "Your final grade is: " << endl
			<< 0.2*test_score + 0.4*exam_score + 0.4*median
			<< setprecision(prec) << endl
			<< "Thank you for using Auto-Grade!" << endl;
	return 0;

}
