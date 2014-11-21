/*
 * MediaPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MediaPlaylist.h"

MediaPlaylist::MediaPlaylist(std::string filename) : PlaylistInterface(filename)
{
	playlist_type = MEDIA;
	group = VIDEO;
}

MediaPlaylist::~MediaPlaylist() {
	// TODO Auto-generated destructor stub
}

