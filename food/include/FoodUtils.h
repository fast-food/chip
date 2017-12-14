#ifndef DEF_FOODUTILS
#define DEF_FOODUTILS

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Menu.h"

static std::ostream& operator<<(std::ostream& os, const std::vector<Menu> &menus){
    int length = menus.size();
    os << length << std::endl;
    for(int i=0 ; i<length ; i++){
        os << menus[i];
        if(i!=length-1){
            os << std::endl;
        }
    }
    return os;
}

static std::istream& operator>>(std::istream& is, std::vector<Menu> &menus){
    std::string line;
    getline(is, line);
    int length = std::stoi(line);
    menus.resize(length);
    for(int i=0 ; i<length ; i++){
        is >> menus[i];
    }
    return is;
}

static bool saveMenus(std::string filename, const std::vector<Menu> &menus){
    std::ofstream file(filename.c_str());
    if(file){
        file << menus;
        file.close();
        return true;
    }
    return false;
}

static bool loadMenus(std::string filename, std::vector<Menu> &menus){
    std::ifstream file(filename.c_str());
    if(file){
        file >> menus;
        file.close();
        return true;
    }
    return false;
}

static std::string toJson(const std::vector<Menu> &menus){
    std::stringstream ss;
    ss << "[";
    for(int i=0 ; i<menus.size() ; i++){
        ss << menus[i].toJson();
        if(i!=menus.size()-1){
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

#endif
