//
// Created by ben on 22/04/18.
//

#ifndef HW3_STOOPER_H
#define HW3_STOOPER_H
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>


class Stooper {
private:
    std::chrono::system_clock::time_point startTime;
    bool isStart= false;

public:
    void start(){
        isStart=true;
        startTime = std::chrono::high_resolution_clock::now();
    }

    float getTimePass(){
        if(isStart== false)
            return ((double )0.000);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - startTime;
        return elapsed.count();
    }

    void reset(){
        start();
    }



};


#endif //HW3_STOOPER_H
