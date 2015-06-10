#include "RescueVehicle.h"
#include "World.h"

// static metabliti
int RescueVehicle::total_repairs = 0;

int RescueVehicle::gettotalrepairs() {
    return total_repairs;
}

// RescueVehicle constructor
// DiscoverVehicle constructor -- neo oxima diaswsis sti thesi x,y tou kosmou w (pointer se kosmo)
RescueVehicle::RescueVehicle(int x, int y, World *w) : Vehicle(x, y, w) {
    repairs = 0;
}

// oxima diaswsis antigrafi apo pointer se iparxon oxima analisis av
RescueVehicle::RescueVehicle(int x, int y, todo td, bool broken, bool newdamage, RescueVehicle *rv) : Vehicle(x, y, td, broken, newdamage, rv) {
    repairs = rv->getrepairs();
}

// epistrefei ton arithmo epidiorthwsewn
int RescueVehicle::getrepairs() {
    return repairs;
}

// tipwnei plirofories oximatos diaswsis
void RescueVehicle::info() {
    std::cout << "*** [RESCUE] VEHICLE #" << code << " INFO ***" << std::endl;
    std::cout << "Rescue vehicle has repaired other vehicles " << repairs << " times" << std::endl;
    Vehicle::info();
}

// tipwnei to R gia tin anaparastasi tou oximatos eksereunisis sto xarti tou kosmou (virtual function)
char RescueVehicle::repr_char() {
    return 'R';
}

// sinartisi metakinisis tou oximatos diaswsis (orisma vector me ta codes apo ta katestramena oximata)
Vehicle* RescueVehicle::move(std::vector<int>& damaged) {
    int possible_pos[8];    // dinates theseis metakinisis
    int dim = world->getdimension();
    // if goes up
    possible_pos[0] = ((dimx - speed) < 0) ? 0 : (dimx - speed);
    possible_pos[1] = dimy;
    // if goes down
    possible_pos[2] = ((dimx + speed) > (dim - 1)) ? (dim - 1) : (dimx + speed);
    possible_pos[3] = dimy;
    // if goes left
    possible_pos[4] = dimx;
    possible_pos[5] = ((dimy - speed) < 0) ? 0 : (dimy - speed);
    // if goes right
    possible_pos[6] = dimx;
    possible_pos[7] = ((dimy + speed) > (dim - 1)) ? (dim - 1) : (dimy + speed);

    Ground **panel = world->groundpanel();
    bool tomove = false;
    int direction;
    int ndimx = dimx;
    int ndimy = dimy;
    int tries = 0;
    bool broken = isbroken();
    // an einai katestrameno
    if (broken) {
        std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is broken at "
            << ndimx << "," << ndimy << std::endl;
        // antegrapse to oxima ston kosmo gia ton epomeno giro
        return new RescueVehicle(ndimx, ndimy, OPERATE, broken, false, this);
    }

    while (!tomove) {
        ndimx = dimx;
        ndimy = dimy;
        tries++;    // prospatheies gia metakinisi (stis 4 apotiximenes prospatheis menei stin idia thesi)
        if (tries > 4) break;

        // me vasi ti kateuthini kathorizetai i epomeni thesi apo tis pithanes tou oximatos
        direction = rand() % 4; // rand kateuthinsi
        ndimx = possible_pos[direction * 2];
        ndimy = possible_pos[(direction * 2) + 1];

        if (!panel[ndimx][ndimy].hasflag()) {
            // an den iparxei simaia kindinou sto simeio proorismou
            tomove = true;  // metakineitai
            float broken_in_move = panel[ndimx][ndimy].getaccessdanger() * (1 - access_ability);
            if (broken_in_move > 0.7) {
                // elegxos an tha pathei zimia kata ti metakinisi
                broken = true;  // epathe zimia
                damaged.push_back(getcode());   // eisagwgi sta katestramena oximata
            }
        }
    }

    // plirofories gia ti metakinisi sti nea thesi kai gia to an epathe zimia
    std::cout << "#" << code << " (" << repr_char() << ")" << " moved from " << dimx << "," << dimy
        << " to " << ndimx << "," << ndimy;
    if (broken)
        std::cout << " -- Broken during the movement";
    std::cout << std::endl;

    // antegrapse to oxima ston kosmo gia ton epomeno giro
    return new RescueVehicle(ndimx, ndimy, OPERATE, broken, broken, this);
}

// sinartisi leitourgias tou oximatos diaswsis
// (orisma vector me ta codes apo ta katestramena oximata kai pointer se neo kosmo
// gia ton neo giro tis eksomeiwsis)
Vehicle* RescueVehicle::operation(World *w, std::vector<int>& damaged) {

    if (isatbase()) {
        // an einai sti basi
        std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is at the base " 
            << dimx << "," << dimy << std::endl;
        return new RescueVehicle(dimx, dimy, MOVE, isbroken(), false, this);
    }

    if (isbroken()) {
        // an einai katestrameno
        std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is broken at " 
            << dimx << "," << dimy << std::endl;
        return new RescueVehicle(dimx, dimy, OPERATE, isbroken(), false, this);
    }

    int dim = world->getdimension();
    int possible_rescue_pos[8]; // geitonikes theseis stis opoies psaxnei gia katestramena oximata
    // up
    possible_rescue_pos[0] = ((dimx - 1) < 0) ? 0 : (dimx - 1);
    possible_rescue_pos[1] = dimy;
    // down
    possible_rescue_pos[2] = ((dimx + 1) > (dim - 1)) ? (dim - 1) : (dimx + 1);
    possible_rescue_pos[3] = dimy;
    // left
    possible_rescue_pos[4] = dimx;
    possible_rescue_pos[5] = ((dimy - 1) < 0) ? 0 : (dimy - 1);
    // if goes right
    possible_rescue_pos[6] = dimx;
    possible_rescue_pos[7] = ((dimy + 1) > (dim - 1)) ? (dim - 1) : (dimy + 1);

    if (!damaged.empty()) {
        // an iparoun katestramena oximata
        std::vector<int>::iterator it = damaged.begin();
        // elegxos an ta katesramena oximata einai stis geitonikes theseis
        while (it != damaged.end()) {
            bool flag = false;
            Vehicle *damagedv = world->getVehiclefromCode(*it);
            for (int i = 0; i < 4; ++i) {
                if ( damagedv->isatspot(possible_rescue_pos[2*i], possible_rescue_pos[2*i + 1]) ) {
                    // oxima einai stis geitonikes theseis
                    damagedv->fixed();  // epidiorthwsi oximatos
                    std::cout << "#" << getcode() << " (" << repr_char() << ") " << "fixed vehicle #"
                        << damagedv->getcode() << " at " << possible_rescue_pos[2*i] << "," 
                        << possible_rescue_pos[2*i + 1] << std::endl;
                    it = damaged.erase(it); // diagrafi apo ton vector me ta katestramena oximata
                    flag = true;
                    break;
                }
            }
            if (!flag)
                ++it;
        }
    }

    // antigrafi tou oximatos sto kosmo gia to neo giro
    return new RescueVehicle(dimx, dimy, MOVE, false, false, this);
}