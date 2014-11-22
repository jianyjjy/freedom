/*
 * PlaylistParser.h
 *
 *  Created on: Nov 13, 2014
 *      Author: satram
 */

#ifndef PLAYLISTPARSER_H_
#define PLAYLISTPARSER_H_

#include "PlaylistInterface.h"

enum STATE_E
{
	INVALID = -1,
	BEGIN,
	HEADER,
	NEW_SEGMENT,
	SEGMENT,
	FOOTER
};



class PlaylistFactory {

	static PlaylistFactory *instance;
	static unsigned int count;

	std::string filename;
	std::ifstream infile;
	PlaylistInterface *playlist;

	std::set<std::string> header_tags;
	std::set<std::string> master_segment_tags;
	std::set<std::string> media_header_tags;
	std::set<std::string> media_segment_tags;
	std::set<std::string> iframe_header_tags;
	std::set<std::string> footer_tags;

	std::deque<std::string> lines;

	std::set<std::string> header;
	std::set<std::string> segment;
	std::set<std::string> footer;

	void process();
	PlaylistFactory();
	virtual ~PlaylistFactory();
	void identify_playlist_type();
	bool update_state(STATE_E new_state, std::string &tag);
	STATE_E get_new_state(std::string & tag);

	STATE_E state;
	std::string segment_start_key;

public:

	static PlaylistFactory * get_instance()
	{
		if(instance == NULL)
		{
			instance = new PlaylistFactory();
		}
		count++;
		return instance;
	}

	void remove_instance()
	{
		count--;
		if(count == 0)
			delete (instance);
	}
	PlaylistInterface *getDOM(char *str);
	PlaylistInterface *getDOM(const char *str)
	{
		return getDOM((char *)str);
	}
};

#endif /* PLAYLISTPARSER_H_ */
