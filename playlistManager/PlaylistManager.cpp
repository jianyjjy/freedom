/*
 * PlaylistManager.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "PlaylistFactory.h"
#include "PlaylistManager.h"
#include "VariantsInfo.h"

PlaylistManager::PlaylistManager(char *master_URI)
{
	master = NULL;
	groups.clear();
	try
	{
		PlaylistFactory * factory = PlaylistFactory::get_instance();
		master = factory->getDOM(master_URI);
		create_groups();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}


}

PlaylistManager::~PlaylistManager()
{
	if(master)
	{
		delete(master);
		master = NULL;
	}

	for(unsigned int i = 0; i < groups.size(); i++)
		delete(groups[i]);
	groups.clear();
}

RenditionGroups * PlaylistManager::get_group(unsigned int id)
{
	for(unsigned int i = 0; i < groups.size(); i++)
	{
		if(groups[i]->get_group_id() == id)
			return groups[i];
	}
	RenditionGroups *new_group = new RenditionGroups(id);
	groups.push_back(new_group);
	return new_group;
}



void PlaylistManager::create_groups()
{
	//get num variants
	unsigned int variants_count = master->get_variants_count();
	if(variants_count == 0)
		throw std::runtime_error("number of variants in master playlist can't be zero");

	std::cout << "variants-count " << variants_count << std::endl;

	//ask master about variants list
	std::deque<VariantsInfo *> variants_info = master->get_variants();
	std::cout << "variants_info size " << variants_info.size() << std::endl;

	//create groups with that
	for(unsigned int i = 0; i < variants_info.size(); i++)
	{
		RenditionGroups *group = get_group(variants_info[i]->get_group_id());
		group->add_variant(variants_info[i]);
	}
}

void PlaylistManager::marshall()
{
	std::cout << "--------------------------------------------------\n";
	std::cout << "master playlist " << std::endl;
	std::cout << master->marshall();

	for(unsigned int i = 0; i < groups.size(); i++)
		groups[i]->marshall();
}
