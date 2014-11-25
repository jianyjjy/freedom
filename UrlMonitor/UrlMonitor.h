/*
 * UrlMonitor.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef URLMONITOR_H_
#define URLMONITOR_H_

#include "monitor_common.h"

class Task {
public:
	Task(){};
	virtual ~Task(){};
	virtual void execute() = 0;
};



class UrlMonitor : public Task
{

	std::string URI;
	std::string path;
	std::string name;

	unsigned int polling_interval;

public:
	UrlMonitor(char * uri_name);
	virtual ~UrlMonitor();
	void execute();
};

#endif /* URLMONITOR_H_ */
