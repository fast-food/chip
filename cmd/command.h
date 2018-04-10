#ifndef COMMANDS
#define COMMANDS

#include <string>

struct Command {
    std::string mRequestCode;
    std::string mResponse;

    Command(){
        mRequestCode = "";
        mResponse = "";
    }

    Command(std::string requestCode, std::string response){
        mRequestCode = requestCode;
        mResponse = response;
    }
};

#endif
