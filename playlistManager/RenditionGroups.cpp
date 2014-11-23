/*
 * RenditionGroups.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "RenditionGroups.h"


RenditionGroups::RenditionGroups(unsigned int id)
{
	variants.clear();
	session_id = id;
}

RenditionGroups::~RenditionGroups()
{
	for(unsigned int i = 0; i < variants.size(); i++)
		delete(variants[i]);
	variants.clear();
}

void RenditionGroups::marshall()
{
	std::cout << "--------------------------------------------------\n";
	std::cout << "Rendition Group " << session_id << std::endl;
	for(unsigned int i = 0; i < variants.size(); i++)
	{
		std::cout << "--------------------------------------------------\n";
		std::cout << "variants#" << i << std::endl;
		variants[i]->marshall();
	}
}


void RenditionGroups::add_variant(VariantsInfo *variant_info)
{
	VariantPlaylist *var = new VariantPlaylist(variant_info);
	variants.push_back(var);
}
