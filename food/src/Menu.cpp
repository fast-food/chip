#include "../include/Menu.h"

Menu::Menu(){
}

MenuSize Menu::getSize(){
    return m_size;
}
Food Menu::getSandwich(){
    return m_sandwich;
}
Food Menu::getExtra(){
    return m_extra;
}
Food Menu::getDrink(){
    return m_drink;
}
Food Menu::getDessert(){
    return m_dessert;
}
float Menu::getPrice(){
    return m_price;
}

void Menu::setSize(MenuSize size){
    m_size = size;
    updatePrice();
}
void Menu::setSandwich(Food sandwich){
    m_sandwich = sandwich;
    updatePrice();
}
void Menu::setExtra(Food extra){
    m_extra = extra;
    updatePrice();
}
void Menu::setDrink(Food drink){
    m_drink = drink;
    updatePrice();
}
void Menu::setDessert(Food dessert){
    m_dessert = dessert;
    updatePrice();
}

void Menu::updatePrice(){
    m_price = m_sandwich.getPrice()+m_extra.getPrice()+m_drink.getPrice()+m_dessert.getPrice()+(m_size+1)*0.20f;
}

std::string Menu::toJson(){
    std::stringstream ss;
    ss << "{";
    ss << "\"price\":\"" << m_price << "\",";
    ss << "\"size\":\"" << m_size << "\",";
    ss << "\"sandwich\":" << m_sandwich.toJson() << ",";
    ss << "\"extra\":" << m_extra.toJson() << ",";
    ss << "\"drink\":" << m_drink.toJson() << ",";
    ss << "\"dessert\":" << m_dessert.toJson();
    ss << "}";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Menu& menu){
    os << menu.m_price << std::endl;
    os << menu.m_size << std::endl;
    os << menu.m_sandwich << std::endl;
    os << menu.m_extra << std::endl;
    os << menu.m_drink << std::endl;
    os << menu.m_dessert;
    return os;
}
std::istream& operator>>(std::istream& is, Menu& menu){
    std::string line;
    getline(is, line);
    menu.m_price = std::stof(line);
    getline(is, line);
    menu.m_size = (MenuSize) std::stoi(line);
    is >> menu.m_sandwich >> menu.m_extra >> menu.m_drink >> menu.m_dessert;
    return is;
}
