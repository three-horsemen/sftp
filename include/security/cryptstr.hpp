#include <string>
#include <malloc.h>
#include <vector>
#include <boost/lexical_cast.hpp>

char *string_to_charArray(std::string s);

std::string charArray_to_string(const char *s);

std::string charArray_to_string(const char *s, ssize_t len);

std::string long_to_string(long a);

long string_to_long(std::string a);

unsigned long long string_to_unsigned_long_long(std::string a);

std::vector<std::string> Tokenize(std::string str,
								  const std::string &delimiters);
