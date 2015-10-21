#include "HttpGet.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data << endl;
    return size * nmemb;
}

HttpGet::HttpGet(void)
{
	_curl = curl_easy_init();
}

HttpGet::~HttpGet(void)
{
	curl_easy_cleanup(_curl);
}

string HttpGet::get(const std::string& url) {
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
	//curl_easy_setopt(_curl, CURLOPT_NOBODY, 1); //display
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "deflate");

    std::stringstream out;
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &out);
	//cout << out << endl;
	//cout << "test" << endl;
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    return out.str();
}

