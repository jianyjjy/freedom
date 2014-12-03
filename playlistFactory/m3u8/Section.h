/*
 * Section.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef SECTION_H_
#define SECTION_H_

#include "m3u8/Tag.h"

class Section {
	std::deque<Tag *> tags;

	std::string path;
	std::string locator;
	std::string id;

public:
	Section(std::string name):id(name){};
	virtual ~Section()
	{
		for(unsigned int i = 0; i < tags.size(); i++)
			delete(tags[i]);
	};

	std::string get_name()
	{
		return id;
	};

	std::string marshall()
	{
		std::ostringstream oss;
		oss.str("");
		for(auto it = tags.begin(), ite = tags.end(); it != ite; it++)
			oss << (*it)->marshall() << "\n";
		if(!path.empty())
			oss << path;
		if(!path.empty() && path.find_last_of("/") != (path.size()-1))
			oss << "/";
		if(!locator.empty())
			oss << locator << "\n";
		oss << "\n";
		return oss.str();
	};
	std::string get_URI()
	{
		std::ostringstream oss;
		oss << path << locator;
		return oss.str();
	}
	void set_path(const char *p)
	{
		path = std::string(p);
	};
	void set_path(std::string &p)
	{
		path = p;
	};
	void set_locator(const char *l)
	{
		locator = std::string(l);
	};
	void set_locator(std::string l)
	{
		locator = l;
	};
	void add_tag(Tag *t){
		tags.push_back(t);
	};

	template<typename T>
	void add_tag(T str)
	{
		Tag *t = new Tag(str);
		tags.push_back(t);
	};

	template<typename T1, typename T2>
	void add_tag(T1 str, T2 name)
	{
		Tag *t = new Tag(str);
		t->add_property(name);
		tags.push_back(t);
	};
	template<typename T1, typename T2, typename T3>
	void add_tag(T1 str, T2 name, T3 val)
	{
		Tag *t = new Tag(str);
		t->add_property(name, val);
		tags.push_back(t);
	};


	template<typename T1, typename T2>
	void modify_tag(T1 str, T2 name)
	{
		Tag *t = new Tag(str);
		t->add_property(name);
		for(auto it = tags.begin(), ite = tags.end(); it != ite; it++)
		{
			if((*it)->get_name() == t->get_name())
			{
				delete(*it);
				it = tags.erase(it);
				tags.insert(it, t);
				break;
			}
		}
	};

	template<typename T1, typename T2, typename T3>
	void modify_tag(T1 str, T2 name, T3 val)
	{
		Tag *t = new Tag(str);
		t->add_property(name, val);
		for(auto it = tags.begin(), ite = tags.end(); it != ite; it++)
			if((*it)->get_name() == t->get_name())
			{
				delete(*it);
				it = tags.erase(it);
				tags.insert(it, t);
				break;
			}

	};

	Tag *get_tag(std::string name)
	{
		for(unsigned int i = 0; i < tags.size(); i++)
		{
			if(tags[i]->get_name() == name)
				return tags[i];
		}
		return NULL;
	}

	friend class VariantsInfo;
};

#endif /* SECTION_H_ */
