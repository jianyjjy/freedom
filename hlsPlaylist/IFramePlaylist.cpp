/*
 * IFramePlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "IFramePlaylist.h"

IFramePlaylist::IFramePlaylist(std::string& url_path, std::string& filename) : PlaylistInterface(url_path, filename)
{
	playlist_type = IFRAME;
	group = VIDEO;
}

IFramePlaylist::~IFramePlaylist() {
	// TODO Auto-generated destructor stub
}



