#include <iostream>
#include <unistd.h>
#include "Menu.h"

#include "Dish.h"
#include <limits.h>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Stooper.h"
#include "Customer.h"
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include "Waiter.h"
#define SEMPERM 0600 /* permission for semaphore */

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
    int coustNum= 5;
    int waiterNum = 4;

    Stooper stooper(simuTime);
    Menu menu(numOfDish);



    //shared memory key
    key_t sharedMemKEY = ftok(".",'b');
    if(sharedMemKEY==-1){ perror("IPC error: ftok(sharedMemKEY)");exit(1);}

    //semaphore key
    key_t semkey = ftok(".",'a');

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

    //attach
    segmem1ptr = (Order*)shmat(sharedMemID, 0, 0);

    //init order status
    for(int i=0; i<coustNum; i++)
        segmem1ptr[i].done=-1;
//-------------------------------shared memory creation-END-------------------



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

        } else{                                                         //father section
            //main process section come here
        }
    }
    //---------------Customer creation-END---------------------




    //---------------Waiters creation---------------------
    for(int i=0;i<waiterNum;i++){
        int pid =fork();

        if(pid<0){ cout <<"\n fork is faild!";exit (1); }               //failed section

        if (pid==0){                                                    //son section
            Waiter waiter(i,&stooper,&menu,segmem1ptr,semkey,coustNum);
            waiter.start();
            exit(0);

        } else{                                                         //father section
            //main process section come here
        }
    }
    //---------------Waiters creation-END---------------------



    //HERE NEED TO COME THE PART THAT THE MAIN PROCESS WAIT FOR EVREYONE
    sleep(15);



    //---------- close the shared memory--------------
    shmdt(segmem1ptr);
    if(shmctl (sharedMemID, IPC_RMID, NULL)==-1){
        cout<<"\n Shared memory didnt delete!!";
    }
    //---------- close the shared memory-END-----------


    //---------- close the semaphore--------------
    semctl(semkey, 0, IPC_RMID, NULL);
    //---------- close the semaphore-END-----------



    return 0;
}




