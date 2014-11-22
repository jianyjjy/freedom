/*
 * MasterPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MasterPlaylist.h"
#include "VariantsInfo.h"

MasterPlaylist::MasterPlaylist(std::string filename) : PlaylistInterface(filename)
{
	playlist_type = MASTER;
	variants.clear();
}


MasterPlaylist::~MasterPlaylist()
{
	for(unsigned int i = 0; i < variants.size(); i++)
		delete(variants[i]);
	variants.clear();
}


unsigned int MasterPlaylist::get_variants_count()
{
	unsigned int count = 0;
	std::deque<std::string> names = playlist.get_section_names();
	for(unsigned int i = 0; i < names.size(); i++)
	{
		std::cout << names[i] << std::endl;
		if(names[i].compare("header") == 0 || names[i].compare("footer") == 0)
			continue;
		count++;
	}
	return count;
}


std::deque<VariantsInfo *> MasterPlaylist::get_variants()
{
	std::deque<std::string> names = playlist.get_section_names();
	for(unsigned int i = 0; i < names.size(); i++)
	{
		if(names[i].compare("header") == 0 || names[i].compare("footer") == 0)
			continue;
		Section& section = playlist.get_section(names[i]);
		VariantsInfo *new_variant = new VariantsInfo(&section);
		variants.push_back(new_variant);
	}
	return variants;
}
