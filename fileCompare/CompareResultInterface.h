//CompareResultInterface.h

#ifndef COMPARE_RESULT_INTERFACE_H
#define COMPARE_RESULT_INTERFACE_H

#include <string>
#include <deque>
using namespace std;

enum ResultTypes {ADDED, DELETED, MODIFIED};

class CompareResultInterface
{
	ResultTypes res_type;

protected:
	long long src_line_index;
	long long dst_line_index;
	deque<string> src_lines;	//DELETED or MODIFIED or MATCHING LINES COUNT
	deque<string> dst_lines;	//ADDED or MODIFIED or MATCHING LINES COUNT


	CompareResultInterface()	{ }
public:
	CompareResultInterface(ResultTypes type)	{ res_type = type; }
	~CompareResultInterface()	{ }

	ResultTypes get_type()	{ return res_type; }

	virtual void add_line(string str) { };
	virtual void add_line(string str1, string str2) { };

	virtual string marshall(void) = 0;

	long long get_src_line(void)	{ return src_line_index+1; } 
	long long get_dst_line(void)	{ return dst_line_index+1; }
	deque<string> get_src_str(void)	{ return src_lines; }
	deque<string> get_dst_str(void)	{ return dst_lines; }
};

#endif	//COMPARE_RESULT_INTERFACE_H
