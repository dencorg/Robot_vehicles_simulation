#ifndef SIMULATION_H
#define SIMULATION_H

#include "Ground.h"
#include "World.h"

// class gia ti prosomoiwsi
class Simulation {

private:
	// pointer sto world tis prosomoiwsis
	World *world;

	// sinolikes posotites sistatikwn sto kosmo
	int total_world_palladio;
	int total_world_iridio;
	int total_world_leukoxriso;

	// goal gia kathe sistatiko
	int palladio_goal;
	int iridio_goal;
	int leukoxriso_goal;

	// vector me ta codes twn oximatwn pou ehoun vlavi
	std::vector<int> damaged_vehicles;

	// giros tis prosomoiwsis
	int simulation_round;

public:
	// constructor (diastasi kosmou, arithmos oximatwn apo kathe katigoria, goals sistatikwn)
	Simulation(int, int, int, int, int);

	// trekse ena giro
	void run_one_round();

	// trekse 5 girous
	void run_five_rounds();

	// elegkse termatismo prosomoiwsis
	void checktermination();

	// functions gia plirofories gia kosmo, oximata
	void simulation_info();
	void showworld();
	void showdamaged();
	void showgroundspotinfo(int, int);
	void baseinfo();
	void vehiclesinfo();
	void vehicleinfo(int);

	// prosthese, ftiakse kai prokalese vlavi se oximata tou kosmou
	void addvehicle(int, int, int);
	void fixvehicle(int);
	void breakvehicle(int);
};

#endif