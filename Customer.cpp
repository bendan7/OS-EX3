//
// Created by ben on 23/04/18.
//

#include "Customer.h"
#include "Menu.h"


Customer::Customer(int id, Stooper *s, Menu *menu,  Order *segmem1ptr,key_t semkey) {
    this->cid=id;
    this->stooper = s;
    this->menu= menu;
    this->segmem1ptr= segmem1ptr;
    this->semkey=semkey;
    cout<<fixed<<setprecision(3)<<stooper->getTimePass()<<" Customer "<<cid<<": created PID "<<getpid()<< " PPID "<< getppid()<<"\n";
}

int Customer::start() {

    srand(getpid());                 //init rand seed by using getpid

    while(stooper->stillRun()){     //run as long the simulation time not over

       sleep(rand()%4+3);          //Sleep for 3 to 6 seconds, randomly

        if(segmem1ptr[cid].done==0 ){  //if the last order didn't serve yet by waiter
            continue; }

        int itemId= rand()%menu->getNumOfDishes();          //0-numofdishes
        int amount = rand()%4+1;                           //1-4 qty
        int yesOrNo= rand()%2;



        //read the menu for 1 sec
        sleep(1);
        if(stooper->stillRun()==false)
            break;
        cout<<fixed<<setprecision(3)<<stooper->getTimePass()<<" Customer ID "<<cid<<": reads a menu about "<<menu->getDishName(itemId);

        //make order
        if(yesOrNo){
            cout<<" (ordered, amount "<<amount<<" )\n";
            makeOrder(itemId,amount);
        }
        else cout<<" (doesn't want to order)\n";

    }

    //end to work message
    cout<<fixed<<setprecision(3)<<stooper->getTimePass()<<" Customer ID "<<cid<<": PID "<<getpid()<<" end work PPID "<<getppid()<<" \n";

    return 0;
}

void Customer::makeOrder(int itemId,int amount ) {

    int semid;
    pid_t pid = getpid();

    if( ( semid = initsem(this->semkey) ) < 0 ) {
        perror("init semaphore failed");
        exit(1);
    }


    //---------critical section---------
    p(semid);
    segmem1ptr[cid].customerId=cid;
    segmem1ptr[cid].amount=amount;
    segmem1ptr[cid].itemId=itemId;
    segmem1ptr[cid].done=0;
    v(semid);

}


int Customer::p(int semid)
{
    struct sembuf p_buf;
    p_buf.sem_num = 0;
    p_buf.sem_op = -1;
    p_buf.sem_flg = SEM_UNDO;

    //int semop(int semid, struct sembuf *sops, size_t nsops);
    if( semop(semid, &p_buf, 1) == -1 )
    {
        perror("Error operation p(semid)");
        exit(1);
    }
    return 0;
}
int Customer::v(int semid)
{
    struct sembuf v_buf;
    v_buf.sem_num = 0;
    v_buf.sem_op = 1;
    v_buf.sem_flg = SEM_UNDO;

    //int semop(int semid, struct sembuf *sops, size_t nsops);
    if( semop(semid, &v_buf, 1) == -1 )
    {
        perror("Error operation v(semid)");
        exit(1);
    }
    return 0;
}
int Customer::initsem(key_t semkey)
{
    int status = 0, semid;

    //int semget(key_t key, int nsems, int semflg);
    if( ( semid = semget(semkey, 1, SEMPERM | IPC_CREAT | IPC_EXCL ) ) == -1 )
    {
        if( errno == EEXIST )
        {
            semid = semget( semkey, 1, 0 );
        }
    }
    else
    {
        union _semun arg;

        arg.val = 1;

        // int semctl(int semid, int semnum, int cmd, union semun arg);
        status = semctl(semid, 0, SETVAL, arg);
    }

    if( semid == -1 || status == -1 )
    {
        perror("Error initsem");
        exit(-1);
    }
    return (semid);
}

