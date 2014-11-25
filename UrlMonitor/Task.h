/*
 * Task.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
public:
	Task(){};
	virtual ~Task(){};
	void execute() = 0;
};

#endif /* TASK_H_ */
