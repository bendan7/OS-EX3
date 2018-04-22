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

public:
    void start(){
        startTime = std::chrono::high_resolution_clock::now();
    }

    float getTimePass(){
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - startTime;
        return elapsed.count();
    }

    void reset(){
        start();
    }



};


#endif //HW3_STOOPER_H
