/*
 * MediaPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MEDIAPLAYLIST_H_
#define MEDIAPLAYLIST_H_

#include "PlaylistInterface.h"


class MediaPlaylist : public PlaylistInterface
{
	unsigned int sequence_number;
	unsigned int node_count;
public:
	MediaPlaylist(std::string& url_path, std::string& filename);
	virtual ~MediaPlaylist();
};

#endif /* MEDIAPLAYLIST_H_ */
