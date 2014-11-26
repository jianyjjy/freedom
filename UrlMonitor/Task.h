/*
 * Task.h
 *
 *  Created on: Nov 25, 2014
 *      Author: satram
 */

#ifndef TASK_H_
#define TASK_H_

class Task
{
public:
	Task(){};
	virtual ~Task(){};
	bool operator()(Task *lhs, Task *rhs) const
	{
		return(lhs->get_absolute_time()>rhs->get_absolute_time());
	}
	virtual void execute(TaskHandler *th) = 0;
	virtual std::chrono::time_point<std::chrono::system_clock> get_absolute_time() = 0;
	virtual void schedule_task() = 0;
	virtual std::string get_name() = 0;
};



#endif /* TASK_H_ */
