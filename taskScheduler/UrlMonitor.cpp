/*
 * UrlMonitor.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */
#include "common.h"
#include "TaskHandler.h"
#include "MonitorMgr.h"

#include "CompareFile.h"
#include "CompareResultInterface.h"
#include "VariantPlaylist.h"
#include "HTTPGet.h"

#include "UrlMonitor.h"


#define PRINT(X) //

UrlMonitor::UrlMonitor(
		std::string uri_name,
		unsigned poll_interval,
		MonitorMgr *mgr,
		PlaylistInterface *playlist_,
		VariantPlaylist *variant_playlist_)
{
	URI = uri_name;
	size_t path_offset = URI.find_last_of("/");
	if(path_offset != std::string::npos)
	{
		path = URI.substr(0, path_offset+1);
		name = URI.substr(path_offset+1, URI.size());
	}
	polling_interval = poll_interval;
	task_scheduler = mgr;

	playlist = playlist_;
	variant_playlist = variant_playlist_;

	cached_filename = URI;
	downloaded_filename = URI + std::string("_dl");
	my_replace(cached_filename, "/", "_");
	my_replace(downloaded_filename, "/", "_");

	fc = new CompareFile();

	http_get = new HTTPGet();
}

UrlMonitor::~UrlMonitor()
{
	std::cout << "dtor UrlMonitor " << URI << std::endl;
	if(fc)
		delete(fc);
}

void UrlMonitor::execute()
{
	//download the playlist
	http_get->http_get_file(URI.c_str(), downloaded_filename.c_str());

	//filecompare
	fc->set_first(cached_filename.c_str());
	fc->set_second(downloaded_filename.c_str());
	std::deque<CompareResultInterface*> compare_result = fc->compare();

	if(compare_result.size() > 0)
	{
		rename(downloaded_filename.c_str(), cached_filename.c_str());
		variant_playlist->update_playlist(compare_result, playlist); 		//get delta to playlist
	}
}

void UrlMonitor::my_replace(std::string &original, const char *search, const char *replace)
{
	size_t pos = 0;
	while((pos = original.find(search, pos)) != std::string::npos)
	{
		original.replace(pos, 1, replace);
		pos++;
	}
}

