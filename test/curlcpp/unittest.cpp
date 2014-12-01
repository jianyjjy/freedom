/*
 * unittest.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: satram
 */
#include "common.h"
#include "CurlCppTest.h"

int main()
{
	CurlCppTest example;
	example.simple_http_request("http://od.cdn.phodux.com/partner/vodcontent/publish/vod-FOX_NETSHOWS_HD-BFOX0006625020140814/stb.m3u8");
	example.http_get_file("http://od.cdn.phodux.com/partner/vodcontent/publish/vod-FOX_NETSHOWS_HD-BFOX0006625020140814/stb.m3u8", "master.m3u8");
	return 0;
}
