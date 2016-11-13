#include "security/cryptstr.hpp"

char *string_to_charArray(std::string s) {
	char *d = (char *) malloc((s.size()) * sizeof(char) + 1); // Space for length plus nul
	if (d == NULL)
		return NULL;                    // No memory
	strcpy(d, s.c_str());               // Copy the characters
	d[s.size()] = '\0';
	return d;                           // Return the new string
}

std::string charArray_to_string(const char *s) {
	return std::string(s);
}

std::string charArray_to_string(const char *s, ssize_t len) {
	return std::string(s, (unsigned long) len);
}

std::string long_to_string(long a) {
	return std::to_string(a);
}

std::vector<std::string> Tokenize(std::string str,
								  const std::string &delimiters) {
	std::vector<std::string> tokens;
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
	return tokens;
	/* Sample usage:
	 string str = "0123#456@789";
	 string delims = "@#";
	 vector<string> tokens = Tokenize(str, delims);
	 //vector<string> tokens = Tokenize(str);
	 for(int i = 0; i < tokens.size(); i++)
	 cout << tokens[i] << endl;
	 cout << "The original string: " << str << endl;
	 */
}

long string_to_long(std::string str) {
	try {
		return boost::lexical_cast<long>(str);
	}
	catch (const boost::bad_lexical_cast &) {
		return 0;
	}
}