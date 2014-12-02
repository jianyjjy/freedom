/*
 * Task.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: satram
 */
#include "common.h"
#include "UrlMonitor.h"
#include "Task.h"

Task::Task(std::shared_ptr<UrlMonitor> monitor_sp, bool delayed)
{
	url_monitor = monitor_sp;
	auto sp = url_monitor.lock();
	if(sp != NULL)
	{
		if(delayed)
			scheduled_time = std::chrono::system_clock::now() + std::chrono::seconds(sp.get()->get_poll_interval());
		else
			scheduled_time = std::chrono::system_clock::now();
		name = sp->get_name();
	}
	else
		throw std::runtime_error("underlying url monitor is gone");
}

void Task::execute()
{
	auto sp = url_monitor.lock();
	if(sp != NULL)
		sp.get()->execute();
	else
		throw std::runtime_error("underlying url monitor is gone");
}

std::chrono::time_point<std::chrono::system_clock> Task::get_absolute_time()
{
	return scheduled_time;
}

std::string Task::get_name()
{
	return name;
}

std::shared_ptr<UrlMonitor> Task::get_url_monitor()
{
	auto sp = url_monitor.lock();
	if(sp != NULL)
		return (sp);
	else
		throw std::runtime_error("underlying url monitor is gone");
}
