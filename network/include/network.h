#ifndef NETWORK
#define NETWORK

#include <string>
#include <sstream>
#include <vector>
#include <utility>
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
        bool postRequest(const std::string& url, const std::vector<std::pair<std::string, std::string> >& post, std::string& result);
};

#endif
