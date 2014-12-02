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
#include "HTTPGet.h"

PlaylistManager::PlaylistManager(char *mstr_URI)
{
	master = NULL;
	groups.clear();
	master_URI = std::string(mstr_URI);
	try
	{
		download_uri();
		PlaylistFactory * factory = PlaylistFactory::get_instance();
		master = factory->getDOM(master_uri_path.c_str(), master_local_uri.c_str());
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

void PlaylistManager::my_replace(std::string &original, const char *search, const char *replace)
{
	size_t pos = 0;
	while((pos = original.find(search, pos)) != std::string::npos)
	{
		original.replace(pos, 1, replace);
		pos++;
	}
}

void PlaylistManager::download_uri()
{
	size_t offset = master_URI.find_last_of("/");
	if(offset != std::string::npos)
	{
		master_uri_path = master_URI.substr(0, offset+1);
		master_local_uri = master_URI;
		my_replace(master_local_uri, "/", "_");
	}
	else
	{
		master_uri_path.clear();
		master_local_uri = master_URI;
	}
	if(master_URI.find("http") != std::string::npos)
	{
		HTTPGet get;
		get.http_get_file(master_URI.c_str(), master_local_uri.c_str());
	}
	else
		master_local_uri = master_URI;
}

