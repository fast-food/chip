#include "../include/apduResp.h"

APDUResp::APDUResp(){
    mSW1 = '\x00';
    mSW2 = '\x00';
}

void APDUResp::setSW1(const uint8_t& SW1){
    mSW1 = SW1;
}

void APDUResp::setSW2(const uint8_t& SW2){
    mSW2 = SW2;
}

void APDUResp::setResponse(const std::string& response){
    size_t length = response.size();
    assert(length <= MAX_RESP_LENGTH);
    mResp = std::vector<uint8_t>(response.begin(), response.end());
}

void APDUResp::setResponse(const uint8_t* resp, const size_t& length){
    std::string response = byteArrayToString(resp, 0, length);
    mResp = std::vector<uint8_t>(response.begin(), response.end());
}

uint8_t APDUResp::getSW1() const{
    return mSW1;
}

uint8_t APDUResp::getSW2() const{
    return mSW2;
}

std::string APDUResp::getResponse() const{
    std::vector<uint8_t> apdu = build();
    size_t length = apdu.size();
    return length>2?byteArrayToString(&apdu[0], 0, length-2):"";
}

std::vector<uint8_t> APDUResp::build() const{
    std::vector<uint8_t> apdu;
    apdu.push_back(mSW1);
    apdu.push_back(mSW2);
    apdu.insert(apdu.end(), mResp.begin(), mResp.end());
    return apdu;
}
