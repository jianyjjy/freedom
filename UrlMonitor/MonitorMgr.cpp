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



#define PRINT(X) //

#define THREAD_POOL_DEPTH (10)


MonitorMgr *MonitorMgr::instance = NULL;
unsigned int MonitorMgr::ref_count = 0;

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
	std::cout << "dtor Monitor mgr\n";
    destroy = true;
	clear_scheduled_tasks();
    timer->join();
    delete(timer);
    destroy_task_handlers();
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

const std::string MonitorMgr::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
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
			PRINT(std::cout << "timer sleep\n");
			//std::cout << "timer thread sleeping - there aren't any tasks in scheduler priority queue\n";
			cv.wait(lk);
			continue;
		}
		//std::cout << "timer thread, take the task with nearest time point\n";
		Task *tk = scheduled_tasks.top();
		PRINT(std::cout << "timer for " << tk->get_name() << "\n");
		if(cv.wait_until(lk, tk->get_absolute_time()) == std::cv_status::timeout)
		{
			//std::cout << "execute - just expired\n";
			//std::cout << "execution of tasks in thread pool\n";
			scheduled_tasks.pop();
			TaskHandler *th = get_task_handler();
			std::cout << currentDateTime() << " Th#" << th->get_id() << " execute task for " << tk->get_name() << std::endl;
			th->add_task(tk);
		}
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
	if(!destroy)
	{
		PRINT(std::cout << "add task " << tk->get_name() << std::endl);
		scheduled_tasks.push(tk);
		cv.notify_one();
	}
}

void MonitorMgr::clear_scheduled_tasks()
{
	while(scheduled_tasks.size() > 0)
		scheduled_tasks.pop();
	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
}
