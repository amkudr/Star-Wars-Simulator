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
        ImperialAgent.h
        Midshipman.h
        Commander.h
        Admiral.h
        ImperialFactory.h
        MidImperialFactory.h
        Spaceship.cpp
        Spaceship.h
        TIEBomber.cpp
        TIEBomber.h
        StarDestroyer.cpp
        StarDestroyer.h
        Falcon.cpp
        Falcon.h
        ComImperalFactory.h
        AdmImperalFactory.h)
