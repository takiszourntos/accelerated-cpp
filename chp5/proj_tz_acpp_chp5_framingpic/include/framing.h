#ifndef INCLUDE_FRAMING_H_
#define INCLUDE_FRAMING_H_
/*
 * framing.h
 *
 *  Created on: May 12, 2019
 *      Author: takis
 */
#include <string>
#include <vector>

std::string::size_type width(const std::vector<std::string>&);
std::vector<std::string> frame(const std::vector<std::string>&);

#endif /* INCLUDE_FRAMING_H_ */
