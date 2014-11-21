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

public:
	enum GROUPS_E
	{
		VIDEO,
		AUDIO,
		SUBTITLES,
		CLOSED_CAPTIONS
	};

	RenditionGroups();
	virtual ~RenditionGroups();


private:
	GROUPS_E type;
	unsigned int sessionId;
	std::deque<VariantPlaylist *> variants;

};

#endif /* RENDITIONGROUPS_H_ */
