//AddedLine.h

#ifndef ADDED_LINE_H
#define ADDED_LINE_H

#include "CompareResultInterface.h"

class AddedLine : public CompareResultInterface
{
public :
	AddedLine(long long src_index, long long dst_index);

	void add_dst_str(string str);
	string marshall(void);
};

#endif	//ADDED_LINE_H
