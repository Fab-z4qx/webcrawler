#pragma once

#include <string>
#include <iostream>

using namespace std;

class MyUrl
{
private:
	std::string _url;

public:
	MyUrl(void);
	MyUrl(const string& url) { _url = url; }
	~MyUrl(void);

	string getUrl(){ return _url; }
	void setUrl(const string &url) { _url = url; }

};

