#ifndef FOODUTILS
#define FOODUTILS

#include <fstream>
#include <sstream>
#include <vector>
#include <jsoncpp/json/json.h>

#include "food.h"

void writeFood(std::ostream& os, const std::vector<Food>& food);
bool writeFoodToFile(const std::string& filename, const std::vector<Food>& food);
void readFood(std::istream& is, std::vector<Food>& food);
bool readFoodFromFile(const std::string& filename, std::vector<Food>& food);
bool parseFood(const std::string& jsonStr, std::vector<Food>& food);

#endif
