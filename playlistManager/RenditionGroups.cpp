/*
 * RenditionGroups.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "RenditionGroups.h"


RenditionGroups::RenditionGroups()
{
	variants.clear();
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
	std::cout << "Rendition Group " << sessionId << std::endl;
	for(unsigned int i = 0; i < variants.size(); i++)
		variants[i]->marshall();
}
