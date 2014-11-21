/*
 * MasterPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MasterPlaylist.h"

MasterPlaylist::MasterPlaylist(std::string filename) : PlaylistInterface(filename)
{
	playlist_type = MASTER;
}

MasterPlaylist::~MasterPlaylist()
{

}


unsigned int MasterPlaylist::get_variants_count()
{
	return playlist.get_section_count();
}


