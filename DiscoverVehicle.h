#ifndef DISCOVERVEHICLE_H
#define DISCOVERVEHICLE_H

#include "Vehicle.h"

// Oxima analisis, klironomei apo tin abstract class Vehicle gia ta oximata 
class DiscoverVehicle : public Vehicle {

protected:
    // static metavliti sinolikes simaies
    static int total_flags;
    
    // simaies kindinou pou ehei valei to oxima eksereunisis
    int flags;

public:
    // static function
    static int gettotalflags();

    // DiscoverVehicle constructors
    // neo discover oxima sto kosmo
    DiscoverVehicle(int, int, World*);
    // antigrafi discover oximatos 
    DiscoverVehicle(int, int, todo, bool, bool, DiscoverVehicle*);

    // get function - simaies kindinou pou ehei topothetisei
    int getflags();

    void info();    // plirofories
    // sinartisi metakinisis
    Vehicle* move(std::vector<int>&);

    // sinartisi leitourgias discover vehicle
    Vehicle* operation(World*, std::vector<int>&);

    char repr_char();   // char pou anaparasta ta oximata eksereunisis
};

#endif