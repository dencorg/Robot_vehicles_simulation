#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Simulation.h"


int main() {

    // seed for random numbers rand()
    srand(time(0));

    // 
    // Parametroi prosomoiwsis
    //

    // Kathorismos twn parametrwn

    // diastasi kosmou prosomeiwsis (nxn)
    int n = 20;

    // arithmos oximatwn gia kathe tipo oximatos
    // (nvehicles oximata analisis, nvehicles oximata eksereunisis, nvehicles oximata diaswsis)
    int nvehicles = 4;

    // stoxos na mazeutoun toses monades gia to kathena apo ta sistatika
    int goal = 300;

    //
    // Telos parametrwn
    //

    // dimiourgia simulation
    Simulation *s = new Simulation(n, nvehicles, goal, goal, goal);
    std::cout << "Starting simulation..." << std::endl;
    s->simulation_info();

    int option = 1;

    // loop
    while (true) {
        
        // odigies ston xristi
        std::cout << "*************** USAGE ********************" << std::endl;
        std::cout << "Press 1 for next simulation round" << std::endl;
        std::cout << "Press 2 to run five simulation rounds" << std::endl;
        std::cout << "Press 3 to show simulation world" << std::endl;
        std::cout << "Press 4 for ground spot info" << std::endl;
        std::cout << "Press 5 for base info" << std::endl;
        std::cout << "Press 6 for vehicles info" << std::endl;
        std::cout << "Press 7 for a vehicle info" << std::endl;
        std::cout << "Press 8 to add a vehicle" << std::endl;
        std::cout << "Press 9 to fix a vehicle" << std::endl;
        std::cout << "Press 10 to break a vehicle" << std::endl;
        std::cout << "Press 0 to exit" << std::endl;
        std::cout << "Waiting for user input (only number)..." << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cin >> option;

        // analoga tin epilogi tou xristi ektelese to akoloutho

        // an 1 trekse ena giro
        if (option == 1)
            s->run_one_round();

        // an 2 trekse 5 girous
        if (option == 2)
            s->run_five_rounds();

        // an 3 deikse ton kosmo tis prosomoiwsis
        if (option == 3)
            s->showworld();

        // an 4 emfanise stoixeia tou edafous gia tis sintetagmenes pou dinontai
        if (option == 4) {
            int x = 0;
            int y = 0;
            std::cout << "Give row number (x)" << std::endl;
            std::cin >> x;

            std::cout << "Give column number (y)" << std::endl;
            std::cin >> y;

            s->showgroundspotinfo(x, y);
        }

        // an 5 dwse plirofories gia ti basi
        if (option == 5)
            s->baseinfo();

        // an 6 dwse plirofories gia ta oximata tou kosmou
        if (option == 6)
            s->vehiclesinfo();

        // an 7 dwse plirofories gia to oxima me to sigekrimeno kwdiko/code
        if (option == 7) {
            int code;
            std::cout << "Enter vehicle code to get its info:" << std::endl;
            std::cin >> code;
            s->vehicleinfo(code);
        }

        // an 8 prosthese sti simulation to eidos oximatos kai ti thesi pou tha 
        // epilegoun apo ton xristi
        if (option == 8) {
            int type;
            int x;
            int y;

            std::cout << "Enter the type of vehicle to add:" << std::endl;
            std::cout << "Analyse: 1" << std::endl;
            std::cout << "Rescue: 2" << std::endl;
            std::cout << "Discover: 3" << std::endl;
            std::cin >> type;

            std::cout << "Where to put it in the world:" << std::endl;
            std::cout << "Give row number (x)" << std::endl;
            std::cin >> x;
            std::cout << "Give column number (y)" << std::endl;
            std::cin >> y;

            s->addvehicle(x, y, type);
        }

        // an 9 epidiorthwse to oxima me ton sigekrimeno kwdiko
        if (option == 9) {
            int code;
            std::cout << "Enter vehicle code to fix:" << std::endl;
            std::cin >> code;

            s->fixvehicle(code);
        }

        // an 10 pathainei vlavi to oxima me ton sigekrimeno kwdiko
        if (option == 10) {
            int code;
            std::cout << "Enter vehicle code to break:" << std::endl;
            std::cin >> code;

            s->breakvehicle(code);
        }

        // an 0 termatismos
        if (option == 0) {
            std::cout << "Exiting simulation..." << std::endl;
            exit(0);
        }

    }
  
}