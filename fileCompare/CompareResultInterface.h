/*
 * CompareResultInterface.h
 *
 *  Created on: Nov 10, 2014
 *      Author: satram
 */

#include "fc_common.h"

#ifndef COMPARERESULTINTERFACE_H_
#define COMPARERESULTINTERFACE_H_

enum ResultTypes
{
	ADDED,
	DELETED,
	MODIFIED
};

class CompareResultInterface
{
protected:
	ResultTypes res_type;
	long long src_line;
	long long dst_line;
	long long changed_line;
	std::string src_str;
	std::string dst_str;

public:
	CompareResultInterface()
	{

	}
	virtual ~CompareResultInterface()
	{

	}

	virtual void add_line(std::string str){};
	virtual void add_line(std::string str1, std::string str2){};

	ResultTypes get_type()
	{
		return res_type;
	}

	virtual std::string marshall() = 0;

	long long get_src_line()
	{
		return src_line;
	}

	long long get_dst_line()
	{
		return dst_line;
	}
	std::string get_src_str()
	{
		return src_str;
	}

	std::string get_dst_str()
	{
		return dst_str;
	}
};


class AddedLine: public CompareResultInterface
{
public:
	AddedLine(long long num1, long long num2, long long num3, std::string str)
	{
		res_type = ADDED;
		src_line = num1;
		dst_line = num2;
		changed_line = num3;
		dst_str = str;
	}

	void add_line(std::string str)
	{
		dst_str += std::string("\n> ") + str;
	}

	std::string marshall()
	{
		std::ostringstream oss;
		oss << src_line << "a" << dst_line << "," << changed_line << std::endl;
		oss << "> " << dst_str << std::endl;
		return oss.str();
	}
};


class DeletedLine: public CompareResultInterface
{
public:
	DeletedLine(long long num1, long long num2, long long num3, std::string str)
	{
		res_type = ADDED;
		src_line = num1;
		changed_line = num2;
		dst_line = num3;
		src_str = str;
	}

	void add_line(std::string str)
	{
		src_str += std::string("\n< ") + str;
	}

	std::string marshall()
	{
		std::ostringstream oss;
		oss << src_line << "," << changed_line << "d" << dst_line << std::endl;
		oss << "< " << src_str << std::endl;
		return oss.str();
	}
};


class ModifiedLine: public CompareResultInterface
{
public:
	ModifiedLine(long long num1, long long num2, std::string str1, std::string str2)
	{
		res_type = ADDED;
		src_line = num1+1;
		dst_line = num2+1;
		src_str = str1;
		dst_str = str2;
	}
	void add_line(std::string str1, std::string str2)
	{
		src_str += str1;
		dst_str += str2;
	}

	std::string marshall()
	{
		std::ostringstream oss;
		oss << src_line << "c" << dst_line << std::endl;
		oss << "< " << src_str << std::endl;
		oss << "---" << std::endl;
		oss << "> " << dst_str << std::endl;
		return oss.str();
	}
};

#endif /* COMPARERESULTINTERFACE_H_ */
