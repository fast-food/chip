#include "../include/network.h"

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up){
    for (int c = 0; c<size*nmemb; c++)
    {
        SERVER_DATA.push_back(buf[c]);
    }
    return size*nmemb;
}

bool request(const std::string& url, std::string& result){
    CURL* curl = curl_easy_init();
    CURLcode res;
    long http_code = 0;

    SERVER_DATA = "";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(curl);
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res==CURLE_OK && http_code==200){
        result = SERVER_DATA;
        return true;
    }
    else{
        result = "";
        return false;
    }
}
