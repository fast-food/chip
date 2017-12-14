#include "../include/Food.h"

Food::Food(){
    m_name = "";
    m_price = 0;
}
Food::Food(std::string name, float price){
    m_name = name;
    m_price = price;
}
Food::~Food(){
}

std::string Food::getName(){
    return m_name;
}
float Food::getPrice(){
    return m_price;
}

void Food::setName(std::string name){
    m_name = name;
}
void Food::setPrice(float price){
    m_price = price;
}

std::string Food::toJson() const{
    std::stringstream ss;
    ss << "{";
    ss << "\"name\":\"" << m_name << "\",";
    ss << "\"price\":" << m_price;
    ss << "}";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Food& food){
    os << food.m_name << std::endl;
    os << food.m_price;
    return os;
}
std::istream& operator>>(std::istream& is, Food& food){
    std::string line;
    getline(is, food.m_name);
    getline(is, line);
    food.m_price = std::stof(line);
    return is;
}
