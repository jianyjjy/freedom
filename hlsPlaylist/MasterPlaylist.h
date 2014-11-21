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
	MasterPlaylist();
	virtual ~MasterPlaylist();
};

#endif /* MASTERPLAYLIST_H_ */
