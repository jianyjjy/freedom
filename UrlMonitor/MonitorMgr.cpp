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
	task_handler_count = 0;
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
	TaskHandler *th = new TaskHandler(this, task_handler_count++);
	task_handlers.push_back(th);
}

void MonitorMgr::destroy_task_handlers()
{
    for(unsigned int i = 0;i < task_handlers.size();i++)
    {
        delete (task_handlers[i]);
        task_handler_count--;
    }
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
		if(scheduled_tasks.size() == 0)
		{
			std::cout << "timer sleep\n";
			//std::cout << "timer thread sleeping - there aren't any tasks in scheduler priority queue\n";
			cv.wait(lk);
		}
		//std::cout << "timer thread, take the task with nearest time point\n";
		Task *tk = scheduled_tasks.top();
		std::cout << "timer for " << tk->get_name() << "\n";
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		if(now > tk->get_absolute_time())
		{
			//std::cout << "execute - already expired\n";
			//std::cout << "execute task whose time-to-execute has already crossed\n";
			scheduled_tasks.pop();
			TaskHandler *th = get_task_handler();
			std::cout << "Th#" << th->get_id() << " execute1 task for " << tk->get_name() << std::endl;
			th->add_task(tk);
		}
		if(cv.wait_until(lk, tk->get_absolute_time()) == std::cv_status::timeout)
		{
			//std::cout << "execute - just expired\n";
			//std::cout << "execution of tasks in thread pool\n";
			scheduled_tasks.pop();
			TaskHandler *th = get_task_handler();
			std::cout << "Th#" << th->get_id() << " execute2 task for " << tk->get_name() << std::endl;
			th->add_task(tk);
		}
		//else
			//std::cout << " disturbed\n";
	}
	return;
}




/*
 * Url Monitor
 */
void MonitorMgr::create_url_monitor(std::string playlist_name, unsigned int poll_interval)
{
	std::unique_lock<std::mutex> lk(m);
	std::cout << "create urlmonitor " << playlist_name << "(poll " << poll_interval << "s)\n";
	UrlMonitor *task = new UrlMonitor(playlist_name, poll_interval, this);
	urlMonitor.push_back(task);
}

void MonitorMgr::remove_all_url_monitor()
{
	std::unique_lock<std::mutex> lk(m);
	for(unsigned int i = 0; i < urlMonitor.size(); i++)
		delete(urlMonitor[i]);
	urlMonitor.clear();
}

void MonitorMgr::remove_url_monitor(char * playlist_name)
{
	std::unique_lock<std::mutex> lk(m);
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
	//std::unique_lock<std::mutex> lk(m);
	std::cout << "add task " << tk->get_name() << std::endl;
	scheduled_tasks.push(tk);
	//Task *t = scheduled_tasks.top();
	//std::cout << "top of pqueue " << t->get_name() << std::endl;
	cv.notify_one();
}
