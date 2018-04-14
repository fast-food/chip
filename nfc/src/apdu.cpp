#include "../include/apdu.h"

APDU::APDU(){
    reset();
}

void APDU::reset(){
    mCla = '\x00';
    mIns = '\x00';
    mParams = {'\x00', '\x00'};
    mLc = {'\x00'};
    mCmd = {};
    mLe = {};

    mSW1 = '\x00';
    mSW2 = '\x00';
    mResp = {};
}

void APDU::setClass(const uint8_t& cla){
    mCla = cla;
}

void APDU::setInstruction(const uint8_t& ins){
    mIns = ins;
}

void APDU::setParams(const uint8_t& p1, const uint8_t& p2){
    mParams[0] = p1;
    mParams[1] = p2;
}

void APDU::setCmd(const std::string& data){
    size_t length = data.size();
    assert(length <= MAX_CMD_LENGTH);
    mCmd = std::vector<uint8_t>(data.begin(), data.end());
    updateCmdLength();
}

void APDU::setCmd(const std::vector<uint8_t>& data){
    size_t length = data.size();
    assert(length <= MAX_CMD_LENGTH);
    mCmd = std::vector<uint8_t>(data.begin(), data.end());
    updateCmdLength();
}

void APDU::updateCmdLength(){
    size_t length = mCmd.size();
    std::vector<uint8_t> lBytes = intToBytes(length);
    if(length==0){
        mLc = {};
    }
    else if(length<=MAX_CMD_LENGTH){
        mLc = {lBytes[3]};
    }
}

void APDU::setExpectedRespLength(const int& length){
    assert(length <= MAX_CMD_LENGTH+1);
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

uint8_t APDU::getClass() const{
    return mCla;
}

uint8_t APDU::getInstruction() const{
    return mIns;
}

std::vector<uint8_t> APDU::getParams() const{
    return mParams;
}

std::string APDU::getCmdString() const{
    return byteArrayToString(&mCmd[0], 0, mCmd.size());
}

std::vector<uint8_t> APDU::getCmdBytes() const{
    return mCmd;
}

std::vector<uint8_t> APDU::buildCmd() const{
    std::vector<uint8_t> apdu;
    apdu.push_back(mCla);
    apdu.push_back(mIns);
    apdu.insert(apdu.end(), mParams.begin(), mParams.end());
    apdu.insert(apdu.end(), mLc.begin(), mLc.end());
    apdu.insert(apdu.end(), mCmd.begin(), mCmd.end());
    apdu.insert(apdu.end(), mLe.begin(), mLe.end());
    return apdu;
}

void APDU::setSW1(const uint8_t& SW1){
    mSW1 = SW1;
}

void APDU::setSW2(const uint8_t& SW2){
    mSW2 = SW2;
}

void APDU::setResp(const std::string& response){
    size_t length = response.size();
    assert(length <= MAX_RESP_LENGTH);
    mResp = std::vector<uint8_t>(response.begin(), response.end());
}

void APDU::setResp(const uint8_t* resp, const size_t& length){
    std::string response = byteArrayToString(resp, 0, length);
    mResp = std::vector<uint8_t>(response.begin(), response.end());
}

uint8_t APDU::getSW1() const{
    return mSW1;
}

uint8_t APDU::getSW2() const{
    return mSW2;
}

std::string APDU::getRespString() const{
    return byteArrayToString(&mResp[0], 0, mResp.size());
}

std::vector<uint8_t> APDU::getRespBytes() const{
    return mResp;
}

std::vector<uint8_t> APDU::buildResp() const{
    std::vector<uint8_t> apdu;
    apdu.push_back(mSW1);
    apdu.push_back(mSW2);
    apdu.insert(apdu.end(), mResp.begin(), mResp.end());
    return apdu;
}

std::vector<uint8_t> APDU::intToBytes(const int& value){
    std::vector<uint8_t> result;
    result.push_back(value >> 24);
    result.push_back(value >> 16);
    result.push_back(value >>  8);
    result.push_back(value);
    return result;
}
