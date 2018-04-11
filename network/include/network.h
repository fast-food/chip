#ifndef NETWORK
#define NETWORK

#include <iostream>
#include <vector>

#include <curl/curl.h>

static std::string SERVER_DATA;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
bool request(const std::string& url, std::string& result);
bool requestUri(const std::string& baseUrl, const std::string& uri, std::string& jsonStr);
bool getFoodFromServer(const std::string& baseUrl, std::string& jsonStr);
bool getMenusFromServer(const std::string& baseUrl, std::string& jsonStr);

#endif
