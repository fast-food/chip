#include "../include/menu.h"

Menu::Menu(){
    mSize = MenuSize::UNDEFINED;
    mPrice = 0;
}

Menu::Menu(MenuSize size, Food sandwich, Food drink, Food extra, float price){
    mSize = size;
    mSandwich = sandwich;
    mDrink = drink;
    mExtra = extra;
    mPrice = price;
}

float Menu::getPrice() const{
    return mPrice;
}

MenuSize Menu::getSize() const{
    return mSize;
}

Food Menu::getSandwich() const{
    return mSandwich;
}

Food Menu::getExtra() const{
    return mExtra;
}

Food Menu::getDrink() const{
    return mDrink;
}

void Menu::setPrice(float price){
    mPrice = price;
}

void Menu::setSize(MenuSize size){
    mSize = size;
}

void Menu::setSandwich(Food sandwich){
    mSandwich = sandwich;
}

void Menu::setExtra(Food extra){
    mExtra = extra;
}

void Menu::setDrink(Food drink){
    mDrink = drink;
}

void Menu::write(std::ostream& os) const{
    os << mPrice << std::endl;
    os << mSize << std::endl;
    mSandwich.write(os);
    os << std::endl;
    mDrink.write(os);
    os << std::endl;
    mExtra.write(os);
}

void Menu::read(std::istream& is){
    std::stringstream ss1,ss2,ss3;
    std::string line;
    getline(is, line);
    mPrice = std::stof(line);
    getline(is, line);
    mSize = (MenuSize) std::stoi(line);
    getline(is, line);
    ss1 << line;
    mSandwich.read(ss1);
    getline(is, line);
    ss2 << line;
    mDrink.read(ss2);
    getline(is, line);
    ss3 << line;
    mExtra.read(ss3);
}
