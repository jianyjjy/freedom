/*
 * MediaPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MediaPlaylist.h"
#include "m3u8/Playlist.h"
#include "m3u8/Section.h"
#include "m3u8/Tag.h"


MediaPlaylist::MediaPlaylist(std::string& url_path, std::string& filename) : PlaylistInterface(url_path, filename)
{
	playlist_type = MEDIA;
	group = VIDEO;
}

MediaPlaylist::~MediaPlaylist()
{

}

unsigned int MediaPlaylist::get_target_duration()
{
	if(Section *header = playlist.get_section("header"))
	{
		if(Tag *tag = header->get_tag("#EXT-X-TARGETDURATION"))
		{
			unsigned int target_duration = tag->properties[0]->get_name()->asUInt();
			return target_duration;
		}
		else
			throw std::runtime_error("#EXT-X-TARGETDURATION tag is not found");
	}
	else
		throw std::runtime_error("media playlist don't have header section");
}
