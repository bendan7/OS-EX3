//
// Created by ben on 18/04/18.
//

#ifndef HW333_DISH_H
#define HW333_DISH_H
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Dish {


private:

    string id;
    string name;
    int price;
    unsigned totalOrder;


public:
    Dish(const string &id, const string &name);

    const string &getId() const;

    void setId(const string &id);

    const string &getName() const;

    void setName(const string &name);

    float getPrice() const;

    void setPrice(float price);

    unsigned int getTotalOrder() const;

    void setTotalOrder(unsigned int totalOrder);


    void printDish();
};


#endif //HW333_DISH_H
