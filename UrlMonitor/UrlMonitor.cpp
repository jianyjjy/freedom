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

}

void UrlMonitor::execute()
{
	//schedule next-task
	schedule_task();

    //auto now = std::chrono::system_clock::now();
    //auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
   //ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    ss << " checking " << URI << std::endl;
    std::cout << ss.str();

	//download the playlist

	//filecompare size

	//if delta, call file compare module

	//get CompareResultInterface * and give it to corresponding playlist
}
