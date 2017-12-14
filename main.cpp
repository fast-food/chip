#include <iostream>
#include "include/Communicator.h"

int main(int argc, char const *argv[]) {
    Communicator com;
    if(com.open()){
        std::cout << "device opened" << std::endl;
        while(!com.isTargetPresent());

        if(com.selectApplication("F222222222")){
            std::cout << "app selected" << std::endl;
            std::string resp;
            if(com.send("hello world", resp)){
                std::cout << "sent !" << std::endl;
                std::cout << "received: " << resp << std::endl;
            }
            else{
                std::cout << "could not send message" << std::endl;
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
