#include <iostream>
#include <unistd.h>
#include "Menu.h"
#include  <stdio.h>
#include <stdlib.h>
#include "Dish.h"
#include <limits.h>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Stooper.h"
#include "Customer.h"
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include "Waiter.h"
#define SEMPERM 0600 /* permission for semaphore */

using namespace std;


int main(int argc, char* args[]) {

    if(argc!=5 ){
        cout<<"Input argumenets ar not valid!\n";
        return 1;
    }

    //init values
    int simuTime= atoi(args[1]);
    int numOfDish =atoi(args[2]);;
    int coustNum= atoi(args[3]);;
    int waiterNum = atoi(args[4]);;

    Stooper stooper(simuTime);
    Menu menu(numOfDish);



    //shared memory key
    key_t sharedMemKEY = ftok(".",'b');
    if(sharedMemKEY==-1){ perror("IPC error: ftok(sharedMemKEY)");exit(1);}

    key_t ordersKey = ftok(".",'c');
    if(ordersKey==-1){ perror("IPC error: ftok(sharedMemKEY)");exit(1);}

    //semaphore key
    key_t semkey = ftok(".",'a');
    key_t semkeyTotOrders = ftok(".",'d');

    int sharedMemID;
    Order *segmem1ptr;

    int totalOrdersID;
    int *totalOrdersBoard;


//-------------------------------shared memory creation-------------------
    //creation of shared memory
    sharedMemID = shmget(sharedMemKEY, sizeof(Order)*coustNum ,IPC_CREAT|IPC_EXCL|0666);
    totalOrdersID= shmget(ordersKey, sizeof(int)*numOfDish ,IPC_CREAT|IPC_EXCL|0666);

    //if shared memory allocated is faild
    if(sharedMemID==-1 || totalOrdersID==-1 ){
        perror("\nshared memory allocated faild!");
        exit(1);
    }

    //attach
    segmem1ptr = (Order*)shmat(sharedMemID, 0, 0);
    totalOrdersBoard = (int*)shmat(totalOrdersID, 0, 0);

    //init order status
    for(int i=0; i<coustNum; i++)
        segmem1ptr[i].done=-1;

    //init amount of orders to zero
    for(int i=0; i<numOfDish;i++)
        totalOrdersBoard[i]=0;

//-------------------------------shared memory creation-END-------------------



    cout << "=====Simulation arguments=====\n";
    cout<< "simulation time: "<< simuTime<<"\n";
    cout<< "Menu items count: "<< numOfDish << "\n";
    cout << "Customers count: "<< coustNum<<"\n";
    cout<< "Waiter count: "<< waiterNum<<"\n";
    cout << "===============================\n";
    cout << "0.000 Main process ID "<<getpid()<< " start\n";
    menu.print();
    stooper.start();   //start the stopwatch
    cout<<fixed<<setprecision(3)<<stooper.getTimePass()<<" Main process start creating sub-process\n";



    //---------------Customer creation---------------------

    for(int i=0;i<coustNum;i++){
        int pid =fork();
        if(pid<0){ cout <<"\n fork is faild!";exit (1); }               //failed section
        if (pid==0){                                                    //son section
            Customer customer(i,&stooper,&menu,segmem1ptr,semkey);
            customer.start();
            exit(0);
        } else{}                                                         //father section
    }
    //---------------Customer creation-END---------------------


    //---------------Waiters creation---------------------
    for(int i=0;i<waiterNum;i++){
        int pid =fork();
        if(pid<0){ cout <<"\n fork is faild!";exit (1); }               //failed section
        if (pid==0){                                                    //son section
            Waiter waiter(i,&stooper,&menu,segmem1ptr,semkey,coustNum,totalOrdersBoard,semkeyTotOrders);
            waiter.start();
            exit(0);
        } else{}                                                        //father section
    }
    //---------------Waiters creation-END---------------------


    //main process wait for all child processes
    int status;
    while(wait(&status) > 0) { /* just chill :) */ ; }
    cout <<"\n";

    //update the total order into the menu
    int totalAmount=0, totalPrice=0;
    for(int i=0 ; i<numOfDish; i++){
        menu.updateDishAmount(i,totalOrdersBoard[i]);
        totalAmount+=totalOrdersBoard[i];
        totalPrice+=totalOrdersBoard[i]*menu.getDishPrice(i);

    }
    menu.print();
    cout<<"Total order "<<totalAmount<<", for an anount "<<totalPrice<<" NIL\n";



    //---------- close the shared memory--------------
    shmdt(segmem1ptr);
    if(shmctl (sharedMemID, IPC_RMID, NULL)==-1){
        cout<<"\n Shared memory didnt delete!!";
    }
    shmdt(totalOrdersBoard);
    if(shmctl (totalOrdersID, IPC_RMID, NULL)==-1){
        cout<<"\n Shared memory didnt delete!!";
    }
    //---------- close the shared memory-END-----------


    //---------- close the semaphores--------------
    semctl(semkey, 0, IPC_RMID, NULL);
    semctl(semkeyTotOrders, 0, IPC_RMID, NULL);
    //---------- close the semaphores-END-----------

    cout<<fixed<<setprecision(3)<<stooper.getTimePass()<<" Main ID "<<getpid()<<" end work\n";
    cout<<fixed<<setprecision(3)<<stooper.getTimePass()<<" End of simulation\n";



    return 0;
}




