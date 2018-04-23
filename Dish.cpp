//
// Created by ben on 23/04/18.
//

#include "Dish.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include "chrono"
using namespace std;

Dish::Dish(const string &id, const string &name){
    this->id=id;
    this->name=name;
    this->price=rand()%101 ;
    totalOrder= 0;
}

const string &Dish::getId() const {
    return id;
}

void Dish::setId(const string &id) {
    Dish::id = id;
}

const string &Dish::getName() const {
    return name;
}

void Dish::setName(const string &name) {
    Dish::name = name;
}

float Dish::getPrice() const {
    return price;
}

void Dish::setPrice(float price) {
    Dish::price = price;
}

unsigned int Dish::getTotalOrder() const {
    return totalOrder;
}

void Dish::setTotalOrder(unsigned int totalOrder) {
    Dish::totalOrder = totalOrder;
}

void Dish:: printDish(){
    cout<< id<< "    "<< name;

    int len = name.size();

    for(int i = 0 ; i<11-len; i++){
        cout<<" ";
    }

    cout << price ;

    len = to_string(price).size();
    for(int i = 0 ; i<8-len; i++){
        cout<<" ";
    }
    cout <<totalOrder;
}