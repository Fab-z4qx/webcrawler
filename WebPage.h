#pragma once
#include <string>

using namespace std;

class WebPage
{
private:
	std::string _hostname;
	std::string _page;

public:
	WebPage(void);
	WebPage(std::string hostname) : _hostname(hostname) {}
	WebPage(std::string hostname, std::string page) : _hostname(hostname), _page(page) {}
	~WebPage(void);

	string getHosname(){ return _hostname; }
	string getPage(){ return _page; }
	string getfullPath() { return _hostname+_page; }

	void setHostname(std::string hostname){ _hostname = hostname; }
	void setPage(std::string page){ _page = page; }

	bool WebPage::operator==( const WebPage& x) const;

};

