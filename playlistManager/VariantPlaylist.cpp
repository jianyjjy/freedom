/*
 * VariantPlaylist.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "PlaylistInterface.h"
#include "VariantPlaylist.h"
#include "VariantsInfo.h"
#include "PlaylistFactory.h"


#include "HTTPGet.h"
#include "monitor_common.h"
#include "MonitorMgr.h"
#include "UrlMonitor.h"
#include "TaskHandler.h"



VariantPlaylist::VariantPlaylist(VariantsInfo *variants_info)
{
	media = NULL;
	iframe = NULL;
	media_uri_path.clear();
	iframe_uri_path.clear();

	PlaylistFactory * factory = PlaylistFactory::get_instance();
	mgr = MonitorMgr::get_instance();

	media_URI = variants_info->get_media_URI();
	if(!media_URI.empty())
	{
		std::cout << "mediaURI " << media_URI << std::endl;
		download_uri(media_URI, media_uri_path, media_local_uri);
		//create DOM
		try {
			media = factory->getDOM(media_uri_path.c_str(), media_local_uri.c_str());
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
		}
		//monitor
		mgr->create_url_monitor(media_URI.c_str(), 10, media, this);
	}

	iframe_URI = variants_info->get_iframe_URI();
	if(!iframe_URI.empty())
	{
		std::cout << "iframeURI " << iframe_URI << std::endl;
		download_uri(iframe_URI, iframe_uri_path, iframe_local_uri);
		//create DOM
		try {
			iframe = factory->getDOM(iframe_uri_path.c_str(), iframe_local_uri.c_str());
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
		}
		//monitor
		mgr->create_url_monitor(iframe_URI.c_str(), 8, iframe, this);
	}
}

VariantPlaylist::~VariantPlaylist()
{
	if(!media_URI.empty())
	{
		mgr->remove_url_monitor(media_URI.c_str());
	}
	if(!iframe_URI.empty())
	{
		mgr->remove_url_monitor(iframe_URI.c_str());
	}

	mgr->delete_instance();

	if(media)
	{
		delete(media);
		media = NULL;
		media_URI.clear();
	}
	if(iframe)
	{
		delete(iframe);
		iframe = NULL;
		iframe_URI.clear();
	}
}

void VariantPlaylist::marshall()
{
	if(media)
	{
		std::cout << "--------------------------------------------------\n";
		std::cout << "Media playlist " << std::endl;
		std::cout << media_URI << std::endl;
		std::cout << media->marshall();
	}

	if(iframe)
	{
		std::cout << "--------------------------------------------------\n";
		std::cout << "Iframe playlist " << std::endl;
		std::cout << iframe_URI << std::endl;
		std::cout << iframe->marshall();
	}

}

void VariantPlaylist::my_replace(std::string &original, const char *search, const char *replace)
{
	size_t pos = 0;
	while((pos = original.find(search, pos)) != std::string::npos)
	{
		original.replace(pos, 1, replace);
		pos++;
	}
}

void VariantPlaylist::download_uri(std::string &URI, std::string &path, std::string &local_uri)
{
	size_t offset = URI.find_last_of("/");
	if(offset != std::string::npos)
	{
		path = URI.substr(0, offset+1);
		local_uri = URI;
		my_replace(local_uri, "/", "_");
	}
	else
	{
		path.clear();
		local_uri = URI;
	}
	if(URI.find("http") != std::string::npos)
	{
		HTTPGet get;
		get.http_get_file(URI.c_str(), local_uri.c_str());
	}
	else
		local_uri = URI;
}


void VariantPlaylist::update_playlist(std::deque<CompareResultInterface*> compare_result, PlaylistInterface *playlist)
{
	if(playlist == media)
		std::cout << "Delta for " << media_URI << std::endl;
	if(playlist == iframe)
		std::cout << "Delta for " << iframe_URI << std::endl;

	for(unsigned int i = 0; i < compare_result.size(); i++)
		cout << compare_result[i]->marshall();
	std::cout << "-----------------------------\n";
}


