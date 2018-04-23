//
// Created by ben on 23/04/18.
//

#include "Customer.h"
#include "Menu.h"


Customer::Customer(int id, Stooper *s, Menu *menu,  Order *segmem1ptr) {
    this->cid=id;
    this->stooper = s;
    this->menu= menu;
    this->segmem1ptr= segmem1ptr;
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
            makeOrder();

        }



    }
    return 0;
}

void Customer::makeOrder() {
    int itemId= rand()%menu->getNumOfDishes();          //0-numofdishes
    int amount = rand()%4+1;                           //1-4 qty

    //semphore

    segmem1ptr[cid].customerId=cid;
    segmem1ptr[cid].amount=amount;
    segmem1ptr[cid].itemId=itemId;
    segmem1ptr[cid].done=0;

}
