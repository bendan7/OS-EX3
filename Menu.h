//
// Created by ben on 18/04/18.
//

#ifndef HW333_MENU_H
#define HW333_MENU_H

#include "Dish.h"
using namespace std;
class Menu {

private:


    Dish **dishesArr;
    int numOfDishes;
    string names[7]= {"Spaghetti", "Pizza", "Salad", "Hamburger", "Pie", "Milkshake", "Tea"};

public:
    Menu(int numOfDishes);
    void print();


};


#endif //HW333_MENU_H