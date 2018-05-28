#include "../include/nfcRequest.h"

NfcRequest::NfcRequest(){
    mType = 0;
    mUrl = "";
}

NfcRequest::NfcRequest(int type, std::string url){
    mType = type;
    mUrl = url;
}

int NfcRequest::getType() const{
    return mType;
}

std::string NfcRequest::getUrl() const{
    return mUrl;
}

std::vector<std::pair<std::string, std::string> > NfcRequest::getDatas() const{
    return mData;
}

void NfcRequest::addData(std::string key, std::string value){
    mData.push_back(std::make_pair(key, value));
}

void NfcRequest::resetData(){
    mData.clear();
}

void NfcRequest::setUrl(std::string url){
    mUrl = url;
}

void NfcRequest::setType(int type){
    mType = type;
}
