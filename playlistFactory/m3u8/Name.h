/*
 * Name.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef NAME_H_
#define NAME_H_

#include "m3u8/Common.h"

class NameBase
{
public:
	NameBase(){};
	virtual ~NameBase(){};
	virtual std::string asString() = 0;
	virtual unsigned int asUInt() = 0;
	virtual int asInt() = 0;
	virtual long long asLongLong() = 0;
	virtual double asDouble() = 0;
	virtual bool asBool() = 0;
	virtual bool empty()
	{
		return true;
	}
};


template<class T>
class Name : public NameBase
{
	T id;

public:
	Name(T name): id(name){};
    virtual ~Name() {};

	std::string asString()
	{
		std::ostringstream oss;
		oss << id;
		return oss.str();
	}
	virtual unsigned int asUInt()
	{
		return stoul(id);
	}
	virtual int asInt()
	{
		return stoi(id);
	}
	virtual long long asLongLong()
	{
		return stoll(id);
	}
	virtual double asDouble()
	{
		return stod(id);
	}
	virtual bool asBool()
	{
		if(id.compare("YES") == 0)
			return true;
		else //if(id.compare("NO") == 0)
			return false;
	}
	bool empty()
	{
		return false;
	}
};

#endif /* NAME_H_ */
