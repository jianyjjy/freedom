//ModifiedLine.cpp

#include "ModifiedLine.h"

#include <iostream>
#include <sstream>
using namespace std;

ModifiedLine::ModifiedLine(long long src_index, long long dst_index, string src_str, string dst_str)
	: CompareResultInterface(ResultTypes::ADDED)
{
	src_line_index = src_index;
	dst_line_index = dst_index;
	if( !src_str.empty() )	src_lines.push_back(src_str);
	if( !dst_str.empty() )	dst_lines.push_back(dst_str);
}

void ModifiedLine::add_line(string src_str, string dst_str)
{
	if( !src_str.empty() )		src_lines.push_back(src_str);
	if( !dst_str.empty() )		dst_lines.push_back(dst_str);
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
