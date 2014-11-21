/*
 * CompareFile.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: satram
 */

#include "CompareFile.h"
#include "CompareResultInterface.h"

CompareFile::CompareFile()
{
}

CompareFile::~CompareFile()
{
	if(results_queue.size() != 0)
	{
		for(unsigned int i = 0; i < results_queue.size(); i++)
		{
			delete(results_queue[i]);
		}
	}
}

std::string CompareFile::get_result()
{
	std::ostringstream oss;
	for(unsigned int i = 0; i < results_queue.size(); i++)
		oss << results_queue[i]->marshall();
	return oss.str();
}


void CompareFile::set_first(const char *filename)
{
	in1.open(filename);
	if(!in1.is_open())
	{
		std::ostringstream oss;
		oss << "unable to open file " << filename;
		throw std::runtime_error(oss.str());
	}
	readlines(in1, src_lines);
}


void CompareFile::set_second(const char *filename)
{
	in2.open(filename);
	if(!in2.is_open())
	{
		std::ostringstream oss;
		oss << "unable to open file " << filename;
		throw std::runtime_error(oss.str());
	}
	readlines(in2, dst_lines);
	compare();
}

void CompareFile::readlines(
		std::ifstream &in,
		std::deque<std::string> &lines)
{
	if(in.is_open())
	{
		while(!in.eof())
		{
			std::string linestr;
			std::getline(in, linestr);			//std::cout << linestr << std::endl;
			lines.push_back(linestr);
		}
	}
	else
		throw std::runtime_error("file is not yet opened\n");
}

#define DEPTH (5)

void CompareFile::compare()
{
	unsigned int i = 0;
	unsigned int j = 0;
	for(; i < src_lines.size() && j < dst_lines.size();)
	{
		if(src_lines[i].compare(dst_lines[j]) == 0)
		{
			i++; j++;
			continue;
		}
		else
		{
			unsigned int prev_size = results_queue.size();

			for(unsigned int k = 1; k < DEPTH; k++)
				if(i+k < src_lines.size() && src_lines[i+k].compare(dst_lines[j]) == 0) //A(n+1) == B(n)
				{
					CompareResultInterface *result = new DeletedLine(i+1, i+k, j, src_lines[i]);
					for(unsigned int n = 1; n < k; n++)
						result->add_line(src_lines[i+n]);
					results_queue.push_back(result);
					i = i+k+1; j++;
					break;
				}
			if(results_queue.size() > prev_size) continue;

			for(unsigned int k = 1; k < DEPTH; k++)
				if(j+k < dst_lines.size() && src_lines[i].compare(dst_lines[j+k]) == 0) //A(n) == B(n+1)
				{
					CompareResultInterface *result = new AddedLine(i, j, j+k, dst_lines[j]);
					for(unsigned int n = 1; n < k; n++)
						result->add_line(dst_lines[j+n]);
					results_queue.push_back(result);
					i++; j = j+k+1;
					break;
				}
			if(results_queue.size() > prev_size) continue;

			if(i+1 < src_lines.size() && j+1 < dst_lines.size() && src_lines[i+1].compare(dst_lines[j+1]) == 0) //A(n+1) == B(n+1)
			{
				CompareResultInterface *result = new ModifiedLine(i, j, src_lines[i], dst_lines[j]);
				results_queue.push_back(result);
				i++; j++;
			}
			if(results_queue.size() > prev_size) continue;

			i++; j++;
		}
	}
	if(j < dst_lines.size())
	{
		unsigned int rem = dst_lines.size() - j;
		CompareResultInterface *result = new AddedLine(i-1, j, j+rem, dst_lines[j]);
		for(unsigned int n = j+1; n < dst_lines.size(); n++)
			result->add_line(dst_lines[n]);
		results_queue.push_back(result);
	}
	if(i < src_lines.size())
	{
		unsigned int rem = src_lines.size() - i;
		CompareResultInterface *result = new DeletedLine(i, i+rem, j-1, src_lines[i]);
		for(unsigned int n = i+1; n < src_lines.size(); n++)
			result->add_line(src_lines[n]);
		results_queue.push_back(result);
	}


}

