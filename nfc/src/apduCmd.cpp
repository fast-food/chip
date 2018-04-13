#include "../include/apduCmd.h"

APDUCmd::APDUCmd(){
    mCla = '\x00';
    mIns = '\x00';
    mParams = {'\x00', '\x00'};
    mLe = {'\x00'};
}

void APDUCmd::setClass(const uint8_t& cla){
    mCla = cla;
}

void APDUCmd::setInstruction(const uint8_t& ins){
    mIns = ins;
}

void APDUCmd::setParams(const uint8_t& p1, const uint8_t& p2){
    mParams[0] = p1;
    mParams[1] = p2;
}

void APDUCmd::setData(const std::string& data){
    size_t length = data.size();
    assert(length <= MAX_CMD_LENGTH);
    mData = std::vector<uint8_t>(data.begin(), data.end());
    setCommandLength();
}

void APDUCmd::setData(const std::vector<uint8_t>& data){
    size_t length = data.size();
    assert(length <= MAX_CMD_LENGTH);
    mData = std::vector<uint8_t>(data.begin(), data.end());
    setCommandLength();
}

void APDUCmd::setCommandLength(){
    size_t length = mData.size();
    std::vector<uint8_t> lBytes = intToBytes(length);
    if(length==0){
        mLc = {};
    }
    else if(length<=MAX_CMD_LENGTH){
        mLc = {lBytes[3]};
    }
}

void APDUCmd::setExpectedLength(const int& length){
    assert(length <= MAX_CMD_LENGTH+1);

    // Le
    std::vector<uint8_t> lBytes = intToBytes(length);
    if(length==0){
        mLe = {};
    }
    else if(length<=MAX_CMD_LENGTH){
        mLe = {lBytes[3]};
    }
    else if(length==MAX_CMD_LENGTH+1){
        mLe = {'\x00'};
    }
}

uint8_t APDUCmd::getClass() const{
    return mCla;
}

uint8_t APDUCmd::getInstruction() const{
    return mIns;
}

std::vector<uint8_t> APDUCmd::getParams() const{
    return mParams;
}

std::string APDUCmd::getData() const{
    std::vector<uint8_t> apdu = build();
    return byteArrayToString(&apdu[0], 0, apdu.size());
}

std::vector<uint8_t> APDUCmd::build() const{
    std::vector<uint8_t> apdu;
    apdu.push_back(mCla);
    apdu.push_back(mIns);
    apdu.insert(apdu.end(), mParams.begin(), mParams.end());
    apdu.insert(apdu.end(), mLc.begin(), mLc.end());
    apdu.insert(apdu.end(), mData.begin(), mData.end());
    apdu.insert(apdu.end(), mLe.begin(), mLe.end());
    return apdu;
}

std::vector<uint8_t> APDUCmd::intToBytes(const int& value){
    std::vector<uint8_t> result;
    result.push_back(value >> 24);
    result.push_back(value >> 16);
    result.push_back(value >>  8);
    result.push_back(value);
    return result;
}
