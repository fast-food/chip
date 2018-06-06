#include "../include/network.h"

Network::Network(){
    mCurl = curl_easy_init();
    mServerData = "";
}

Network::~Network(){
    curl_easy_cleanup(mCurl);
    curl_global_cleanup();
}

size_t Network::writeCallback(char* buf, size_t size, size_t nmemb, void* userdata){
    for (int c = 0; c<size*nmemb; c++){
        mServerData.push_back(buf[c]);
    }
    return size*nmemb;
}

bool Network::request(const std::string& url, std::string& result){
    CURLcode res;
    long http_code = 0;
    mServerData = "";

    curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, Network::writeCallbackStatic);
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(mCurl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(mCurl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(mCurl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(mCurl);
    curl_easy_getinfo (mCurl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res==CURLE_OK && http_code==200){
        result = mServerData;
        return true;
    }
    else{
        result = curl_easy_strerror(res);
        return false;
    }
}

bool Network::postRequest(const std::string& url, const std::vector<std::pair<std::string, std::string> >& post, std::string& result){
    CURLcode res;
    long http_code = 0;
    mServerData = "";

    std::stringstream ss;
    for(const auto& p : post){
        ss << p.first << "=" << p.second;
        ss << "&";
    }

    curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, ss.str().c_str());
    curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, Network::writeCallbackStatic);
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(mCurl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(mCurl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(mCurl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(mCurl);
    curl_easy_getinfo (mCurl, CURLINFO_RESPONSE_CODE, &http_code);

    if(res == CURLE_OK && http_code==200){
        result = mServerData;
        return true;
    }
    else{
        result = curl_easy_strerror(res);
        return false;
    }
}
