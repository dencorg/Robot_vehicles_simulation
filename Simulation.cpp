#include "Simulation.h"

// constructor (diastasi kosmou, arithmos oximatwn apo kathe katigoria,
// stoxos gia palladio, gia iridio, gia leukoxriso)
Simulation::Simulation(int dimension, int vehiclesnum, int pg, int ig, int lg) {
    // dimiourgise ton kosmo
    world = new World(dimension, vehiclesnum);

    // arxikopoiisi metavlitwn prosomoiwsis
    simulation_round = 0;
    palladio_goal = pg;
    iridio_goal = ig;
    leukoxriso_goal = lg;

    total_world_palladio = 0;
    total_world_iridio = 0;
    total_world_leukoxriso = 0;
    Ground **panel = world->groundpanel();

    // ipologismos sinolikou ogkou sistatikwn tou edafous 
    // k midenismos twn sistatikwn gia ti vasi
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if ( (i == world->getbasex()) && (j == world->getbasey()) ) {
                panel[i][j].setpalladiounits(0);
                panel[i][j].setiridiounits(0);
                panel[i][j].setleukoxrisounits(0);
            }
            total_world_palladio += panel[i][j].getpalladiounits();
            total_world_iridio += panel[i][j].getiridiounits();
            total_world_leukoxriso += panel[i][j].getleukoxrisounits();
        }
    }

}

// info gia ti prosomoiwsi (sinolika stats gia edafos)
void Simulation::simulation_info() {
    std::cout << "*** Simulation world info ***" << std::endl;
    std::cout << "Total paladio in world: " << total_world_palladio << std::endl;
    std::cout << "Total iridio in world: " << total_world_iridio << std::endl;
    std::cout << "Total leukoxriso in world: " << total_world_leukoxriso << std::endl;
}

// emfanisi kosmou tis prosomoiwsis
void Simulation::showworld() {
    world->showworld();
}

// emfanise katestramena oximata
void Simulation::showdamaged() {
    if (damaged_vehicles.empty())
        std::cout << "There are no broken vehicles";
    else {
        std::cout << "There are " << damaged_vehicles.size() << " broken vehicles, with codes:"
            << std::endl;
        for (std::vector<int>::iterator it = damaged_vehicles.begin(); it != damaged_vehicles.end(); ++it) {
            std::cout << *it << " ";
        }
    }
    std::cout << std::endl;
}

// plirofories gia ena sigekrimeno simeio tou edafous
void Simulation::showgroundspotinfo(int x, int y) {
    int dim = world->getdimension();

    if ( (x < dim ) && (x >= 0) && (y < dim) && (y >= 0) ) {
        Ground **panel = world->groundpanel();
        panel[x][y].info();
    } else {
        std::cout << "Invalid world spot" << std::endl;
    }
}

// plirofories gia ti vasi (sistatika pou ehoun mazeutei kai o stoxos pou exoume
// valei gia kathena apo auta)
void Simulation::baseinfo() {
    Ground **panel = world->groundpanel();
    std::cout << "*** Base Info (located at " << world->getbasex() << "," << world->getbasey()
        << ") ***" << std::endl;
    std::cout << "Palladio: " << panel[world->getbasex()][world->getbasey()].getpalladiounits() 
        << " (Goal: " << palladio_goal << ")" << std::endl;
    std::cout << "Iridio: " << panel[world->getbasex()][world->getbasey()].getiridiounits() 
        << " (Goal: " << iridio_goal << ")" << std::endl;
    std::cout << "Leukoxriso: " << panel[world->getbasex()][world->getbasey()].getleukoxrisounits() 
        << " (Goal: " << leukoxriso_goal << ")" << std::endl;
}

// sinolikes plirofories gia oximata tou kosmou
void Simulation::vehiclesinfo() {
    Vehicle::totalstats();
    showdamaged();
}

// plirofories gia sigekrimeno oxima me kwdiko code
void Simulation::vehicleinfo(int code) {
    Vehicle *v = world->getVehiclefromCode(code);
    if (v == NULL) {
        std::cout << "There is no vehicle with that code." << std::endl;
    } else {
        v->info();
    }
}

// prosthiki oximatas sti thesi x,y kai to eidos sto type
void Simulation::addvehicle(int x, int y, int type) {
    int dim = world->getdimension();

    if ( (x < dim) && (x >= 0) && (y < dim) && (y >= 0) ) {

        if ( (type == 1) || (type == 2) || (type == 3) ) {

            // prosthese analyse vehicle
            if (type == 1) {
                world->insertNewAnalyseVehicle(x, y);
                std::cout << "New Analyse Vehicle added." << std::endl;
            }

            // prosthese rescue vehicle
            if (type == 2) {
                world->insertNewRescueVehicle(x, y);
                std::cout << "New Rescue Vehicle added." << std::endl;
            }

            // prosthese discover vehicle
            if (type == 3) {
                world->insertNewDiscoverVehicle(x, y);
                std::cout << "New Discover Vehicle added." << std::endl;
            }

        } else {
            std::cout << "Invalid type input" << std::endl;
            return;
        }
 
    } else {
        std::cout << "Invalid world coordinates" << std::endl; 
    }
}

