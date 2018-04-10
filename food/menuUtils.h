#ifndef MENUUTILS
#define MENUUTILS

#include <fstream>
#include <sstream>
#include <vector>

#include "menu.h"

void writeMenus(std::ostream& os, const std::vector<Menu>& menus){
    os << menus.size() << std::endl;
    for(const auto& m : menus){
        m.write(os);
        os << std::endl;
    }
}

bool writeMenusToFile(const std::string& filename, const std::vector<Menu>& menus){
    std::ofstream file(filename.c_str());
    if(file){
        writeMenus(file, menus);
        file.close();
        return true;
    }
    return false;
}

void readMenus(std::istream& is, std::vector<Menu>& menus){
    std::string line;
    getline(is, line);
    int length = std::stoi(line);
    menus.resize(length);
    for(int i=0 ; i<length ; i++){
        Menu menu;
        menu.read(is);
        menus[i] = menu;
    }
}

bool readMenusFromFile(const std::string& filename, std::vector<Menu>& menus){
    std::ifstream file(filename.c_str());
    if(file){
        readMenus(file, menus);
        file.close();
        return true;
    }
    return false;
}

#endif
