#ifndef MY_INCLUDES_WORDY_H_
#define MY_INCLUDES_WORDY_H_
/*
 * wordy.h
 *
 *  Created on: May 23, 2019
 *      Author: takis
 */

#include <string>
#include <vector>

typedef std::vector<std::string>::size_type vs_sz;

struct word_record_t
{
	std::string word;
	vs_sz count;
};

typedef std::vector<word_record_t>::const_iterator vwr_citer_t;


#endif /* MY_INCLUDES_WORDY_H_ */
