#pragma once

#include <curl/curl.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>


using namespace std;
class HttpGet
{
private:
	CURL *_curl;

public:
	HttpGet(void);
	~HttpGet(void);

	string get(const std::string& url);
};

