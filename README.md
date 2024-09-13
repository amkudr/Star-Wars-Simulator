# Star Wars Simulation 

## Project Overview

This project is a simulation of a Star Wars-themed game based on the **Model-View-Controller** (MVC) paradigm.
The simulation revolves around the Galactic Empire, managing operations across space, including crystal transportation and combat against Rebel forces.

### Key Features:
- **Object-Oriented Design** using **C++**.
- Implements **design patterns**, specifically the **Singleton** and **Abstract Factory** patterns.
- Simulates space battles, transportation, and patrolling using various spaceship types.
- Follows a 2D Euclidean space model for the Galactic Empire's operations.

## Components

### 1. **Model**
- Manages all simulation objects, including agents (spaceships and stations), and handles interactions between them.
- Ensures the simulation progresses in discrete time steps, updating the state of all objects.

### 2. **View**
- Displays the state of the simulation as an ASCII map.
- Visualizes objects using the first two letters of their names.

### 3. **Controller**
- Manages user input and controls the simulation.
- Routes user commands to update the simulation state.

## Simulation Objects

### Galactic Empire Spaceships:
- **Shuttle**: Transports crystals between stations and fortresses.
- **TIE Bomber**: Patrols space and attacks enemies.
- **Star Destroyer**: Engages in long-range combat and patrols.

### Rebel Spaceship:
- **Millennium Falcon**: A smuggler ship attacking Imperial shuttles.

### Stations & Fortresses:
- **Space Station**: Produces crystals and stores them in tanks.
- **Fortress Star**: Stores crystals and serves as a target for shuttle transport.

## Key Commands

- **create**: Creates spaceships and agents (shuttle, bomber, destroyer, falcon).
- **go**: Advances the simulation by one time step (1 hour).
- **status**: Displays the current state of all simulation objects.
- **course**: Sets the course and speed of a spaceship.
- **destination**: Sets a destination for a spaceship.
- **start_supply**: Commands shuttles to begin transporting crystals between stations and fortresses.

## How to Run

1. Compile the project using a **C++11** compatible compiler:
   ```bash
   g++ -std=c++11 main.cpp -o simST
2. Run the simulation with the input file describing the locations of stations and fortresses:
   ```bash 
   ./simST sites.dat \
   ``` \

3. Enter commands to control the simulation. Example commands:
   ```bash 
   create destroyer T0 Tarkin (24.00, 24.00) 
   create falcon Millennium (42.00, 42.00) 
   T0 course 180 2000 
   Millennium course 270 3000 
   go 
   status 
   ``` 

## File Structure

- `main.cpp`: Contains the `main` function and sets up the simulation controller.
- `Controller.h`, `Controller.cpp`: Handles user input and controls the flow of the simulation.
- `Model.h`, `Model.cpp`: Manages all the objects and their states in the simulation.
- `View.h`, `View.cpp`: Displays the current state of the simulation as an ASCII map.
- `spaceship.h`, `spaceship.cpp`: Defines the behavior and attributes of the spaceships.
- `station.h`, `station.cpp`: Defines the behavior and attributes of stations and fortresses.

## Dependencies

- **C++11 or later** for smart pointer usage and move semantics.
- No external libraries required.

