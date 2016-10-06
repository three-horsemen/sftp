/*
 * TimelineManager.hpp
 *
 *  Created on: 04-Oct-2016
 *      Author: reubenjohn
 */

#ifndef INCLUDE_SYNC_TIMELINE_TIMELINEMANAGER_HPP_
#define INCLUDE_SYNC_TIMELINE_TIMELINEMANAGER_HPP_

#include <string>

namespace sync {

using namespace std;

class TimelineManager {
public:
	TimelineManager();
	virtual ~TimelineManager();

	bool initiateCommand(string filesAffected[]);
};

} /* namespace sync */

#endif /* INCLUDE_SYNC_TIMELINE_TIMELINEMANAGER_HPP_ */
