#ifndef DEF_FOOD
#define DEF_FOOD

#include <iostream>
#include <sstream>
#include <string>

class Food {
    protected:
        std::string m_name;
        float m_price;

    public:
        Food();
        Food(std::string name, float price);
        virtual ~Food();

        std::string getName();
        float getPrice();

        void setName(std::string name);
        void setPrice(float price);

        std::string toJson() const;

        friend std::ostream& operator<<(std::ostream& os, const Food& food);
        friend std::istream& operator>>(std::istream& is, Food& food);
};

#endif
