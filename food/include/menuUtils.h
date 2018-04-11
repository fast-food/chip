#ifndef MENUUTILS
#define MENUUTILS

#include <fstream>
#include <sstream>
#include <vector>
#include <jsoncpp/json/json.h>

#include "menu.h"

void toStream(std::ostream& os, const std::vector<Menu>& menus);
std::string toString(const std::vector<Menu>& menus);
bool parseMenus(const std::string& jsonStr, std::vector<Menu>& menus);

#endif
