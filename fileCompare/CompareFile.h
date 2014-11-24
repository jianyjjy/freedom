//CompareFile.h

#ifndef COMPARE_FILE_H
#define COMPARE_FILE_H

#include <string>
#include <deque>
using namespace std;


class CompareResultInterface;

class CompareFile
{
	string first_file;
	string second_file;

public :
	CompareFile() 	{ first_file = "";	second_file = ""; }
	~CompareFile()	{ }

	void set_first(string filename)		{ first_file = filename; }
	void set_second(string filename)	{ second_file = filename; }

	deque<CompareResultInterface*> get_result(void);
};

#endif	//COMPARE_FILE_H
