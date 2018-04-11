#ifndef FOOD
#define FOOD

#include <string>
#include <iostream>

#include "foodType.h"

class Food {
    private:
        int mId;
        FoodType mType;
        std::string mName;

    public:
        Food();
        Food(const int& id, const FoodType& type, const std::string& name);

        int getId() const;
        FoodType getType() const;
        std::string getName() const;

        void setId(const int& id);
        void setType(const FoodType& type);
        void setName(const std::string& name);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
