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


class Customer {
private:
    int id;
    Stooper *stooper;
    Menu *menu;

public:
    Customer(int id, Stooper *s, Menu *menu);

    int start();


};


#endif //HW3_CUSTOMER_H
