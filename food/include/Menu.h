#ifndef DEF_MENU
#define DEF_MENU

#include "Food.h"

enum MenuSize {
    Small, Medium, Large
};

class Menu {
    private:
        MenuSize m_size;
        Food m_sandwich;
        Food m_extra;
        Food m_drink;
        Food m_dessert;
        float m_price;

    public:
        Menu();

        MenuSize getSize();
        Food getSandwich();
        Food getExtra();
        Food getDrink();
        Food getDessert();
        float getPrice();

        void setSize(MenuSize size);
        void setSandwich(Food sandwich);
        void setExtra(Food extra);
        void setDrink(Food drink);
        void setDessert(Food dessert);

        void updatePrice();

        friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
        friend std::istream& operator>>(std::istream& is, Menu& menu);
};

#endif
