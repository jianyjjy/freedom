/*
 * MasterPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MASTERPLAYLIST_H_
#define MASTERPLAYLIST_H_

#include "PlaylistInterface.h"


class MasterPlaylist : public PlaylistInterface
{
	std::deque<VariantsInfo *> variants;

public:
	MasterPlaylist(std::string filename);
	virtual ~MasterPlaylist();

	unsigned int get_variants_count();
	std::deque<VariantsInfo *> get_variants();
};

#endif /* MASTERPLAYLIST_H_ */
