#include "World.h"

World::World(int dim, int num_vehicles) {
    // arxikopoiisi
    dimension = dim;
    wp = new Ground*[dimension];
    for(int i = 0; i < dimension; ++i)
        wp[i] = new Ground[dimension];

    // topothetisi vasis sto kosmo
    basex = 1 + rand() % (dimension - 2);
    basey = 1 + rand() % (dimension - 2);
    wp[basex][basey].setbase();

    // dimiourgeia oximatos kai topothetisi sto kosmo
    for (int i = 0; i < num_vehicles; ++i) {
        int tmpx = helper_randomint();
        int tmpy = helper_randomint();
        insertNewDiscoverVehicle(tmpx, tmpy);

        tmpx = helper_randomint();
        tmpy = helper_randomint();
        insertNewRescueVehicle(tmpx, tmpy);

        tmpx = helper_randomint();
        tmpy = helper_randomint();
        insertNewAnalyseVehicle(tmpx, tmpy);
    }
}

// neos world apo iparxon world
World::World(World *otherworld) {
    // dimiourgia neou world
    dimension = otherworld->getdimension();
    basex = otherworld->getbasex();
    basey = otherworld->getbasey();
    Ground **panel = otherworld->groundpanel();

    // antigrafi tou pinaka me to edafos
    wp = new Ground*[dimension];
    for(int i = 0; i < dimension; ++i)
        wp[i] = new Ground[dimension];

    for(int i = 0; i < dimension; ++i) {
        for(int j = 0; j < dimension; ++j) {
            wp[i][j] = panel[i][j];
        }
    }
}

void World::insertNewDiscoverVehicle(int x, int y) {
    // eisagwgi neou discover vehicle ston world
    Vehicles.push_back(new DiscoverVehicle(x, y, this));
}

void World::insertNewRescueVehicle(int x, int y) {
    // eisagwgi neou rescue vehicle ston world
    Vehicles.push_back(new RescueVehicle(x, y, this));
}

void World::insertNewAnalyseVehicle(int x, int y) {
    // eisagwgi neou analyse vehicle ston world
    Vehicles.push_back(new AnalyseVehicle(x, y, this));
}

// eisagwgi iparxontos vehicle se allo world
void World::insertVehicle(Vehicle *v) {
    v->setworld(this);
    Vehicles.push_back(v);
}

// epistrefei ti diastasi tou kosmou
int World::getdimension() {
    return dimension;
}

// epitrefei to oxima apo ton vector Vehicles
Vehicle* World::getVehicle(int index) {
    if (index >= Vehicles.size())
        return NULL;
    return Vehicles[index];
}

// epistrefei to oxima vasi tou code
Vehicle* World::getVehiclefromCode(int code) {
    // anazitisi ston vector Vehicles
    for (std::vector<Vehicle *>::iterator it = Vehicles.begin(); it != Vehicles.end(); ++it) {
        if ((*it)->getcode() == code) {
            return (*it);
        }
    }
    return NULL;
}

// epestrepse pointer se disdiastato pinaka gia to edafos tou kosmou
Ground** World::groundpanel() {
    return wp;
}

// x / row tis basis
int World::getbasex() {
    return basex;
}

// y / column tis basis
int World::getbasey() {
    return basey;
}

// anaparastasi tou kosmou
void World::showworld() {
    std::cout << "*** WORLD REPRESENTATION ***" << std::endl;
    // pinakas gia proswrini apothikeusi twn pliroforiwn
    char panel[dimension][dimension];
    int bx = 0, by = 0;

    // plirofories sxetika me to edafos
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            // basi
            if (wp[i][j].isbase()) {
                panel[i][j] = 'B';
            } else if (wp[i][j].hasflag()) {
                // edafos me simaia kindinou
                panel[i][j] = 'F';
            } else {
                // kanoniko edafos
                panel[i][j] = 'X';
            }
        }
    }

    // oximata (kaliptoun to edafos)
    for (std::vector<Vehicle *>::iterator it = Vehicles.begin(); it != Vehicles.end(); ++it) {
        panel[(*it)->getrow()][(*it)->getcol()] = (*it)->repr_char();
    }

    // emfanisi pliroforiwn tou kosmou
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            std::cout << panel[i][j];
            if (j == (dimension - 1))
                std::cout << std::endl;
            else
                std::cout << " ";
        }
    }

    std::cout << std::endl;
    std::cout << "B: Base at " << basex << "," << basey << std::endl;
    std::cout << "F: Flag,  X: Normal ground" << std::endl;
    std::cout << "Vehicles: A is Analyse, D is Discover, R is Rescue" << std::endl;
    std::cout << "******" << std::endl;
}

// info gia ola ta vehicles
void World::vehiclesinfo() {
    for (std::vector<Vehicle *>::iterator it = Vehicles.begin(); it != Vehicles.end(); ++it) {
        (*it)->info();
    }
}

// voithitiki sinartisi tipwnei tixaio int sto diastima [0, dim - 1]
int World::helper_randomint() {
    return rand() % dimension;
}