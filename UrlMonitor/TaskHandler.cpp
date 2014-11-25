/*
 * TaskHandler.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#include "monitor_common.h"
#include "MonitorMgr.h"
#include "UrlMonitor.h"
#include "TaskHandler.h"

TaskHandler::TaskHandler(MonitorMgr *mgr)
{
	thread_pool_mgr = mgr;
	tid = new std::thread(&TaskHandler::execute_task, this);
	destroy = false;
}

TaskHandler::~TaskHandler()
{
	destroy = true;
	wakeup();
	tid->join();
	delete(tid);
}


void TaskHandler::execute_task()
{
	while(!destroy)
	{
		std::unique_lock<std::mutex> lk(m);
		if(tasks_to_execute.size() == 0)
		{
			thread_pool_mgr->register_free_task_handler(this);
			cv.wait(lk);
			continue;
		}
		Task *t = tasks_to_execute.back();
		tasks_to_execute.pop_back();
		t->execute();
	}
	return;
}

void TaskHandler::wakeup()
{
	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
}

void TaskHandler::add_task(Task *t)
{
	std::unique_lock<std::mutex> lk(m);
	tasks_to_execute.push_back(t);
	cv.notify_one();
}
