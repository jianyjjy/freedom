/*
 * CurlCppTest.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: satram
 */
#include "common.h"

#include "curl_easy.h"
#include "curl_form.h"
#include "curl_pair.h"
#include "curl_receiver.h"
#include "curl_sender.h"

#include "CurlCppTest.h"

using curl::curl_form;
using curl::curl_easy;
using curl::curl_sender;
using curl::curl_receiver;

using std::cout;
using std::endl;
using std::ofstream;


CurlCppTest::CurlCppTest() {
	// TODO Auto-generated constructor stub

}

int CurlCppTest::simple_http_request(const char *url)
{
    curl_easy easy;
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,url) );
    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
    try {
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        vector<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    return 0;
}

int CurlCppTest::https_post_login_form()
{
    curl_form form;
    curl_easy easy;

    // Forms creation
    curl_pair<CURLformoption,string> name_form(CURLFORM_COPYNAME,"user");
    curl_pair<CURLformoption,string> name_cont(CURLFORM_COPYCONTENTS,"username");
    curl_pair<CURLformoption,string> pass_form(CURLFORM_COPYNAME,"passw");
    curl_pair<CURLformoption,string> pass_cont(CURLFORM_COPYCONTENTS,"password");

    try {
        // Form adding
        form.add(name_form,name_cont);
        form.add(pass_form,pass_cont);

        // Add some options to our request
        easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://127.0.0.1"));
        easy.add(curl_pair<CURLoption,bool>(CURLOPT_SSL_VERIFYPEER,false));
        easy.add(curl_pair<CURLoption,curl_form>(CURLOPT_HTTPPOST,form));
        easy.perform();
    } catch (curl_easy_exception error) {
        // Print errors, if any
        error.print_traceback();
    }
    return 0;
}

int CurlCppTest::http_get_file(const char *url, const char *filename)
{
    // Create a file
    ofstream myfile;
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
    return 0;
}

int CurlCppTest::web_socket_conn()
{
    // Simple request
    string request = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";

    // Creation of easy object.
    curl_easy easy;
    try {
        easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://example.com"));
        // Just connect
        easy.add(curl_pair<CURLoption,bool>(CURLOPT_CONNECT_ONLY,true));
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        vector<pair<string,string>> errors = error.what();
        // Print errors if any
        error.print_traceback();
    }

    // Creation of a sender. You should wait here using select to check if socket is ready to send.
    curl_sender<string> sender(easy);
    sender.send(request);
    // Prints che sent bytes number.
    cout<<"Sent bytes: "<<sender.get_sent_bytes()<<endl;

    for(;;) {
        // You should wait here to check if socket is ready to receive
        try {
            // Create a receiver
            curl_receiver<char,1024> receiver;
            // Receive the content on the easy handler
            receiver.receive(easy);
            // Prints the received bytes number.
            cout<<"Receiver bytes: "<<receiver.get_received_bytes()<<endl;
        } catch (curl_easy_exception error) {
            // If any errors occurs, exit from the loop
            break;
        }
    }
    return 0;
}

CurlCppTest::~CurlCppTest() {
	// TODO Auto-generated destructor stub
}
