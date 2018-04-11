#ifndef MENUUTILS
#define MENUUTILS

#include <fstream>
#include <sstream>
#include <vector>
#include <jsoncpp/json/json.h>

#include "menu.h"

void writeMenus(std::ostream& os, const std::vector<Menu>& menus);
bool writeMenusToFile(const std::string& filename, const std::vector<Menu>& menus);
void readMenus(std::istream& is, std::vector<Menu>& menus);
bool readMenusFromFile(const std::string& filename, std::vector<Menu>& menus);
bool parseMenus(const std::string& jsonStr, std::vector<Menu>& menus);

#endif
