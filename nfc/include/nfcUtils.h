#ifndef NFCUTILS
#define NFCUTILS

#include <sstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

uint8_t charToHex(const char& c);
std::string byteArrayToString(const uint8_t* byteArray, const int& start, const int& end);
std::vector<uint8_t> hexStringToByteArray(const std::string& str);
void print(const std::vector<uint8_t>& v);

#endif
