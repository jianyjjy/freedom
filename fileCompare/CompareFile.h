//CompareFile.h

#ifndef COMPARE_FILE_H
#define COMPARE_FILE_H

#include <string>
#include <deque>
using namespace std;


class CompareResultInterface;

struct CommonSubSeq;

class CompareFile
{
	string first_file;
	string second_file;

	CommonSubSeq* longest_common_subseq(deque<string> data1, int start1, int end1, deque<string>data2, int start2, int end2);
	void find_common_subseqs(deque<string> data1, int start1, int end1, deque<string> data2, int start2, int end2, deque<CommonSubSeq*>* pCommonSeqs);

public :
	CompareFile() 	{ first_file = "";	second_file = ""; }
	~CompareFile()	{ }

	void set_first(string filename)		{ first_file = filename; }
	void set_second(string filename)	{ second_file = filename; }

	deque<CompareResultInterface*> compare(void);
};

#endif	//COMPARE_FILE_H
