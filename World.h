#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>

#include "Ground.h"
#include "AnalyseVehicle.h"
#include "RescueVehicle.h"
#include "DiscoverVehicle.h"

// class gia plirofories tou kosmou tis prosomoiwsis
class World {

private:
    // world dimension
    int dimension;

    // basi
    int basex;
    int basey;

    // pointer se pointer pou anaparista to kosmo tis prosomoiwsis
    Ground **wp;

    // vector pou periexei ta vehicles pou iparxoun sto kosmo
    std::vector<Vehicle *> Vehicles;

public:
    // constructors
    // (diastasi kosmou, plithos gia kathe eidos oximatwn)
    World(int, int);
    // constructor apo iparxon kosmo
    World(World*);

    // functions gia eisagwgi vehicles
    // eisagwgi newn oximatwn
    void insertNewDiscoverVehicle(int, int);
    void insertNewRescueVehicle(int, int);
    void insertNewAnalyseVehicle(int, int);

    // eisagwgi ston kosmo tis prosomoiwsis (allazei o kosmos se kathe giro
    // gia na fanoun oi allages)
    void insertVehicle(Vehicle*);

    // diastasi kosmou
    int getdimension();

    // epestrepse poitner sto sigekrimeno vehicle
    Vehicle* getVehicle(int);
    Vehicle* getVehiclefromCode(int);

    // o disdiastatos pinakas me to edafos tou kosmou
    Ground** groundpanel();

    // info gia world k oximata
    void showworld();
    void vehiclesinfo();

    // sintetagmenes tis vasis
    int getbasex();
    int getbasey();

    // random int anamesa se 0 kai (dimension - 1)
    int helper_randomint();
};

#endif