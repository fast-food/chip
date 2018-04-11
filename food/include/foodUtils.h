#ifndef FOODUTILS
#define FOODUTILS

#include <fstream>
#include <sstream>
#include <vector>
#include <jsoncpp/json/json.h>

#include "food.h"

void toStream(std::ostream& os, const std::vector<Food>& food);
std::string toString(const std::vector<Food>& food);
bool parseFood(const std::string& jsonStr, std::vector<Food>& food);

#endif
