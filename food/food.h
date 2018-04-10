#ifndef FOOD
#define FOOD

#include <string>
#include <iostream>

struct Food {
    int mId;
    std::string mName;

    Food(){
        mId = -1;
        mName = "";
    }

    Food(const int& id, const std::string& name){
        mId = id;
        mName = name;
    }

    void write(std::ostream& os) const{
        os << mId << " " << mName;
    }

    void read(std::istream& is){
        is >> mId;
        is >> mName;
    }
};

#endif
