/*
 * CurlCppTest.h
 *
 *  Created on: Dec 1, 2014
 *      Author: satram
 */

#ifndef CURLCPPTEST_H_
#define CURLCPPTEST_H_

class CurlCppTest {

	int https_post_login_form();
	int web_socket_conn();

public:

	int simple_http_request(const char *url);
	int http_get_file(const char *url, const char *filename);

	CurlCppTest();
	virtual ~CurlCppTest();
};

#endif /* CURLCPPTEST_H_ */
