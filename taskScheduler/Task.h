/*
 * Task.h
 *
 *  Created on: Nov 25, 2014
 *      Author: satram
 */

#ifndef TASK_H_
#define TASK_H_

class UrlMonitor;

class Task
{
	std::weak_ptr<UrlMonitor> url_monitor;
	std::chrono::time_point<std::chrono::system_clock> scheduled_time;
	std::string name;

public:
	Task(std::shared_ptr<UrlMonitor> monitor_sp, bool delayed = false);
	virtual ~Task(){};
	void execute();
	std::chrono::time_point<std::chrono::system_clock> get_absolute_time();
	std::string get_name();
	std::shared_ptr<UrlMonitor> get_url_monitor();
};



#endif /* TASK_H_ */
