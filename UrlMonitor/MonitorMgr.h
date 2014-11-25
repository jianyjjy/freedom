/*
 * MonitorMgr.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef MONITORMGR_H_
#define MONITORMGR_H_

class MonitorMgr
{

	static MonitorMgr *instance;

	std::mutex tp_m;
	std::condition_variable tp_cv;
	std::deque<TaskHandler *> task_handlers;
	std::deque<TaskHandler *> available_taskhandlers;

	unsigned int thread_pool_size;

	//std::priority_queue<UrlMonitor *, std::deque<UrlMonitor *>, > timer;


	MonitorMgr();
	virtual ~MonitorMgr();

	void create_task_handler();
	TaskHandler * get_task_handler();
    void destroy_task_handlers();

public:

	static MonitorMgr* get_instance()
	{
		if(instance == NULL)
			instance = new MonitorMgr();
		return instance;
	}
	void register_free_task_handler(TaskHandler *th);

};

#endif /* MONITORMGR_H_ */
