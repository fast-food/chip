#ifndef MENU
#define MENU

#include "food.h"
#include <sstream>
#include <vector>

class Menu {
    private:
        float mPrice;
        std::vector<FoodType> mFoodTypes;

    public:
        Menu();
        Menu(float price);

        float getPrice() const;
        std::vector<FoodType> getFoodTypes() const;

        void setPrice(const float& price);
        void addFoodType(const FoodType& type);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
