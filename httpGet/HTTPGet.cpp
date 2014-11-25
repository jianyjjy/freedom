//HTTPGet.cpp

#include "HTTPGet.h"

#include <curl/curl.h>
#include <curl/easy.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

#define LOG(str) cout << "[LOG] " << str << endl;

size_t write_to_stream(void *data, size_t size, size_t nmemb, void *stream)
{
	ofstream* os = static_cast<ofstream*>(stream);

	size_t size_before = os->tellp();
	os->write((const char*)data, size * nmemb);
	size_t bytes_written = os->tellp();
	bytes_written -= size_before;

	return bytes_written;
}


bool httpGet_write(string url, ofstream* stream)
{
	LOG("Entering in HTTPGet::write() to stream");

	if( !stream->is_open() )
		return false;

	CURL* curl;
	CURLcode curl_code;

	curl = curl_easy_init();
	if( !curl )
		return false;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_stream);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
	curl_code = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	LOG("writing to stream done");

	return (curl_code == CURLE_OK);
}

size_t write_to_memory(void *data, size_t size, size_t nmemb, void *mem_loc)
{
	MemoryStruct* mem = static_cast<MemoryStruct*>(mem_loc);
	size_t total_bytes = size * nmemb;

	mem->memory = (char*)realloc(mem->memory, mem->size + total_bytes + 1);
	if( mem->memory == nullptr )
	{
		LOG("Not enough memory");
		return 0;
	}

	memcpy(mem->memory + mem->size, data, total_bytes);
	mem->size += total_bytes;
	mem->memory[mem->size] = 0;

	return total_bytes;
}


bool httpGet_write(string url, MemoryStruct* memory)
{
	LOG("Entering in HTTPGet::write() to memory");


	CURL *curl;
        CURLcode curl_code;
        curl = curl_easy_init();
	if( !curl )
		return false;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_memory);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)memory);
	curl_code  = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	LOG("writing to memory done");

	return (curl_code == CURLE_OK);
}
