/*
 * VariantPlaylist.h
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#ifndef VARIANTPLAYLIST_H_
#define VARIANTPLAYLIST_H_

class MonitorMgr;

#include "PlaylistInterface.h"
#include "CompareResultInterface.h"

class VariantPlaylist {

	std::string media_URI;
	std::string media_uri_path;
	std::string media_local_uri;

	std::string iframe_URI;
	std::string iframe_uri_path;
	std::string iframe_local_uri;

	PlaylistInterface *media;
	PlaylistInterface *iframe;

	MonitorMgr *mgr;

	void my_replace(std::string &original, const char *search, const char *replace);
	void download_uri(std::string &URI, std::string &path, std::string &local_uri);
	void http_get_file(const char *url, const char *filename);

public:
	VariantPlaylist(VariantsInfo *variants_info);
	virtual ~VariantPlaylist();
	void marshall();
	void update_playlist(std::deque<CompareResultInterface*> compare_result, PlaylistInterface *playlist);
};

#endif /* VARIANTPLAYLIST_H_ */
