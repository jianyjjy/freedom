/*
 * TaskHandler.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef TASKHANDLER_H_
#define TASKHANDLER_H_

#include "monitor_common.h"

class TaskHandler
{
	unsigned int id;
	std::mutex m;
	std::condition_variable cv;
	std::thread* tid;
	MonitorMgr *thread_pool_mgr;

	std::deque<Task *> tasks_to_execute;
	bool destroy;
	void wakeup();
	void execute_task();

public:
	TaskHandler(MonitorMgr *mgr, unsigned int count);
	virtual ~TaskHandler();
	void add_task(Task *t);
	unsigned int get_id()
	{
		return id;
	}
};

#endif /* TASKHANDLER_H_ */
