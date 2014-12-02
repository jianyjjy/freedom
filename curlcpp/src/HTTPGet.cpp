/*
 * HTTPGet.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: satram
 */

#include "common.h"
#include "curl_easy.h"

#include "HTTPGet.h"
using curl::curl_easy;
using std::cout;
using std::endl;
using std::ofstream;

HTTPGet::HTTPGet() {
	// TODO Auto-generated constructor stub

}

HTTPGet::~HTTPGet() {
	// TODO Auto-generated destructor stub
}

void HTTPGet::http_get_file(const char *url, const char *filename)
{
    // Create a file
    std::ofstream myfile;
    myfile.open (filename);
    // Create a writer to handle the stream

    curl_writer writer(myfile);
    // Pass it to the easy constructor and watch the content returned in that file!
    curl_easy easy(writer);

    // Add some option to the easy handle
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,url) );
    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
    try {
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        vector<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    myfile.close();
}
