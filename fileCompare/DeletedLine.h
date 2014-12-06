//DeletedLine.h

#ifndef DELETED_LINE_H
#define DELETED_LINE_H

#include "CompareResultInterface.h"

class DeletedLine : public CompareResultInterface
{
public :
	DeletedLine(long long src_index, long long dst_index);

	void add_src_str(string str);
	string marshall(void);
};

#endif	//DELETED_LINE_H
