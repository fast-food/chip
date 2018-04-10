#include <iostream>

#include "../nfc/include/Communicator.h"
#include "../food/include/FoodUtils.h"

int main(int argc, char const *argv[]) {
    static const std::string MENU = "1";

    std::vector<Menu> menus;
    loadMenus("food/menus", menus);

    Communicator com;
    if(com.open()){
        std::cout << "device opened. Waiting for device..." << std::endl;
        while(!com.isTargetPresent());

        std::string response;
        if(com.selectApplication("F222222222", response)){
            std::cout << "response = [" << response << "]" << std::endl;
            if(response==MENU){
                if(!com.send(MENU+toJson(menus), response)){
                    std::cout << "could not send message" << std::endl;
                }
            }
        }
        else{
            std::cout << "could not select app" << std::endl;
        }
        com.close();
    }
    else{
        std::cout << "could not open device" << std::endl;
    }
    return 0;
}
