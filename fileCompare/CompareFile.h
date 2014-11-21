/*
 * CompareFile.h
 *
 *  Created on: Nov 10, 2014
 *      Author: satram
 */


#include "fc_common.h"

#ifndef COMPAREFILE_H_
#define COMPAREFILE_H_

#define MAX_LINE_SIZE	(1024)

class CompareFile
{
	std::ifstream in1;
	std::ifstream in2;
	std::deque<CompareResultInterface *> results_queue;
	void compare();

	//file entries
	std::deque<std::string> src_lines;
	std::deque<std::string> dst_lines;

	void readlines(
			std::ifstream &in,
			std::deque<std::string> &lines);

public:
	CompareFile();
	virtual ~CompareFile();
	void set_first(const char *filename);
	void set_second(const char *filename);
	std::string get_result();
};

#endif /* COMPAREFILE_H_ */
