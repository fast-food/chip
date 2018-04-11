#include "../include/food.h"

Food::Food(){
    mId = -1;
    mName = "";
}

Food::Food(const int& id, const std::string& name){
    mId = id;
    mName = name;
}

int Food::getId() const{
    return mId;
}

std::string Food::getName() const{
    return mName;
}

void Food::setId(int id){
    mId = id;
}

void Food::setName(std::string name){
    mName = name;
}

void Food::write(std::ostream& os) const{
    os << mId << " " << mName;
}

void Food::read(std::istream& is){
    is >> mId;
    is >> mName;
}
