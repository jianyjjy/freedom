/*
 * Playlist.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "m3u8/Section.h"


class Playlist {
	std::list<Section> section_list;
	std::ostringstream oss;
	std::deque<std::string> names;

public:
	Playlist(){};
	virtual ~Playlist(){};

	void add_section(Section &s)
	{
		section_list.push_back(s);
	}

	std::string marshall()
	{
		oss.str("");
		for(auto it = section_list.begin(), ite = section_list.end(); it != ite; it++)
			oss << it->marshall();
		return oss.str();

	}
	Section & get_section(std::string name)
	{
		for(auto it = section_list.begin(), ite = section_list.end(); it != ite; it++)
		{
			if(it->get_name() == name)
				return (*it);
		}
		throw std::runtime_error("requested section not found");
	}

	void delete_section(std::string name)
	{
		for(auto it = section_list.begin(), ite = section_list.end(); it != ite; it++)
		{
			if(it->get_name() == name){
				section_list.erase(it);
				break;
			}
		}
	}

	void modify_section(Section &s)
	{
		for(auto it = section_list.begin(), ite = section_list.end(); it != ite; it++)
		{
			if(it->get_name() == s.get_name()){
				it = section_list.erase(it);
				section_list.insert(it, s);
				break;
			}
		}
	}

	unsigned int get_section_count()
	{
		return section_list.size();
	}

	std::deque<std::string>& get_section_names()
	{
		names.clear();
		for(auto it = section_list.begin(), ite = section_list.end(); it != ite; it++)
			names.push_back(it->get_name());
		return names;
	}
};

#endif /* PLAYLIST_H_ */
