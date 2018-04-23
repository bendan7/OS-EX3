//
// Created by ben on 23/04/18.
//

#ifndef HW3_CUSTOMER_H
#define HW3_CUSTOMER_H

#include <iostream>
#include <unistd.h>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Stooper.h"
#include "Menu.h"
#include <time.h>
using namespace std;

struct Order {
    int customerId;
    int itemId;
    int amount;
    int done;
};

class Customer {
private:
    int cid;
    Stooper *stooper;
    Menu *menu;
    Order *segmem1ptr;

public:
    Customer(int id, Stooper *s, Menu *menu,  Order *segmem1ptr);

    int start();
    void makeOrder();


};


#endif //HW3_CUSTOMER_H
