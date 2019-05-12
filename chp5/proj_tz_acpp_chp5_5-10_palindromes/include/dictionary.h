#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
/*
 * dictionary.h
 *
 *  Created on: May 12, 2019
 *      Author: takis
 */

#include <string>
#include <list>

void load_dict(std::list<std::string>&);
void find_palin(const std::list<std::string>&, std::list<std::string>&);

#endif /* INCLUDE_DICTIONARY_H_ */
