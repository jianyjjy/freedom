//ModifiedLine.h

#ifndef MODIFIED_LINE_H
#define MODIFIED_LINE_H

#include "CompareResultInterface.h"

class ModifiedLine : public CompareResultInterface
{
public :
	ModifiedLine(long long src_index, long long dst_index, string src_str, string dst_str);

	void add_line(string src_str, string dst_str);
	string marshall(void);
};

#endif	//MODIFIED_LINE_H
