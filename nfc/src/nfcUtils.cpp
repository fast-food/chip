#include "../include/nfcUtils.h"

uint8_t charToHex(const char& c){
   if(c >= '0' && c <= '9')
     return (c - '0');
   else
     return (c-'A'+10);
}

std::string byteArrayToString(const uint8_t* byteArray, const int& start, const int& end){
    std::stringstream ss;
    for(int i=start ; i<end ; i++){
        ss << byteArray[i];
    }
    return ss.str();
}

std::vector<uint8_t> hexStringToByteArray(const std::string& str) {
    std::vector<uint8_t> hex;
    for (int i=0 ; i<str.length() ; i+=2) {
        hex.push_back(charToHex(str[i+1]) + (charToHex(str[i]) << 4));
    }
    return hex;
}

void print(const std::vector<uint8_t>& v) {
    for(int i=0 ; i<v.size() ; i++){
        printf("%.2X", v[i]);
    }
    std::cout << std::endl;
}
