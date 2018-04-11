#ifndef NFCUTILS
#define NFCUTILS

#include <sstream>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <iomanip>

uint8_t charToHex(char c);
std::string byteArrayToString(uint8_t* byteArray, int start, int end);
std::vector<uint8_t> hexStringToByteArray(const std::string &str);
void print(const std::vector<uint8_t>& v);

#endif
