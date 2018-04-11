#ifndef FOOD
#define FOOD

#include <string>
#include <iostream>

class Food {
    private:
        int mId;
        std::string mName;

    public:
        Food();
        Food(const int& id, const std::string& name);

        int getId() const;
        std::string getName() const;

        void setId(int id);
        void setName(std::string name);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
