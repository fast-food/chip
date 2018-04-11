#include "../include/foodUtils.h"

void toStream(std::ostream& os, const std::vector<Food>& food){
    os << food.size() << std::endl;
    for(const auto& f : food){
        f.write(os);
        os << " ";
    }
}

std::string toString(const std::vector<Food>& food){
    std::stringstream ss;
    toStream(ss, food);
    return ss.str();    
}

bool parseFood(const std::string& jsonStr, std::vector<Food>& food){
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(jsonStr.c_str(), root)){
        std::vector<std::string> foodNames = {"sandwich", "extra", "drink"};
        food.clear();
        for(const auto& name : foodNames){
            for(int i=0 ; i<root[name].size() ; i++){
                Food f(root[name][i]["id"].asInt(), (FoodType) root[name][i]["type"].asInt(), root[name][i]["name"].asString());
                food.push_back(f);
            }
        }
        return true;
    }
    return false;
}
