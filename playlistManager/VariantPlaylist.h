/*
 * VariantPlaylist.h
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#ifndef VARIANTPLAYLIST_H_
#define VARIANTPLAYLIST_H_

#include "PlaylistInterface.h"

class VariantPlaylist {

	PlaylistInterface *media;
	PlaylistInterface *iframe;

public:
	VariantPlaylist(VariantsInfo *variants_info);
	virtual ~VariantPlaylist();
	void marshall();
};

#endif /* VARIANTPLAYLIST_H_ */
