Student project in C++
---

Simulation of robotic resource gathering vehicles on an alien unknown world.
The vehicles may be damaged when moving around the world.
Vehicle variables are: speed, state (broken or not) and access capability
(how possible is to be broken during movement).
The ground spots have indications of how dangerous is to get to them.

There are three kinds of vehicles:
- Analyse vehicles (vehicles that mine the resources)
- Discover vehicles (vehicles that put flags on to indicate dangerous ground spots in the world)
- Rescue vehicles (vehicles that repair neighbour damaged vehicles)

The three resources are: 
- Palladio - Palladium
- Iridio - Iridium
- Leukoxrisos - Platinum

This is a student project so watch out :)
Source comments are in greek (more like greeklish).

Some simulation parameters such as world size, can be changed from Main.cpp.

Compile by running the make command.
```
make
./simulation
```
