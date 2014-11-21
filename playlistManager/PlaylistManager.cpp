/*
 * PlaylistManager.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "PlaylistManager.h"

PlaylistManager::PlaylistManager(char *master_playlist_name)
{
	master = NULL;
	groups.clear();

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
