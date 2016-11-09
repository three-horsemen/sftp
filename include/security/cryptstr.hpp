#include <string>
#include <malloc.h>
#include <vector>
#include <boost/lexical_cast.hpp>

char *string_to_charArray(std::string s);

std::string charArray_to_string(const char *s);

std::string long_to_string(long a);

long string_to_long(std::string a);

std::vector<std::string> Tokenize(std::string str,
								  const std::string &delimiters);
