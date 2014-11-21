/*
 * PlaylistManager.h
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#ifndef PLAYLISTMANAGER_H_
#define PLAYLISTMANAGER_H_

#include "PlaylistInterface.h"
#include "RenditionGroups.h"

class PlaylistManager {

	PlaylistInterface* master;
	std::deque<RenditionGroups *> groups;

	void create_groups();

public:
	PlaylistManager(char *master_playlist_name);
	virtual ~PlaylistManager();
	void marshall();
};

#endif /* PLAYLISTMANAGER_H_ */
