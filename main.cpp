#include <iostream>
#include <unistd.h>
#include "Menu.h"

#include "Dish.h"

#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Stooper.h"
#include "Customer.h"
#include <time.h>
using namespace std;

/*struct Order {
    int customerId;
    int itemId;
    int amount;
    int done;
};*/

int main(void) {

    //init values
    int simuTime= 10;
    int numOfDish =5;
    int coustNum= 10;
    int waiterNum = 1;

    Stooper stooper(simuTime);
    Menu menu(numOfDish);

    //shared memory
    key_t sharedMemKEY = ftok(".",'b');
    int sharedMemID;
    Order *segmem1ptr;



//    cout << "====Simulation arguments====\n";
//    cout<< "simulation time: "<< simuTime<<"\n";
//    cout<< "Menu items count: "<< numOfDish << "\n";
//    cout << "Customers count: "<< coustNum<<"\n";
//    cout<< "Waiter count: 1"<< waiterNum<<"\n";


//-------------------------------shared memory creation-------------------
    //creation of shared memory
    sharedMemID = shmget(sharedMemKEY, sizeof(Order)*coustNum ,IPC_CREAT|IPC_EXCL|0666);

    //if shared memory allocated is faild
    if(sharedMemID==-1){
        perror("\nshared memory allocated faild!");
        exit(1);
    }

    segmem1ptr = (Order*)shmat(sharedMemID, 0, 0);
//-------------------------------shared memory creation-END-------------------


    stooper.start();

    segmem1ptr[0].amount=868;

    int pid =fork();

    if(pid<0){
        cout <<"\n fork is faild!";
        return 1;
    }


    if (pid==0){
        //son section

        Customer tomer(1,&stooper,&menu,segmem1ptr);
        tomer.start();

        exit(0);

    } else{
        //father section

        sleep(10);



    }



    //---------- close the shared memory-----------
    shmdt(segmem1ptr);
    if(shmctl (sharedMemID, IPC_RMID, NULL)==-1){
        cout<<"\n Shared memory didnt delete!!";
    }
    //---------- close the shared memory-END-----------
    return 0;
}

