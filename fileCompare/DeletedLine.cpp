//DeletedLine.cpp

#include "DeletedLine.h"

#include <iostream>
#include <sstream>
using namespace std;


DeletedLine::DeletedLine(long long src_index, long long dst_index, long long num3, string str)
	: CompareResultInterface(ResultTypes::DELETED)
{
	src_line_index = src_index;
	dst_line_index = dst_index;
	if( !str.empty() )	src_lines.push_back(str);
}

void DeletedLine::add_line(string str)
{
        src_lines.push_back(str);
}

string DeletedLine::marshall(void)
{
	stringstream ss;
	ss << (src_line_index+1);
        if( src_lines.size() > 1 ) ss << "," << (src_line_index+src_lines.size());
        ss << "d" << (dst_line_index+1) << endl;

        for( auto str : src_lines )
                ss << "< " << str << endl;

	return ss.str();
}
