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

VariantPlaylist::VariantPlaylist(VariantsInfo *variants_info)
{
	media = NULL;
	iframe = NULL;
	PlaylistFactory * factory = PlaylistFactory::get_instance();

	std::string media_URI = variants_info->get_media_URI();
	if(!media_URI.empty())
	{
		std::cout << "mediaURI " << media_URI << std::endl;
		try {
			media = factory->getDOM(media_URI.c_str());
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::string iframe_URI = variants_info->get_iframe_URI();
	if(!iframe_URI.empty())
	{
		std::cout << "iframeURI " << iframe_URI << std::endl;
		try {
		iframe = factory->getDOM(iframe_URI.c_str());
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	}
}

VariantPlaylist::~VariantPlaylist()
{
	if(media)
	{
		delete(media);
		media = NULL;
	}
	if(iframe)
	{
		delete(iframe);
		iframe = NULL;
	}
}

void VariantPlaylist::marshall()
{
	if(media)
	{
		std::cout << "--------------------------------------------------\n";
		std::cout << "Media playlist " << std::endl;
		std::cout << media->marshall();
	}

	if(iframe)
	{
		std::cout << "--------------------------------------------------\n";
		std::cout << "Iframe playlist " << std::endl;
		std::cout << iframe->marshall();
	}

}
