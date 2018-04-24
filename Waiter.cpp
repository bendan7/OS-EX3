//
// Created by ben on 23/04/18.
//

#include "Waiter.h"

Waiter::Waiter(int id, Stooper *s, Menu *menu,  Order *segmem1ptr,key_t semkey, int numOfCust) {
    this->wid=id;
    this->stooper = s;
    this->menu= menu;
    this->segmem1ptr= segmem1ptr;
    this->semkey=semkey;
    this->numOfCust=numOfCust;
    cout<<fixed<<setprecision(3)<<stooper->getTimePass()<<" Waiter "<<wid<<": created PID "<<getpid()<< " PPID "<< getppid()<<"\n";
}

int Waiter::start() {

    srand(wid);                 //init rand seed by using waiter id

    while(stooper->stillRun()){     //run as long the simulation time not over

        sleep(rand()%2+1);          //Sleep for 1 to 2 seconds, randomly
        if(stooper->stillRun()==false)
            break;

        //search for un-done order
        for(int i=0; i<numOfCust;i++){
            if(segmem1ptr[i].done==0)
                serve(i);              //if the waiter find un-done order
        }

    }
    //end to work message
    cout<<fixed<<setprecision(3)<<stooper->getTimePass()<<" Waiter ID "<<wid<<": PID "<<getpid()<<" end work PPID "<<getppid()<<" \n";

    return 0;
}

void Waiter::serve(int orderNum) {

    int semid,custoID,amount,itemID;

    if( ( semid = initsem(this->semkey) ) < 0 ) {
        perror("init semaphore failed");
        exit(1);
    }

    //---------critical section---------
    p(semid);
    if(segmem1ptr[orderNum].done==0){
        segmem1ptr[orderNum].done=1;
        custoID=segmem1ptr[orderNum].customerId;
        amount=segmem1ptr[orderNum].amount;
        itemID=segmem1ptr[orderNum].itemId;

        //here come section that add the amount to the total.
        //
    }
    v(semid);
    cout<< fixed<<setprecision(3)<<stooper->getTimePass()<<" Waiter ID "<<wid<<": performs the order of customer ID "<<custoID<<" ("<<amount<<" "<<menu->getDishName(itemID) <<") \n";
}


int Waiter::p(int semid)
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

int Waiter::v(int semid)
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

int Waiter::initsem(key_t semkey)
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

