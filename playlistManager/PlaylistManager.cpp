/*
 * PlaylistManager.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "PlaylistFactory.h"
#include "PlaylistManager.h"

PlaylistManager::PlaylistManager(char *master_playlist_name)
{
	master = NULL;
	groups.clear();
	try
	{
		PlaylistFactory * factory = PlaylistFactory::get_instance();
		master = factory->getDOM(master_playlist_name);
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


void PlaylistManager::create_groups()
{
	//ask master about variants list

	//create groups with that
}
