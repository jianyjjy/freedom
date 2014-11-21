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
