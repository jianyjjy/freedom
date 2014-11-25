/*
 * UrlMonitor.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef URLMONITOR_H_
#define URLMONITOR_H_

class UrlMonitor {

	std::string URI;
	std::string path;
	std::string name;

	unsigned int polling_interval;

public:
	UrlMonitor(char * uri_name);
	virtual ~UrlMonitor();
};

#endif /* URLMONITOR_H_ */
