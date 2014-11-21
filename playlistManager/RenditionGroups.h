/*
 * RenditionGroups.h
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#ifndef RENDITIONGROUPS_H_
#define RENDITIONGROUPS_H_

#include "VariantPlaylist.h"

class RenditionGroups
{
	enum GROUPS_E
	{
		VIDEO,
		AUDIO,
		SUBTITLES,
		CLOSED_CAPTIONS
	};


	GROUPS_E type;
	unsigned int sessionId;
	std::deque<VariantPlaylist *> variants;

public:

	RenditionGroups();
	virtual ~RenditionGroups();
	void marshall();



};

#endif /* RENDITIONGROUPS_H_ */
