#include "../include/foodUtils.h"

void writeFood(std::ostream& os, const std::vector<Food>& food){
    os << food.size() << std::endl;
    for(const auto& f : food){
        f.write(os);
        std::cout << " ";
    }
}

bool writeFoodToFile(const std::string& filename, const std::vector<Food>& food){
    std::ofstream file(filename.c_str());
    if(file){
        writeFood(file, food);
        file.close();
        return true;
    }
    return false;
}

void readFood(std::istream& is, std::vector<Food>& food){
    std::string line;
    getline(is, line);
    int length = std::stoi(line);
    food.resize(length);
    for(int i=0 ; i<length ; i++){
        Food f;
        f.read(is);
        food[i] = f;
    }
}

bool readFoodFromFile(const std::string& filename, std::vector<Food>& food){
    std::ifstream file(filename.c_str());
    if(file){
        readFood(file, food);
        file.close();
        return true;
    }
    return false;
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
