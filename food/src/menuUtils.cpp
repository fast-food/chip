#include "../include/menuUtils.h"

void toStream(std::ostream& os, const std::vector<Menu>& menus){
    os << menus.size() << std::endl;
    for(const auto& m : menus){
        m.write(os);
        os << " ";
    }
}

std::string toString(const std::vector<Menu>& menus){
    std::stringstream ss;
    toStream(ss, menus);
    return ss.str();
}

bool parseMenus(const std::string& jsonStr, std::vector<Menu>& menus){
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(jsonStr.c_str(), root)){
        menus.clear();
        for(int i=0 ; i<root.size() ; i++){
            Menu menu(root[i]["price"].asFloat());
            for(int j=0 ; j<root[i]["food_type"].size() ; j++){
                FoodType type = (FoodType) root[i]["food_type"][j].asInt();
                menu.addFoodType(type);
            }
            menus.push_back(menu);
        }
        return true;
    }
    return false;
}
