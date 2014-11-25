/*
 * MonitorMgr.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef MONITORMGR_H_
#define MONITORMGR_H_

#include "Task.h"

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=true)
    {reverse=revparam;}
  bool operator() (Task *lhs, Task *rhs) const
  {
    if (reverse) return (lhs->get_absolute_time()>rhs->get_absolute_time());
    else return (lhs->get_absolute_time() < rhs->get_absolute_time());
  }
};

typedef std::priority_queue<Task*, std::deque<Task *>, mycomparison> mypq_type;

class MonitorMgr
{

	static MonitorMgr *instance;

	std::mutex tp_m;
	std::condition_variable tp_cv;
	std::deque<TaskHandler *> task_handlers;
	std::deque<TaskHandler *> available_taskhandlers;

	unsigned int thread_pool_size;
	unsigned int task_handler_count;
	mypq_type scheduled_tasks;
	//std::priority_queue<Task*, std::deque<Task *>> scheduled_tasks;
	std::deque<Task *> urlMonitor;

	MonitorMgr();
	virtual ~MonitorMgr();

	void create_task_handler();
	TaskHandler * get_task_handler();
    void destroy_task_handlers();

    void timer_thread();
    std::thread *timer;
    bool destroy;
    std::mutex m;
    std::condition_variable cv;

public:

	static MonitorMgr* get_instance()
	{
		if(instance == NULL)
			instance = new MonitorMgr();
		return instance;
	}
	void register_free_task_handler(TaskHandler *th);
	void create_url_monitor(std::string playlist_name, unsigned int poll_interval);
	void remove_all_url_monitor();
	void remove_url_monitor(char * playlist_name);
	void add_task(Task *tk);
};

#endif /* MONITORMGR_H_ */
