//ModifiedLine.cpp

#include "ModifiedLine.h"

#include <iostream>
#include <sstream>
using namespace std;

ModifiedLine::ModifiedLine(long long src_index, long long dst_index)
	: CompareResultInterface(ResultTypes::ADDED)
{
	src_line_index = src_index;
	dst_line_index = dst_index;
}

void ModifiedLine::add_src_str(string str)
{
	src_lines.push_back(str);
}

void ModifiedLine::add_dst_str(string str)
{
	dst_lines.push_back(str);
}

string ModifiedLine::marshall(void)
{
	stringstream ss;
	ss << (src_line_index+1);
        if( src_lines.size() > 1 ) ss << "," << (src_line_index+src_lines.size());
        ss << "c" << (dst_line_index+1);
        if( dst_lines.size() > 1 ) ss << "," << (dst_line_index+dst_lines.size());
        ss << endl;

        for( auto str : src_lines )
		ss << "< " << str << endl;
	ss << "---" << endl;
        for( auto str : dst_lines )
		ss << "> " << str << endl;

	return ss.str();
}
