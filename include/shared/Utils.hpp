//
// Created by reubenjohn on 9/11/16.
//

#ifndef SFTP_UTILS_HPP
#define SFTP_UTILS_HPP

#include <string>

#include <time.h>

using namespace std;

class Utils {
public:
	static long getCurrentTimeMillis();

	static string getFormattedEpochTime(long);

	static bool isNumber(const std::string &s);
};


#endif //SFTP_UTILS_HPP
