#include <iostream>
#include <map>

#include "../food/include/menuUtils.h"
#include "../nfc/include/nfcManager.h"
#include "../network/include/network.h"

std::map<std::string, std::string> getCommands(){
    std::map<std::string, std::string> cmds;

    // menus
    std::string menusFilename = "data/menus";
    std::vector<Menu> menus;
    if(!readMenusFromFile(menusFilename, menus)){
        std::cout << "could not read menus : " << menusFilename << std::endl;
        exit(1);
    }

    std::stringstream ss;
    writeMenus(ss, menus);
    cmds["1"] = ss.str();

    // others...
    cmds["0"] = "Hello World!!! :D";

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
