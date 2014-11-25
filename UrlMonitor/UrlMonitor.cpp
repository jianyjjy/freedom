/*
 * UrlMonitor.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */
#include "common.h"
#include "UrlMonitor.h"

UrlMonitor::UrlMonitor(char * uri_name)
{
	URI = std::string(uri_name);
	size_t path_offset = URI.find_last_of("/");
	if(path_offset != std::string::npos)
	{
		path = URI.substr(0, path_offset+1);
		name = URI.substr(path_offset+1, URI.size());
	}
	polling_interval = 3;
}

UrlMonitor::~UrlMonitor()
{

}
