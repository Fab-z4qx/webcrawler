#include "WebPage.h"

WebPage::WebPage(void)
{
}

WebPage::~WebPage(void)
{
}

bool WebPage::operator==( const WebPage& x) const{
	if(_hostname == x._hostname && _page == x._page)
		return true;
	else
		return false;
}