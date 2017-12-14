#include <iostream>
#include "include/FoodUtils.h"

using namespace std;

int main(int argc, char const *argv[]) {
    std::vector<Menu> menus;
    loadMenus("menus", menus);

    Menu newMenu;

    int menuSize;
    float price;
    string name;

    cout << "###   Add a Menu  ###" << endl << endl;

    cout << "Menu size : ";
    cin >> menuSize;
    newMenu.setSize((MenuSize) menuSize);
    cin.ignore();

    cout << "Sandwich Name : ";
    getline(cin, name);
    cout << "Sandwich Price : ";
    cin >> price;
    newMenu.setSandwich(Food(name, price));
    cin.ignore();

    cout << "Extra Name : ";
    getline(cin, name);
    cout << "Extra Price : ";
    cin >> price;
    newMenu.setExtra(Food(name, price));
    cin.ignore();

    cout << "Drink Name : ";
    getline(cin, name);
    cout << "Drink Price : ";
    cin >> price;
    newMenu.setDrink(Food(name, price));
    cin.ignore();

    cout << "Dessert Name : ";
    getline(cin, name);
    cout << "Dessert Price : ";
    cin >> price;
    newMenu.setDessert(Food(name, price));
    cin.ignore();

    menus.push_back(newMenu);
    saveMenus("menus", menus);
    return 0;
}
