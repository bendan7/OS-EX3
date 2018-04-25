//
// Created by ben on 23/04/18.
//

#include "Menu.h"


Menu::Menu(int numOfDishes){
    this->numOfDishes=numOfDishes;
    this->dishesArr= new Dish*[numOfDishes];

    srand(time(NULL));
    for(int i =0 ; i<numOfDishes ; i++){                            //fill the arr with dishes
        dishesArr[i]= new Dish(to_string(i+1), names[i]);

    }

}

void Menu::print(){
    cout << "===========Menu list===========\n";
    cout << "Id   Name       Price   Orders\n";
    for(int i =0 ; i<this->numOfDishes ; i++){
        dishesArr[i]->printDish();
        cout <<"\n";
    }
    cout << "===============================\n";


}

int Menu::getNumOfDishes() const {
    return numOfDishes;
}

void Menu::updateDishAmount(int index, int amount){
    dishesArr[index]->setTotalOrder(amount);

}