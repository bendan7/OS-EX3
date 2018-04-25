//
// Created by ben on 23/04/18.
//

#ifndef HW3_WAITER_H
#define HW3_WAITER_H

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
#include "Customer.h"
#define SEMPERM 0600
#define TRUE 1
#define FALSE 0
using namespace std;
//
//struct Order {
//    int customerId;
//    int itemId;
//    int amount;
//    int done;
//};

//typedef union _semun
//{
//    int val;
//    struct semid_ds *buf;
//    unsigned short *array;
//}semun;

class Waiter {
private:
    int wid;
    int numOfCust;
    Stooper *stooper;
    Menu *menu;
    Order *segmem1ptr;      //shared memory
    int *totalOrdersBoard;  //shared mem
    key_t semkey;
    key_t semkeyTotOrders;

public:
    Waiter(int id, Stooper *s, Menu *menu,  Order *segmem1ptr,key_t semkey, int numOfCust, int *totalOrdersBoard ,key_t semkeyTotOrders);

    int start();
    void serve(int orderNum);
    int initsem(key_t semkey);
    int v(int semid);
    int p(int semid);

};


#endif //HW3_WAITER_H
