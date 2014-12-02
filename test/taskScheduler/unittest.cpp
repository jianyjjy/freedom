/*
 * unittest.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: satram
 */

#include "common.h"
#include "monitor_common.h"
#include "MonitorMgr.h"
#include "UrlMonitor.h"
#include "TaskHandler.h"

int main()
{
	MonitorMgr *mgr = MonitorMgr::get_instance();
	mgr->create_url_monitor("media1.m3u8", 3);
	mgr->create_url_monitor("media2.m3u8", 5);
	mgr->create_url_monitor("media3.m3u8", 10);

	int count = 0;
	while(count < 2)
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));
		count++;
	}
	mgr->delete_instance();
	return 0;
}
