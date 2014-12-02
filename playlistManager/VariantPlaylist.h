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

	std::string media_URI;
	std::string media_uri_path;
	std::string media_local_uri;

	std::string iframe_URI;
	std::string iframe_uri_path;
	std::string iframe_local_uri;

	PlaylistInterface *media;
	PlaylistInterface *iframe;

	void my_replace(std::string &original, const char *search, const char *replace);
	void download_uri(std::string &URI, std::string &path, std::string &local_uri);

public:
	VariantPlaylist(VariantsInfo *variants_info);
	virtual ~VariantPlaylist();
	void marshall();
};

#endif /* VARIANTPLAYLIST_H_ */
