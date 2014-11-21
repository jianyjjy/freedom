/*
 * MasterPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MASTERPLAYLIST_H_
#define MASTERPLAYLIST_H_

#include "playlist_common.h"
#include "PlaylistInterface.h"

class MasterPlaylist : public PlaylistInterface
{
public:
	MasterPlaylist(std::string filename);
	virtual ~MasterPlaylist();

	unsigned int get_variants_count();
};

#endif /* MASTERPLAYLIST_H_ */
