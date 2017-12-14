#ifndef DEF_UTILS
#define DEF_UTILS

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iterator>

#include <stdint.h>

static uint8_t charToHex(char c){
   if(c >= '0' && c <= '9')
     return (c - '0');
   else
     return (c-'A'+10);
}

static std::vector<uint8_t> stringToByteArray(const std::string &str){
    std::vector<uint8_t> source(str.begin(), str.end());
    return source;
}

static std::vector<uint8_t> hexStringToByteArray(const std::string &str) {
    std::vector<uint8_t> hex;
    for (int i=0 ; i<str.length() ; i+=2) {
        hex.push_back(charToHex(str[i+1]) + (charToHex(str[i]) << 4));
    }
    return hex;
}

#endif