// epidiorthwse oxima me kwdiko code
void Simulation::fixvehicle(int code) {
    for (std::vector<int>::iterator it = damaged_vehicles.begin(); it != damaged_vehicles.end(); ++it) {
        if (*it == code) {
            Vehicle *v = world->getVehiclefromCode(*it);
            v->fixed();
            damaged_vehicles.erase(it);

            std::cout << "#" << v->getcode() << " (" << v->repr_char() << ")" << " is now fixed"
                << std::endl;
            return;
        }
    }
    std::cout << "No broken vehicle found with that code" << std::endl;
}

// prokalese vlavi sto oxima me kwdiko code
void Simulation::breakvehicle(int code) {
    Vehicle *v = world->getVehiclefromCode(code);
    if (v == NULL) {
        // an den iparxei
        std::cout << "There is no vehicle with that code." << std::endl;
    } else if (v->isbroken()) {
        // idi katestrameno
        std::cout << "Vehicle is already broken." << std::endl;
    } else {
        // prokalese vlavi k prosthese to sto vector me ta katestramena
        v->damaged();
        damaged_vehicles.push_back(v->getcode());
        std::cout << "#" << v->getcode() << " (" << v->repr_char() << ")" << " is now broken"
            << std::endl;
    }
}

// elegxos an termatise i prosomoiwsi
void Simulation::checktermination() {
    int total = Vehicle::gettotal();
    int damaged = damaged_vehicles.size();

    // an ola ta oximata einai katestramena termatise
    if (total == damaged) {
        std::cout << "***** Simulation Ends *****" << std::endl;
        std::cout << "All vehicles are broken!" << std::endl;
        std::cout << "***** Simulation Ends *****" << std::endl;

        exit(1);
    }

    Ground **panel = world->groundpanel();
    int bx = world->getbasex();
    int by = world->getbasey();

    // an exei mazeutei to apaitoumeno plithos sistatikwn termatise
    if ( ( panel[bx][by].getpalladiounits() >= palladio_goal ) && 
        ( panel[bx][by].getiridiounits() >= iridio_goal ) &&
        ( panel[bx][by].getleukoxrisounits() >= leukoxriso_goal ) )
    {
        std::cout << "***** Simulation Ends *****" << std::endl;

        std::cout << "Resources gathered!" << std::endl;
        std::cout << "UNITS: Palladio: " << panel[bx][by].getpalladiounits()
            << " -- Iridio: " << panel[bx][by].getiridiounits() 
            << " -- Leukoxriso: " << panel[bx][by].getleukoxrisounits() << std::endl; 

        std::cout << "***** Simulation Ends *****" << std::endl;

        exit(2);
    }  
}

// enas giros prosomoiwsis
void Simulation::run_one_round() {
    simulation_round++;
    std::cout << "*** Simulation round #" << simulation_round << " ***" << std::endl;
    int t = Vehicle::gettotal();
    World *nw = new World(world);

    // rescue oximata stin arxi giati droun epi twn allwn oximatwn
    for (int i = 0; i < t; ++i) {
        Vehicle *v = world->getVehicle(i);
        if (v->repr_char() == 'R') {
            // elegxos ti energeia kanoun meta
            if (v->gettodonext() == MOVE) {
                // metakinisi
                nw->insertVehicle(v->move(damaged_vehicles));
            } else {
                // leitourgia
                nw->insertVehicle(v->operation(nw, damaged_vehicles));
            }
        }
    }

    // ipoloipa oximata
    for (int i = 0; i < t; ++i) {
        Vehicle *v = world->getVehicle(i);
        if (v->repr_char() == 'R') continue;
        // elegxos ti energeia kanoun meta
        if (v->gettodonext() == MOVE) {
            // metakinisi
            nw->insertVehicle(v->move(damaged_vehicles));
        } else {
            // leitourgia
            nw->insertVehicle(v->operation(nw, damaged_vehicles));
        }
    }

    // neos kosmos prosomoiwsis
    world = nw;

    std::cout << "*** End of simulation round #" << simulation_round << " ***" << std::endl;
    checktermination(); // elegxos an prepei na termatistei i prosomoiwsi
}

// trekse 5 girous prosomoiwsis
void Simulation::run_five_rounds() {
    for (int i = 0; i < 5; ++i)
        run_one_round();
}