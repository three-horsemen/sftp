//
// Created by reubenjohn on 9/11/16.
//

#include <sys/time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "shared/Utils.hpp"

long Utils::getCurrentTimeMillis() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

string Utils::getFormattedEpochTime(long millisFromEpoch) {
	std::time_t tt = static_cast<time_t>(millisFromEpoch / 1000);
	boost::posix_time::ptime sentAt = boost::posix_time::from_time_t(tt);
	return boost::posix_time::to_iso_string(sentAt);
}

bool Utils::isNumber(const std::string &s) {
	return !s.empty() && std::find_if(s.begin(),
									  s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
