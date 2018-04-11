#include "../include/menuUtils.h"

void writeMenus(std::ostream& os, const std::vector<Menu>& menus){
    os << menus.size() << std::endl;
    for(const auto& m : menus){
        m.write(os);
        os << " ";
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

bool parseMenus(const std::string& jsonStr, std::vector<Menu>& menus){
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(jsonStr.c_str(), root)){
        menus.clear();
        for(int i=0 ; i<root["menus"].size() ; i++){
            Menu menu(root["menus"][i]["price"].asFloat());
            for(int j=0 ; j<root["menus"][i]["food_type"].size() ; j++){
                FoodType type = (FoodType) root["menus"][i]["food_type"][j].asInt();
                menu.addFoodType(type);
                menus.push_back(menu);
            }
        }
        return true;
    }
    return false;
}
