/*
 * UrlMonitor.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef URLMONITOR_H_
#define URLMONITOR_H_

#include "monitor_common.h"



class UrlMonitor
{

	std::string URI;
	std::string path;
	std::string name;
	MonitorMgr *task_scheduler;
	unsigned int polling_interval;


public:
	UrlMonitor(std::string uri_name, unsigned poll_interval, MonitorMgr *mgr);
	virtual ~UrlMonitor();
	void execute();

	unsigned int get_poll_interval()
	{
		return polling_interval;
	};

	std::string get_name()
	{
		return URI;
	}


};

#endif /* URLMONITOR_H_ */
