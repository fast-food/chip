#include <iostream>
#include <unistd.h>
#include <map>

#include "../nfc/include/nfcManager.h"
#include "../network/include/network.h"

const std::string BASE_URL = "http://127.0.0.1:8080";

std::map<uint8_t, std::string> getCommands(){
    std::map<uint8_t, std::string> cmds;
    std::string json;

    // menus
    if(!requestUri(BASE_URL, "/menu", json)){
        std::cout << "Could not get menus from server." << std::endl;
        exit(1);
    }
    cmds[0x01] = json;

    // food
    if(!requestUri(BASE_URL, "/food", json)){
        std::cout << "Could not get food from server." << std::endl;
        exit(1);
    }
    cmds[0x02] = json;

    return cmds;
}

int main(int argc, char const *argv[]) {
    std::map<uint8_t, std::string> cmds = getCommands();

    NfcManager manager;
    if(manager.open()){
        std::cout << "Nfc device opened. Waiting for target..." << std::endl;

        while(1){
            APDU apdu;

            while(!manager.isTargetPresent());
            if(manager.selectApplication("F222222222", apdu)){
                std::vector<uint8_t> response = apdu.getRespBytes();
                while(response.size()!=0){
                    uint8_t code = response[0];
                    std::string msg = cmds[response[0]];
                    size_t msgLength = msg.size();
                    size_t maxLength = apdu.getCmdMaxLength();

                    if(msgLength <= maxLength){
                        apdu.reset();
                        apdu.setClass(code);
                        apdu.setCmd(msg);
                        if(!manager.transceive(apdu)){
                            break;
                        }
                        response = apdu.getRespBytes();
                    }
                    else{
                        apdu.reset();
                        apdu.setClass(code);
                        int q = msgLength/maxLength;
                        int r = msgLength%maxLength;

                        // send q messages of length maxLength
                        apdu.setInstruction(0x01);
                        for(unsigned int i=0 ; i<q ; i++){
                            apdu.setCmd(msg.substr(i*maxLength, maxLength));
                            if(!manager.transceive(apdu)){
                                break;
                            }
                        }

                        // send 1 message of length r
                        apdu.setInstruction(0x02);
                        apdu.setCmd(msg.substr(q*maxLength, r));
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
