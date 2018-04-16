#include <iostream>

#include "../nfc/include/nfcManager.h"
#include "../network/include/network.h"

int main(int argc, char const *argv[]) {
    Network network;
    NfcManager manager;
    if(manager.open()){
        std::cout << "Nfc device opened. Waiting for target..." << std::endl;

        while(1){
            APDU apdu;
            std::string json;

            while(!manager.isTargetPresent());
            if(manager.selectApplication("F222222222", apdu)){
                std::vector<uint8_t> response = apdu.getRespBytes();
                while(response.size()!=0){
                    std::string url = apdu.getRespString();
                    if(!network.request(url, json)){
                        std::cout << "Could not request: " << url << std::endl;
                        break;
                    }
                    size_t msgLength = json.size();
                    size_t maxLength = apdu.getCmdMaxLength();

                    if(msgLength <= maxLength){
                        apdu.reset();
                        apdu.setCmd(json);
                        if(!manager.transceive(apdu)){
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
                        for(unsigned int i=0 ; i<q ; i++){
                            apdu.setCmd(json.substr(i*maxLength, maxLength));
                            if(!manager.transceive(apdu)){
                                break;
                            }
                        }

                        // send 1 message of length r
                        apdu.setParams(0x02, 0x00);
                        apdu.setCmd(json.substr(q*maxLength, r));
                        if(!manager.transceive(apdu)){
                            break;
                        }
                        response = apdu.getRespBytes();
                    }
                }
            }
            else{
                std::cout << "select error" << std::endl;
            }
        }

        manager.close();
    }
    else{
        std::cout << "could not open device" << std::endl;
    }
    return 0;
}
