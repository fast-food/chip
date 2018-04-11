#ifndef MENU
#define MENU

#include "food.h"
#include <sstream>

enum MenuSize {
    SMALL,
    LARGE,
    UNDEFINED
};

class Menu {
    private:
        float mPrice;
        MenuSize mSize;
        Food mSandwich;
        Food mDrink;
        Food mExtra;

    public:
        Menu();
        Menu(MenuSize size, Food sandwich, Food drink, Food extra, float price);

        float getPrice() const;
        MenuSize getSize() const;
        Food getSandwich() const;
        Food getExtra() const;
        Food getDrink() const;

        void setPrice(float price);
        void setSize(MenuSize size);
        void setSandwich(Food sandwich);
        void setExtra(Food extra);
        void setDrink(Food drink);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
