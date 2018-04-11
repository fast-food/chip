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

bool getFoodFromServer(const std::string& serverAddr, std::vector<Food>& food){
    SERVER_DATA = "";
    std::string response;
    if(request(serverAddr, response)){
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(response.c_str(), root)){
            std::vector<std::string> foodNames = {"sandwich", "extra", "drink"};
            food.clear();
            for(const auto& name : foodNames){
                for(int i=0 ; i<root[name].size() ; i++){
                    Food f(root[name][i]["id"].asInt(), root[name][i]["name"].asString());
                    food.push_back(f);
                }
            }
            return true;
        }
    }
    return false;
}
