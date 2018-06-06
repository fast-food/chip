#include <iostream>
#include <jsoncpp/json/json.h>

#include "../nfc/include/nfcManager.h"
#include "../nfc/include/nfcRequest.h"
#include "../network/include/network.h"

bool parseNfcRequest(const std::string& json, NfcRequest& request){
    Json::Value root;
    Json::Reader reader;
    if (reader.parse(json.c_str(), root)){
        request.setType(root["type"].asInt());
        request.setUrl(root["url"].asString());
        for(const auto& obj : root["data"]){
            request.addData(obj["key"].asString(), obj["value"].asString());
        }
        return true;
    }
    std::cout << "Failed to parse request : " << reader.getFormattedErrorMessages();
    return false;
}

int main() {
    Network network;
    NfcManager manager;
    NfcRequest nfcRequest;

    if(manager.open()){
        std::cout << "Nfc device opened. Waiting for target..." << std::endl;

        while(1){
            APDU apdu;
            std::string json;
            bool interrupted = false;

            while(!manager.isTargetPresent());
            if(manager.selectApplication("F222222222", apdu)){
                std::vector<uint8_t> response = apdu.getRespBytes();
                while(response.size()!=0){
                    std::string received = apdu.getRespString();
                    if(!parseNfcRequest(received, nfcRequest)){
                        std::cout << "Could not parse json : " << received << std::endl;
                        break;
                    }

                    if(nfcRequest.getType()==NfcRequest::GET){
                        std::string url = nfcRequest.getUrl();
                        if(!network.getRequest(url, json)){
                            std::cout << "Could not request: " << url << std::endl;
                            break;
                        }

                        size_t msgLength = json.size();
                        size_t maxLength = apdu.getCmdMaxLength();

                        if(msgLength <= maxLength){
                            apdu.reset();
                            apdu.setCmd(json);
                            if(!manager.transceive(apdu)){
                                interrupted = true;
                                break;
                            }
                            response = apdu.getRespBytes();
                        }
                        else{
                            int q = msgLength/maxLength;
                            int r = msgLength%maxLength;

                            // send q messages of length maxLength
                            apdu.reset();
                            apdu.setParams(0x01, 0x00);
                            for(int i=0 ; i<q ; i++){
                                apdu.setCmd(json.substr(i*maxLength, maxLength));
                                if(!manager.transceive(apdu)){
                                    interrupted = true;
                                    break;
                                }
                            }

                            // send 1 message of length r
                            apdu.setParams(0x02, 0x00);
                            apdu.setCmd(json.substr(q*maxLength, r));
                            if(!manager.transceive(apdu)){
                                interrupted = true;
                                break;
                            }
                            response = apdu.getRespBytes();
                        }
                    }
                    else if(nfcRequest.getType()==NfcRequest::POST){
                        if(!network.postRequest(nfcRequest.getUrl(), nfcRequest.getData(), json)){
                            std::cout << "Could not request: " << nfcRequest.getUrl() << std::endl;
                            break;
                        }
                        apdu.reset();
                        apdu.setCmd(json);
                        if(!manager.transceive(apdu)){
                            interrupted = true;
                            break;
                        }
                        response = apdu.getRespBytes();
                    }
                }
            }
            else{
                interrupted = true;
            }

            if(interrupted){
                std::cout << "Connection interrupted. Please try again." << std::endl;
            }
        }

        manager.close();
    }
    else{
        std::cout << "could not open device" << std::endl;
    }
    return 0;
}
