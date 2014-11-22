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

	if(!variants_info->get_media_URI().empty())
		media = factory->getDOM(variants_info->get_media_URI().c_str());

	if(!variants_info->get_iframe_URI().empty())
		iframe = factory->getDOM(variants_info->get_iframe_URI().c_str());
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
