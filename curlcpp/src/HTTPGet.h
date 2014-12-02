/*
 * HTTPGet.h
 *
 *  Created on: Dec 1, 2014
 *      Author: satram
 */

#ifndef HTTPGET_H_
#define HTTPGET_H_

class HTTPGet {

public:
	HTTPGet();
	virtual ~HTTPGet();
	void http_get_file(const char *url, const char *filename);
};

#endif /* HTTPGET_H_ */
