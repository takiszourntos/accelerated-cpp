/*
********************************************************
* wordstats.cpp: program receives text from user  	   *
* 	       		 and then displays word count for      *
* 	       		 each word in the text;                *
* 	       		 makes use of vector container type    *
*                                               	   *
* author: Takis Zourntos                        	   *
* date: May 2019                              		   *
********************************************************
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "wordy.h"

using std::cout;					using std::cin;
using std::endl;					using std::string;
using std::vector;					using std::sort;

int main()
{
	// obtain text from user
	vector<string> words;
	string token;
	cout << "Please enter some text. Press <CTRL><D> to signal EoF:" << endl << endl;
	while (cin >> token)
		words.push_back(token);

	// generate our word statistics
	sort(words.begin(), words.end()); // use STD library sort algorithm to sort alphabetically
	vector<string>::const_iterator iter=words.begin();
	vs_sz count;
	word_record_t element;
	vector<word_record_t> wordstats;

	// invariant: iter points to the word to be stored in wordstats
	while (iter != words.end())
	{
		count = 1;
		// invariant: iter points to word that we are checking for a "next match"
		while (*(iter)==*(iter+1))
		{
			++count; // we have a "next match", so increment count
			++iter; // move to next word
		}
		element.word = *iter;
		element.count = count;
		wordstats.push_back(element);
		++iter;
	}

	// display results for the user
	string wi;
	vs_sz ci;
	cout << endl << "Here are the word counts for each word in your text:" << endl;
	for (vwr_citer_t iter_ws=wordstats.begin(); iter_ws != wordstats.end(); ++iter_ws)
	{
		wi = iter_ws -> word;
		ci = iter_ws -> count;
		cout << wi << ": " << ci << endl;
	}
	cout << endl;
	return 0;
}




