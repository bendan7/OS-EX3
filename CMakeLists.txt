cmake_minimum_required(VERSION 3.10)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw3 main.cpp Stooper.h Customer.cpp Customer.h Menu.cpp Menu.h Dish.cpp Dish.h Waiter.cpp Waiter.h)