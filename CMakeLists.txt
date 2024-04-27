cmake_minimum_required(VERSION 3.27)
project(HWFinal)

set(CMAKE_CXX_STANDARD 11)

add_executable(HWFinal main.cpp
        Controller.cpp
        Controller.h
        Model.cpp
        Model.h
        SpaceStation.cpp
        SpaceStation.h
        View.cpp
        View.h
        Shuttle.cpp
        Shuttle.h)
