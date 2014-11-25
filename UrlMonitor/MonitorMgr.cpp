/*
 * MonitorMgr.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */
#include "monitor_common.h"
#include "MonitorMgr.h"
#include "UrlMonitor.h"
#include "TaskHandler.h"

#define THREAD_POOL_DEPTH (10)


MonitorMgr *MonitorMgr::instance = NULL;

MonitorMgr::MonitorMgr()
{
	thread_pool_size = THREAD_POOL_DEPTH;
	task_handlers.clear();
	destroy = false;
	timer = new std::thread(&MonitorMgr::timer_thread, this);
	urlMonitor.clear();
}


MonitorMgr::~MonitorMgr()
{
    destroy_task_handlers();
    destroy = true;
    timer->join();
    remove_all_url_monitor();
}


/*
 * thread pool
 */

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


/*
 * Timer
 */

void MonitorMgr::timer_thread()
{
	while(!destroy)
	{
		std::unique_lock<std::mutex> lk(m);
		if(scheduld_tasks.size() == 0)
		{
			//there aren't any tasks in scheduler priority queue
			cv.wait(lk);
		}
		//take the task with nearest time point
		Task *tk = scheduld_tasks.top();
		scheduld_tasks.pop();

		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		if(now > tk->get_absolute_time())
		{
			//execute task whose time-to-execute has already crossed
			TaskHandler *th = get_task_handler();
			th->add_task(tk);
		}
		else if(cv.wait_until(lk, tk->get_absolute_time()) == std::cv_status::timeout)
		{
			//execution of tasks in thread pool
			TaskHandler *th = get_task_handler();
			th->add_task(tk);
		}
	}
	return;
}




/*
 * Url Monitor
 */
void MonitorMgr::create_url_monitor(char *playlist_name, unsigned int poll_interval)
{
	UrlMonitor *task = new UrlMonitor(playlist_name, poll_interval, this);
	urlMonitor.push_back(task);
}

void MonitorMgr::remove_all_url_monitor()
{
	for(unsigned int i = 0; i < urlMonitor.size(); i++)
		delete(urlMonitor[i]);
	urlMonitor.clear();
}

void MonitorMgr::remove_url_monitor(char * playlist_name)
{
	bool found = false;
	for(auto it = urlMonitor.begin(), ite = urlMonitor.end(); it != ite; it++)
	{
		if((*it)->get_name().compare(playlist_name) == 0)
		{
			found = true;
			delete(*it);
			it = urlMonitor.erase(it);
			break;
		}
	}
	if(!found)
	{
		std::ostringstream oss;
		oss << "unable to find url monitor for playlist " << playlist_name;
		throw std::runtime_error(oss.str());
	}
}

/*
 * Task related
 */

void MonitorMgr::add_task(Task *tk)
{
	std::unique_lock<std::mutex> lk(m);
	scheduld_tasks.push(tk);
	cv.notify_one();
}
