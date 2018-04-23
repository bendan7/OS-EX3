//
// Created by ben on 23/04/18.
//

#ifndef HW3_MENU_H
#define HW3_MENU_H


#include "Dish.h"
using namespace std;
class Menu {

private:

public:
    int getNumOfDishes() const;

private:
    Dish **dishesArr;
    int numOfDishes;
    string names[7]= {"Spaghetti", "Pizza", "Salad", "Hamburger", "Pie", "Milkshake", "Tea"};

public:
    Menu(int numOfDishes);
    void print();


};

#endif //HW3_MENU_H
