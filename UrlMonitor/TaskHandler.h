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
	std::mutex m;
	std::condition_variable cv;
	std::thread* tid;

	std::deque<Task *> tasks_to_execute;
	bool destroy;
	void wakeup();
	void execute_task();

public:
	TaskHandler();
	virtual ~TaskHandler();
	void add_task(Task *t);
};

#endif /* TASKHANDLER_H_ */
