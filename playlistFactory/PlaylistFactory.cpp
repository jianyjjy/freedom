/*
 * PlaylistParser.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: satram
 */

#include "common.h"
#include "MasterPlaylist.h"
#include "MediaPlaylist.h"
#include "IFramePlaylist.h"
#include "PlaylistFactory.h"

PlaylistFactory *PlaylistFactory::instance = NULL;
unsigned int PlaylistFactory::count = 0;


#define PRINT(X)	//X


PlaylistFactory::PlaylistFactory()
{
	header_tags.insert("#EXTM3U");
	header_tags.insert("#EXT-X-VERSION");
	header_tags.insert("#EXT-X-INDEPENDENT-SEGMENTS");
	header_tags.insert("#EXT-X-START");

	master_segment_tags.insert("#EXT-X-STREAM-INF");
	master_segment_tags.insert("#EXT-X-I-FRAME-STREAM-INF");
	master_segment_tags.insert("#EXT-X-MEDIA");
	master_segment_tags.insert("#EXT-X-SESSION-DATA");

	media_header_tags.insert("#EXT-X-TARGETDURATION");
	media_header_tags.insert("#EXT-X-MEDIA-SEQUENCE");
	media_header_tags.insert("#EXT-X-DISCONTINUITY-SEQUENCE");
	media_header_tags.insert("#EXT-X-PLAYLIST-TYPE");

	media_segment_tags.insert("#EXTINF");
	media_segment_tags.insert("#EXT-X-BYTERANGE");
	media_segment_tags.insert("#EXT-X-DISCONTINUITY");
	media_segment_tags.insert("#EXT-X-KEY");
	media_segment_tags.insert("#EXT-X-MAP");
	media_segment_tags.insert("#EXT-X-PROGRAM-DATE-TIME");

	iframe_header_tags.insert("#EXT-X-I-FRAMES-ONLY");

	footer_tags.insert("#EXT-X-ENDLIST");

}

PlaylistFactory::~PlaylistFactory()
{

}


PlaylistInterface *PlaylistFactory::getDOM(char *str)
{
	playlist = NULL;
	state = BEGIN;
	segment_start_key.clear();
	filename = std::string(str);
	infile.open(filename);
	if(!infile.is_open())
		throw std::runtime_error("unable to open the file");
	else
	{
		while(!infile.eof())
		{
			std::string src;
			std::getline(infile, src);
			lines.push_back(src);
		}
	}
	process();
	return playlist;
}

/*
 * find playlist type and
 * create appropriate playlist object
 */
void PlaylistFactory::identify_playlist_type()
{
	for(unsigned int i = 0; i < lines.size(); i++)
	{
		std::string tag = lines[i].substr(0, lines[i].find_first_of(":"));
		PRINT(std::cout << tag << std::endl);
		if(!tag.empty())
		{
			if(master_segment_tags.find(tag) != master_segment_tags.end())
			{
				std::cout << "create master DOM" << std::endl;
				playlist = new MasterPlaylist(filename);
				header = header_tags;
				segment = master_segment_tags;
				break;
			}
			else if(media_header_tags.find(tag) != media_header_tags.end())
			{
				std::cout << "create media DOM" << std::endl;
				playlist = new MediaPlaylist(filename);
				header = media_header_tags;
				segment = media_segment_tags;
				footer = footer_tags;
				break;
			}
			else if(iframe_header_tags.find(tag) != iframe_header_tags.end())
			{
				std::cout << "create iframe DOM" << std::endl;
				playlist = new IFramePlaylist(filename);
				header = iframe_header_tags;
				segment = media_segment_tags;
				footer = footer_tags;
				break;
			}
		}
	}
}

STATE_E PlaylistFactory::get_new_state(std::string & tag)
{
	STATE_E new_state = INVALID;
	if(segment.find(tag) != segment.end())
	{
		 new_state = SEGMENT;
		 if(segment_start_key.empty())
		 {
			 if(segment.find(tag) != segment.end())
			 {
				 segment_start_key = tag;
				 new_state = NEW_SEGMENT;
			 }
		 }
		 else if(tag.compare(segment_start_key) == 0)
			 new_state = NEW_SEGMENT;

	}
	else if(header.find(tag) != header.end())
	 new_state = HEADER;
	else if(footer.find(tag) != footer.end())
	 new_state = FOOTER;
	PRINT(std::cout << "state is " << new_state << " for " << tag << std::endl;)
	return new_state;
}

bool PlaylistFactory::update_state(STATE_E new_state, std::string &tag)
{
	bool state_change = false;
	try
	{
		switch(state)
		{
		case BEGIN:
			break;
		case NEW_SEGMENT:
			if(new_state == NEW_SEGMENT) state_change = true;
			break;
		case HEADER:
			if(new_state == NEW_SEGMENT) state_change = true;
			break;
		case SEGMENT:
			if(new_state == NEW_SEGMENT) state_change = true;
			break;
		case FOOTER:
			if(new_state != state) throw std::runtime_error("footer - invalid state transition");
			break;
		default:
			throw std::runtime_error("Invalid state");
			break;
		}
		PRINT(if(state_change) std::cout << "state change: " << state << " ... " << new_state << std::endl);
		state = new_state;
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
	return state_change;
}



void PlaylistFactory::process()
{
	identify_playlist_type();


	//add sections of data to the playlist
	std::deque<std::string> section;
	for(unsigned int i = 0; i < lines.size(); i++)
	{
		std::string tag = lines[i].substr(0, lines[i].find_first_of(":"));

		STATE_E new_state = get_new_state(tag);

		bool state_change = false;
		if(new_state != INVALID)
			state_change = update_state(new_state, tag);

		if(state_change)
		{
			 if(state == SEGMENT || state == NEW_SEGMENT)
				 playlist->add_section(section);
			 else if(state == HEADER)
				 playlist->add_header(section);
			 else if(state == FOOTER)
				 playlist->add_footer(section);
			section.clear();
			section.push_back(lines[i]);
			PRINT(std::cout << "queue refresh \n");
		}
		else
		{
			PRINT(std::cout << "queue add: " << lines[i] << std::endl);
			if(!tag.empty())
				section.push_back(lines[i]);
		}
	}
	if(section.size() > 0)
		playlist->add_section(section);

}

#undef PRINT
