#include "DiscoverVehicle.h"
#include "World.h"

// static metabliti
int DiscoverVehicle::total_flags = 0;

int DiscoverVehicle::gettotalflags() {
    return total_flags;
}

// DiscoverVehicle constructor
// DiscoverVehicle constructor -- neo oxima eksereunisis sti thesi x,y tou kosmou w (pointer se kosmo)
DiscoverVehicle::DiscoverVehicle(int x, int y, World *w) : Vehicle(x, y, w) {
    flags = 0;
}

// oxima eksereunisis antigrafi apo pointer se iparxon oxima analisis av
DiscoverVehicle::DiscoverVehicle(int x, int y, todo td, bool broken, bool newdamage, DiscoverVehicle *dv) : Vehicle(x, y, td, broken, newdamage, dv) {
    flags = dv->getflags();
}

// epistrefei ton arithmo apo simaies kindinou pou ehei topothetisei
int DiscoverVehicle::getflags() {
    return flags;
}

// tipwnei plirofories gia to oxima eksereunisis
void DiscoverVehicle::info() {
    std::cout << "*** [DISCOVER] VEHICLE #" << code << " INFO ***" << std::endl;
    std::cout << "Discover vehicle has put " << flags << " danger flags" << std::endl;
    Vehicle::info();
}

// tipwnei to D gia tin anaparastasi tou oximatos eksereunisis sto xarti tou kosmou (virtual function)
char DiscoverVehicle::repr_char() {
    return 'D';
}

// sinartisi metakinisis tou oximatos analisis (orisma vector me ta codes apo ta katestramena oximata)
Vehicle* DiscoverVehicle::move(std::vector<int>& damaged) {
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
        return new DiscoverVehicle(ndimx, ndimy, OPERATE, broken, false, this);
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
            tomove = true; // metakineitai
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
    return new DiscoverVehicle(ndimx, ndimy, OPERATE, broken, broken, this);
}

// sinartisi leitourgias tou oximatos eksereunisis
// (orisma vector me ta codes apo ta katestramena oximata kai pointer se neo kosmo
// gia ton neo giro tis eksomeiwsis)
Vehicle* DiscoverVehicle::operation(World *w, std::vector<int>& damaged) {

    if (isatbase()) {
        // an einai sti vasi
        std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is at the base " 
            << dimx << "," << dimy << std::endl;
        return new DiscoverVehicle(dimx, dimy, MOVE, isbroken(), false, this);
    }

    if (isbroken()) {
        // an einai katestrameno
        std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is broken at " 
            << dimx << "," << dimy << std::endl;
        return new DiscoverVehicle(dimx, dimy, OPERATE, isbroken(), false, this);
    }

    Ground **panel = world->groundpanel();
    Ground **otherpanel = w->groundpanel();

    // an i epikindinotita prosvasis tou simeiou sto opoio vrisketai einai panw apo 0.6
    // topothetise simaia kindinou
    if (panel[dimx][dimy].getaccessdanger() > 0.6) {
        otherpanel[dimx][dimy].setflag();
        flags++;
        total_flags++;

        std::cout << "#" << code << " (" << repr_char() << ")" << " flagged ground at "
            << dimx << "," << dimy << " (danger " << panel[dimx][dimy].getaccessdanger() 
            << ")" << std::endl;
    }

    // antigrafi tou oximatos sto kosmo gia to neo giro
    return new DiscoverVehicle(dimx, dimy, MOVE, false, false, this);
}