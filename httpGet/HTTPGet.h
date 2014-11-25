//HTTPGet.h

#ifndef HTTP_GET_H
#define HTTP_GET_H

#include <string>
#include <fstream>
using namespace std;

struct MemoryStruct
{
	char *memory;
	size_t size;
};

bool httpGet_write(string url, ofstream* stream);
bool httpGet_write(string url, MemoryStruct* memory);

#endif	//HTTP_GET_H
