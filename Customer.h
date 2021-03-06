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
#include<sys/ipc.h>
#include<sys/sem.h>
#define SEMPERM 0600
#define TRUE 1
#define FALSE 0
using namespace std;

struct Order {
    int customerId;
    int itemId;
    int amount;
    int done;
};

typedef union _semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}semun;

class Customer {
private:
    int cid;
    Stooper *stooper;
    Menu *menu;
    Order *segmem1ptr;
    key_t semkey;

public:
    Customer(int id, Stooper *s, Menu *menu,  Order *segmem1ptr,key_t semkey);

    int start();
    void makeOrder(int itemId,int amount);
    int initsem(key_t semkey);
    int v(int semid);
    int p(int semid);


};


#endif //HW3_CUSTOMER_H
