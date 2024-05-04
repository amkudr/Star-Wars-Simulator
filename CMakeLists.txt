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
        Shuttle.h
        ImperialAgent.cpp
        ImperialAgent.h
        Midshipman.cpp
        Midshipman.h
        Commander.cpp
        Commander.h
        Admiral.cpp
        Admiral.h
        ImperialFactory.cpp
        ImperialFactory.h
        MidImperialFactory.cpp
        MidImperialFactory.h
        Spaceship.cpp
        Spaceship.h)
