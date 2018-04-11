#ifndef NETWORK
#define NETWORK

#include <iostream>
#include <vector>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "../../food/include/food.h"

std::string SERVER_DATA;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
bool request(const std::string& url, std::string& result);
bool getFoodFromServer(const std::string& serverAddr, std::vector<Food>& food);

//
// int main(int argc, char const *argv[]) {
//     std::string server = "http://127.0.0.1:8080/food";
//     std::vector<Food> food;
//     if(getFoodFromServer(server, food)){
//         for(const auto& f : food){
//             std::cout << f.mId << " : " << f.mName << std::endl;
//         }
//     }
//     else{
//         std::cout << "Could not get food from server." << std::endl;
//     }
//     return 0;
// }


#endif
