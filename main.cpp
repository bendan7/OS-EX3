#include <iostream>
#include <unistd.h>
#include "Menu.h"
#include "Menu.cpp"
#include "Dish.h"
#include "Dish.cpp"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Stooper.h"

#include <time.h>


float GetTimePass(std::chrono::system_clock::time_point startTime);

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

    Stooper stooper;








//    cout << "====Simulation arguments====\n";
//    cout<< "simulation time: "<< simuTime<<"\n";
//    cout<< "Menu items count: "<< numOfDish << "\n";
//    cout << "Customers count: "<< coustNum<<"\n";
//    cout<< "Waiter count: 1"<< waiterNum<<"\n";


//-------------------------------shared memory creation-------------------

    //creation of shared memory
    sharedMemID = shmget(sharedMemKEY, 128 ,IPC_CREAT|IPC_EXCL|0666);

    //if shared memory allocated is faild
    if(sharedMemID==-1){
        cout<< "\nshared memory allocated faild!";
        return 1;
    }

//-------------------------------shared memory creation-END-------------------



    stooper.start();


    segmem1ptr = static_cast<char *>(shmat(sharedMemID, 0, 0));
    segmem1ptr[0]= '!';

    int pid =fork();
    if(pid<0){
        cout <<"\n fork is faild!";
        return 1;
    }


    if (pid==0){
        //son section

        sleep(3);
        cout<<stooper.getTimePass()<<"\n";


        exit(0);

    } else{
        //father section

        sleep(4);

        cout<<stooper.getTimePass();
        cout << segmem1ptr[0];


    }


    //Menu h(3);
   // h.print();


    // close the shared memory
    if(shmctl (sharedMemID, IPC_RMID, 0)==-1){
        cout<<"\n Shared memory didnt delete!!";
    }

    return 0;
}





