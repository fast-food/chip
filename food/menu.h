#ifndef MENU
#define MENU

#include "food.h"

enum MenuSize {
    SMALL,
    LARGE,
    UNDEFINED
};

struct Menu {
    MenuSize mSize;
    Food mSandwich;
    Food mDrink;
    Food mExtra;
    float mPrice;

    Menu(){
        mSize = MenuSize::UNDEFINED;
        mPrice = 0;
    }

    Menu(MenuSize size, Food sandwich, Food drink, Food extra, float price){
        mSize = size;
        mSandwich = sandwich;
        mDrink = drink;
        mExtra = extra;
        mPrice = price;
    }

    void write(std::ostream& os) const{
        os << mPrice << std::endl;
        os << mSize << std::endl;
        mSandwich.write(os);
        os << std::endl;
        mDrink.write(os);
        os << std::endl;
        mExtra.write(os);
    }

    void read(std::istream& is){
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
};

#endif
