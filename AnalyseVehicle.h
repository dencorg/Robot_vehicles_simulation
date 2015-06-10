#ifndef ANALYSEVEHICLE_H
#define ANALYSEVEHICLE_H

#include "Vehicle.h"

// Oxima analisis, klironomei apo tin abstract class Vehicle gia ta oximata 
class AnalyseVehicle : public Vehicle {

protected:
    // static metabliti gia to sinoliko fortio pou eksorixthike
    static int vehicles_total_cargo_mined;
    
    int max_cargo;  // megisto fortio pou mporei na kouvalisei to oxima
    int palladio_cargo; // fortio palladiou
    int iridio_cargo;   // fortio iridiou
    int leukoxriso_cargo;   // fortio leukoxrisou
    int total_cargo_mined;  // sinoliko fortio pou eksorikse to oxima

public:
    static int get_vehiclestotalcargomined();

    // // AnalyseVehicle constructors
    // neo analyse oxima sto kosmo
    AnalyseVehicle(int, int, World*);
    // antigrafi analyse oximatos 
    AnalyseVehicle(int, int, todo, bool, bool, AnalyseVehicle*);

    // get methods
    int get_maxcargo();
    int get_palladiocargo();
    int get_iridiocargo();
    int get_leukoxrisocargo();
    int get_curcargomined();
    int get_totalcargomined();

    void info();    // tipwnei plirofories
    Vehicle* move(std::vector<int>&);   // sinartisi metaforas
    Vehicle* operation(World*, std::vector<int>&);  // sinartisi leitourgias

    char repr_char();   // char pou anaparasta ta oximata analisis
};

#endif