/*
 * UrlMonitor.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef URLMONITOR_H_
#define URLMONITOR_H_

#include "monitor_common.h"

class Task
{
public:
	Task(){};
	virtual ~Task(){};
	bool operator()(Task *lhs, Task *rhs)
	{
		if(lhs->get_absolute_time() < rhs->get_absolute_time())
			return true;
		else
			return false;
	}
	virtual void execute() = 0;
	virtual std::chrono::time_point<std::chrono::system_clock> get_absolute_time() = 0;
	virtual void schedule_task() = 0;
	virtual std::string get_name() = 0;
};



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
	void execute();

	std::chrono::time_point<std::chrono::system_clock> get_absolute_time()
	{
		return next_time_slot;
	};

	std::string get_name()
	{
		return URI;
	}
	void schedule_task()
	{
		next_time_slot = std::chrono::system_clock::now() + std::chrono::seconds(polling_interval);
		//std::cout << "adding task to taskscheduler " << URI << std::endl;
		task_scheduler->add_task(this);
	}
};

#endif /* URLMONITOR_H_ */
