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
	unsigned int session_id;
	std::deque<VariantPlaylist *> variants;

public:

	RenditionGroups(unsigned int id);
	virtual ~RenditionGroups();
	void add_variant(VariantsInfo *variant_info);
	void marshall();

	unsigned int get_group_id()
	{
		return session_id;
	}



};

#endif /* RENDITIONGROUPS_H_ */
