/*
 * unittest.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#include "common.h"
#include "PlaylistManager.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: ./playlistMgrtool <master-playlist-name>";
		return -1;
	}
	PlaylistManager mgr(argv[1]);
	mgr.marshall();

	std::this_thread::sleep_for(std::chrono::seconds(20));
}
