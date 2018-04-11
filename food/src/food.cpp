#include "../include/food.h"

Food::Food(){
    mId = -1;
    mType = FoodType::FoodType_UNDEFINED;
    mName = "";
}

Food::Food(const int& id, const FoodType& type, const std::string& name){
    mId = id;
    mType = type;
    mName = name;
}

int Food::getId() const{
    return mId;
}

FoodType Food::getType() const{
    return mType;
}

std::string Food::getName() const{
    return mName;
}

void Food::setId(const int& id){
    mId = id;
}

void Food::setType(const FoodType& type){
    mType = type;
}

void Food::setName(const std::string& name){
    mName = name;
}

void Food::write(std::ostream& os) const{
    os << mId << " ";
    os << mType << " ";
    os << mName;
}

void Food::read(std::istream& is){
    int type;
    is >> mId;
    is >> type;
    mType = (FoodType) type;
    is >> mName;
}
