/*
 * UrlMonitor.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */
#include "common.h"
#include "TaskHandler.h"
#include "MonitorMgr.h"
#include "UrlMonitor.h"

#define PRINT(X) //

UrlMonitor::UrlMonitor(std::string uri_name, unsigned poll_interval, MonitorMgr *mgr)
{
	URI = uri_name;
	size_t path_offset = URI.find_last_of("/");
	if(path_offset != std::string::npos)
	{
		path = URI.substr(0, path_offset+1);
		name = URI.substr(path_offset+1, URI.size());
	}
	polling_interval = poll_interval;
	task_scheduler = mgr;
	schedule_task();
}

UrlMonitor::~UrlMonitor()
{
	std::cout << "dtor UrlMonitor " << URI << std::endl;
}

void UrlMonitor::execute(TaskHandler *th)
{
	//schedule next-task
	schedule_future_task();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	//download the playlist

	//filecompare size

	//if delta, call file compare module

	//get CompareResultInterface * and give it to corresponding playlist
}
