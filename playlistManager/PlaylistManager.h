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


	std::string master_URI;
	std::string master_uri_path;
	std::string master_local_uri;


	void create_groups();
	RenditionGroups * get_group(unsigned int id);
	void my_replace(std::string &original, const char *search, const char *replace);
	void download_uri();

public:
	PlaylistManager(char *master_URI);
	virtual ~PlaylistManager();
	void marshall();
};

#endif /* PLAYLISTMANAGER_H_ */
