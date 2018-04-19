#include <iostream>
#include "Menu.h"
#include "Menu.cpp"
#include "Dish.h"
#include "Dish.cpp"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"

using namespace std;

int main(void) {

    //init values
    int simuTime= 15;
    int numOfDish =5;
    int coustNum= 2;
    int waiterNum = 1;

    //shared memory
    key_t sharedMemKEY = ftok(".",'a');
    int sharedMemID;
    char  *segmem1ptr;


//    clock_t start = clock();
//    clock_t now ;



    cout << "====Simulation arguments====\n";
    cout<< "simulation time: "<< simuTime<<"\n";
    cout<< "Menu items count: "<< numOfDish << "\n";
    cout << "Customers count: "<< coustNum<<"\n";
    cout<< "Waiter count: 1"<< waiterNum<<"\n";

    //creation of shared memory
    sharedMemID = shmget(sharedMemKEY, 128 ,IPC_CREAT|IPC_EXCL|0666);

    //if shared memory allocated is faild
    if(sharedMemID<0){
        cout<< "\nshared memory allocated faild!";
        return 1;
    }

    segmem1ptr = static_cast<char *>(shmat(sharedMemID, 0, 0));
    segmem1ptr[0]= '!';



    cout << sharedMemID;


    //Menu h(3);

   // h.print();




    return 0;
}