/*
 * MonitorMgr.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */
#include "monitor_common.h"
#include "TaskHandler.h"
#include "MonitorMgr.h"

#define THREAD_POOL_DEPTH (10)


MonitorMgr *MonitorMgr::instance = NULL;

MonitorMgr::MonitorMgr()
{
	thread_pool_size = THREAD_POOL_DEPTH;
	task_handlers.clear();
}


MonitorMgr::~MonitorMgr()
{
    destroy_task_handlers();
}


//thread pool stuff

void MonitorMgr::create_task_handler()
{
	TaskHandler *th = new TaskHandler(this);
	task_handlers.push_back(th);
}

void MonitorMgr::destroy_task_handlers()
{
    for(unsigned int i = 0;i < task_handlers.size();i++)
        delete (task_handlers[i]);

    task_handlers.clear();
}

TaskHandler* MonitorMgr::get_task_handler()
{
	TaskHandler *current = NULL;
	std::unique_lock<std::mutex> lk(tp_m);
	if(available_taskhandlers.size() == 0)
	{
		create_task_handler();
		tp_cv.wait(lk);
	}
	current = available_taskhandlers.front();
	available_taskhandlers.pop_front();
	return current;
}

void MonitorMgr::register_free_task_handler(TaskHandler *th)
{
	std::unique_lock<std::mutex> lk(tp_m);
	available_taskhandlers.push_back(th);
	tp_cv.notify_one();
}


//timer
