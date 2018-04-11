#include <iostream>
#include <map>

#include "../food/include/menuUtils.h"
#include "../nfc/include/nfcManager.h"
#include "../network/include/network.h"

const std::string BASE_URL = "http://127.0.0.1:8080";

std::map<std::string, std::string> getCommands(){
    std::map<std::string, std::string> cmds;
    std::string json;

    // menus
    std::vector<Menu> menus;
    if(!requestUri(BASE_URL, "/menu", json)){
        std::cout << "Could not get menus from server." << std::endl;
        exit(1);
    }
    if(!parseMenus(json, menus)){
        std::cout << "Could not parse menus." << std::endl;
        exit(1);
    }
    std::stringstream ss;
    writeFood(ss, menus);
    cmds["1"] = ss.str();


    // food
    std::vector<Food> food;
    if(!requestUri(BASE_URL, "/food", json)){
        std::cout << "Could not get food from server." << std::endl;
        exit(1);
    }
    if(!parseFood(json, food)){
        std::cout << "Could not parse food." << std::endl;
        exit(1);
    }
    std::stringstream ss;
    writeFood(ss, food);
    cmds["2"] = ss.str();

    return cmds;
}

int main(int argc, char const *argv[]) {
    std::map<std::string, std::string> cmds = getCommands();

    NfcManager manager;
    if(manager.open()){
        std::cout << "Nfc device opened. Waiting for target..." << std::endl;
        while(1){
            while(!manager.isTargetPresent());

            std::string response;
            if(manager.selectApplication("F222222222", response)){
                std::cout << "request = [" << response << "]" << std::endl;
                for(const auto& cmd : cmds){
                    if(response==cmd.first){
                        if(!manager.send(cmd.first+cmd.second, response)){
                            std::cout << "could not send message back" << std::endl;
                        }
                        break;
                    }
                }
            }
            else{
                std::cout << "could not select app" << std::endl;
            }
        }
        manager.close();
    }
    else{
        std::cout << "could not open device" << std::endl;
    }
    return 0;
}
