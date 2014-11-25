/*
 * MonitorMgr.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef MONITORMGR_H_
#define MONITORMGR_H_

class MonitorMgr {

	static MonitorMgr *instance;
	//std::map<UrlMonitor *, bool> url_monitors;
	//std::priority_queue<UrlMonitor *, std::deque<UrlMonitor *>, > timer;


	MonitorMgr();
	virtual ~MonitorMgr();

public:

	static MonitorMgr* get_instance()
	{
		if(instance == NULL)
			instance = new MonitorMgr();
		return instance;
	}

};

#endif /* MONITORMGR_H_ */
