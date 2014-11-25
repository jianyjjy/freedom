//testmain.cpp

#include "HTTPGet.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	if( argc < 2 )
	{
		std::cout << "Usage: ./httpGetTool <url>" << endl;
		return -1;
	}

	string url(argv[1]);
	
	{
		std::cout << "Performing url to stream" << endl;
		ofstream os("out_stream");
		if( httpGet_write(url, &os) )
			std::cout << "url to stream done" << endl;
		else
			std::cout << "url to stream failed" << endl;
	}

	std:: cout << endl << endl;

	{
		std::cout << "Performing url to memory" << endl;
		MemoryStruct mem{nullptr, 0};
		if( httpGet_write(url, &mem) )
		{
			std::cout << "url to memory done" << endl;
			std::cout << mem.memory << endl;
		}
		else
			std::cout << "url to memory failed" << endl;
	}

	cout << "Test";
	return 0;
}
