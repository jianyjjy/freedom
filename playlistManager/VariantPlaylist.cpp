/*
 * VariantPlaylist.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "PlaylistInterface.h"
#include "VariantPlaylist.h"

VariantPlaylist::VariantPlaylist()
{
	media = NULL;
	iframe = NULL;

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
		media->marshall();
	}

	if(iframe)
	{
		std::cout << "--------------------------------------------------\n";
		std::cout << "Iframe playlist " << std::endl;
		iframe->marshall();
	}

}