//
// Created by ben on 23/04/18.
//

#include "Customer.h"
#include "Menu.h"


Customer::Customer(int id, Stooper *s, Menu *menu) {
    this->id=id;
    this->stooper = s;
    this->menu= menu;
}

int Customer::start() {

    while(stooper->stillRun()){

        sleep(rand()%4+3);          //Sleep for 3 to 6 seconds, randomly
        sleep(1);                   //read the menu for 1 sec

        if(0){
            continue;
        }

        //make order
        if(rand()%2){

        }



    }
    return 0;
}
