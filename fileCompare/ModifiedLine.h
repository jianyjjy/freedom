//ModifiedLine.h

#ifndef MODIFIED_LINE_H
#define MODIFIED_LINE_H

#include "CompareResultInterface.h"

class ModifiedLine : public CompareResultInterface
{
public :
	ModifiedLine(long long src_index, long long dst_index);

	void add_src_str(string str);
	void add_dst_str(string str);
	string marshall(void);
};

#endif	//MODIFIED_LINE_H
