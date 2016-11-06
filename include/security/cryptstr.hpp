#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <vector>
// using namespace std;
char *string_to_charArray(std::string s);
std::string charArray_to_string(char *s, int len);
std::string charArray_to_string(const char *s);

std::string int_to_string(int a);
int string_to_int(std::string a);

std::vector<std::string> Tokenize(std::string str,
		const std::string& delimiters);
