#ifndef DEF_UTILS
#define DEF_UTILS

#include <sstream>
#include <vector>
#include <stdint.h>

static uint8_t charToHex(char c){
   if(c >= '0' && c <= '9')
     return (c - '0');
   else
     return (c-'A'+10);
}

static std::string byteArrayToString(uint8_t* byteArray, int start, int end){
    std::stringstream ss;
    for(int i=start ; i<end ; i++){
        ss << byteArray[i];
    }
    return ss.str();
}

static std::vector<uint8_t> hexStringToByteArray(const std::string &str) {
    std::vector<uint8_t> hex;
    for (int i=0 ; i<str.length() ; i+=2) {
        hex.push_back(charToHex(str[i+1]) + (charToHex(str[i]) << 4));
    }
    return hex;
}

#endif
