#pragma once


#ifndef stringfunc
#define stringfunc "STRINGTOOLS"

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>


//thanks Evan Teran on stack exchange
template <typename Out>
void split(const std::string& s, char delim, Out result);

std::vector<std::string> split(const std::string& s, char delim);
#endif // !stringfunc

