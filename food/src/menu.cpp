#include "../include/menu.h"

Menu::Menu(){
    mPrice = 0;
    mFoodTypes = std::vector<FoodType>();
}

Menu::Menu(float price){
    mPrice = price;
    mFoodTypes = std::vector<FoodType>();
}

float Menu::getPrice() const{
    return mPrice;
}

std::vector<FoodType> Menu::getFoodTypes() const{
    return mFoodTypes;
}

void Menu::setPrice(const float& price){
    mPrice = price;
}

void Menu::addFoodType(const FoodType& type){
    mFoodTypes.push_back(type);
}

void Menu::write(std::ostream& os) const{
    os << mPrice << " ";
    os << mFoodTypes.size() << " ";
    for(int i=0 ; i<mFoodTypes.size() ; i++){
        os << mFoodTypes[i];
        if(i<mFoodTypes.size()-1){
            os << " ";
        }
    }
}

void Menu::read(std::istream& is){
    int size, type;
    is >> mPrice;
    is >> size;
    for(int i=0 ; i<size ; i++){
        is >> type;
        mFoodTypes.push_back((FoodType) type);
    }
}
