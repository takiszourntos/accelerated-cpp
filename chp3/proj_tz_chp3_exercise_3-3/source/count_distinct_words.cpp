/*
 * count_distinct_words.cpp
 *
 * 	This program is my solution to Exercise 3-3 in Koenig & Moo, Accelerated C++.
 *
 * 	This program compiles a list of words read from a input stream,
 * 	and determines the number of times each distinct word appears.
 * 	First version does not remove punctuation, thus "it" and "it." are
 * 	considered distinct :( ... I tried, but that part of the code does not work.
 *
 *
 *  Created on: May 7, 2019
 *      Author: takis
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector; using std::sort;


int main()
{
	// get user to start typing words
	cout	<< "Howdy! Please start entering text. I am going to provide a count" << endl
			<< "of each distinct word. " "Believe it!" << endl;

	vector<string> wordy_text;
	string element;
	string::size_type length;
	// invariant is: wordy_text contains each word read so far
	while (cin >> element)
	{
		// remove punctuation
		length = element.size();
		const string punct_end = element.substr(length-1,0);
		const string punct_begin = element.substr(0,0);
		// remove any initial quote character
		if (punct_begin == "\"") element = element.substr(1,length-1);
		if ( (punct_end == ",")|| (punct_end == ".") || (punct_end == "!") || (punct_end =="?") || (punct_end ==";") || (punct_end =="\"") || (punct_end ==":"))
				{
					element = element.substr(0,length-2);
				}
		wordy_text.push_back(element);
	}


	// sort vector to facilitate scanning
	sort(wordy_text.begin(), wordy_text.end());

	// provide flying word count
	typedef vector<string>::size_type vec_str_sz;
	const vec_str_sz total_word_count = wordy_text.size(); // total word count
	cout << "total word count: " << total_word_count << endl;
	vec_str_sz counter = 0;
	vec_str_sz index = 0;
	vec_str_sz streak; // holds the number of times current word appears

	// invariant is:
	//		counter is the current number of processed words
	// 		index points to the next unique word in wordy_text
	while (counter != total_word_count)
	{
		streak = 1; // each word appears at least once
		element = wordy_text[index];
		cout << element << " appears ";
		// count the number of times element appears, i.e., the "streak"; streak \ge 1
		// invariant is:
		//		streak contains the number of times the string element appears in the text
		while ( (index != (total_word_count-1)) && (element ==  wordy_text[index+1]) )
			{
				++streak; // increment the streak
				++index; // point to next word
				element = wordy_text[index]; // move to next word
			}
		cout << streak << " time(s)" << endl;
		counter += streak;
		++index;
	}
	return 0;
}




