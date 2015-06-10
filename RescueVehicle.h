#ifndef RESCUEVEHICLE_H
#define RESCUEVEHICLE_H

#include "Vehicle.h"

// Oxima diaswsis, klironomei apo tin abstract class Vehicle gia ta oximata 
class RescueVehicle : public Vehicle {

protected:
    // static metabliti sinolikes epidiorthwseis
    static int total_repairs;
    
    // epidiorthwseis pou ehei kanei to oxima diaswsis
    int repairs;

public:
    // static function epistrefei tis sinolikes epidiorthwseis
    static int gettotalrepairs();

    // RescueVehicle constructors
    // neo discover oxima sto kosmo
    RescueVehicle(int, int, World*);
    // antigrafi discover oximatos 
    RescueVehicle(int, int, todo, bool, bool, RescueVehicle*);

    // get function -- epidiorthwseis pou ehei kanei to oxima
    int getrepairs();

    void info();    // plirofories

    // sinartisi metakinisis
    Vehicle* move(std::vector<int>&);

    // sinartisi leitourgias oximatos diaswsis
    Vehicle* operation(World*, std::vector<int>&);

    char repr_char();   // char pou anaparasta ta oximata eksereunisis
};

#endif