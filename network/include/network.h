#ifndef NETWORK
#define NETWORK

#include <string>
#include <curl/curl.h>

class Network {
    private:
        CURL* mCurl;
        std::string mServerData;

        size_t writeCallback(char* buf, size_t size, size_t nmemb, void* userdata);
        static size_t writeCallbackStatic(char* buf, size_t size, size_t nmemb, void* userdata){
            return ((Network*)userdata)->writeCallback(buf, size, nmemb, userdata);
        }

    public:
        Network();
        ~Network();
        bool request(const std::string& url, std::string& result);
};

#endif
