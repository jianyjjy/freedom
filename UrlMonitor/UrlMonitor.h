/*
 * UrlMonitor.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef URLMONITOR_H_
#define URLMONITOR_H_

#include "monitor_common.h"



class UrlMonitor : public Task
{

	std::string URI;
	std::string path;
	std::string name;
	MonitorMgr *task_scheduler;
	unsigned int polling_interval;
	std::chrono::time_point<std::chrono::system_clock> next_time_slot;

public:
	UrlMonitor(std::string uri_name, unsigned poll_interval, MonitorMgr *mgr);
	virtual ~UrlMonitor();
	void execute(TaskHandler *th);

	std::chrono::time_point<std::chrono::system_clock> get_absolute_time()
	{
		return next_time_slot;
	};

	std::string get_name()
	{
		return URI;
	}
	void schedule_future_task()
	{
		next_time_slot = std::chrono::system_clock::now() + std::chrono::seconds(polling_interval);
		task_scheduler->add_task(this);
	}

	void schedule_task()
	{
		next_time_slot = std::chrono::system_clock::now();
		task_scheduler->add_task(this);
	}

};

#endif /* URLMONITOR_H_ */
