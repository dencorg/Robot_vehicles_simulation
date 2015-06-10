#include "AnalyseVehicle.h"
#include "World.h"

// static
int AnalyseVehicle::vehicles_total_cargo_mined = 0;

int AnalyseVehicle::get_vehiclestotalcargomined() {
    return vehicles_total_cargo_mined;
}

// AnalyseVehicle constructor -- neo oxima analisis sti thesi x,y tou kosmou w (pointer se kosmo)
AnalyseVehicle::AnalyseVehicle(int x, int y, World *w) : Vehicle(x, y, w) {
    max_cargo = 200;    // MAX_CARGO
    palladio_cargo = 0;
    iridio_cargo = 0;
    leukoxriso_cargo = 0;
    total_cargo_mined = 0;
}

// oxima analisis antigrafi apo pointer se iparxon oxima analisis av
AnalyseVehicle::AnalyseVehicle(int x, int y, todo td, bool broken, bool newdamage, AnalyseVehicle *av) : Vehicle(x, y, td, broken, newdamage, av) {
    max_cargo = av->get_maxcargo();
    palladio_cargo = av->get_palladiocargo();
    iridio_cargo = av->get_iridiocargo();
    leukoxriso_cargo = av->get_leukoxrisocargo();
    total_cargo_mined = av->get_totalcargomined();
}

// get methods
int AnalyseVehicle::get_maxcargo() {
    return max_cargo;
}

int AnalyseVehicle::get_palladiocargo() {
    return palladio_cargo;
}

int AnalyseVehicle::get_iridiocargo() {
    return iridio_cargo;
}

int AnalyseVehicle::get_leukoxrisocargo() {
    return leukoxriso_cargo;
}

int AnalyseVehicle::get_curcargomined() {
    return palladio_cargo + iridio_cargo + leukoxriso_cargo;
}

int AnalyseVehicle::get_totalcargomined() {
    return total_cargo_mined;
}

// tipwnei plirofories gia to oxima analisis
void AnalyseVehicle::info() {
    std::cout << "*** [ANALYSE] VEHICLE #" << code << " INFO ***" << std::endl;
    std::cout << "Analyse Vehicle current total cargo: " << get_curcargomined() << " (MAX: " << max_cargo << ")" << std::endl;
    std::cout << ">> Palladio: " << palladio_cargo << " -- Iridio: " << iridio_cargo << " -- Leukoxriso: " << leukoxriso_cargo << " <<" << std::endl; 
    Vehicle::info();
}

// tipwnei to A gia tin anaparastasi tou oximatos analisis sto xarti tou kosmou (virtual function)
char AnalyseVehicle::repr_char() {
    return 'A';
}

// sinartisi metakinisis tou oximatos analisis (orisma vector me ta codes apo ta katestramena oximata)
Vehicle* AnalyseVehicle::move(std::vector<int>& damaged) {
    int possible_pos[8];    // dinates theseis metakinisis
    int dim = world->getdimension();
    // panw
    possible_pos[0] = ((dimx - speed) < 0) ? 0 : (dimx - speed);
    possible_pos[1] = dimy;
    // katw
    possible_pos[2] = ((dimx + speed) > (dim - 1)) ? (dim - 1) : (dimx + speed);
    possible_pos[3] = dimy;
    // aristera
    possible_pos[4] = dimx;
    possible_pos[5] = ((dimy - speed) < 0) ? 0 : (dimy - speed);
    // deksia
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
        return new AnalyseVehicle(ndimx, ndimy, OPERATE, broken, false, this);
    }

    while (!tomove) {
        ndimx = dimx;
        ndimy = dimy;
        tries++;    // prospatheies gia metakinisi (stis 4 apotiximenes prospatheis menei stin idia thesi)
        if (tries > 4) break;

        direction = rand() % 4; // tixaia katheuthinsi tou oximatos me xrisi rand()

        // me vasi ti kateuthini kathorizetai i epomeni thesi apo tis pithanes tou oximatos
        ndimx = possible_pos[direction * 2];
        ndimy = possible_pos[(direction * 2) + 1];

        if (!panel[ndimx][ndimy].hasflag()) {
            // an den iparxei simaia kindinou sto simeio proorismou
            tomove = true;  // metakineitai
            float broken_in_move = panel[ndimx][ndimy].getaccessdanger() * (1 - access_ability);
            // elegxos an tha pathei zimia kata ti metakinisi
            if (broken_in_move > 0.7) {
                // epathe zimia
                broken = true;
                damaged.push_back(getcode());   // eisagwgi sta katestramena oximata
            }
        }
    }

    // plirofories gia ti metakinisi sti nea thesi kai gia to an epathe zimia
    std::cout << "#" << code << " (" << repr_char() << ")" << " moved from " << dimx << "," << dimy
        << " to " << ndimx << "," << ndimy;
    if (broken) {
        std::cout << " -- Broken during the movement";
    }
    std::cout << std::endl;

    // antegrapse to oxima ston kosmo gia ton epomeno giro
    return new AnalyseVehicle(ndimx, ndimy, OPERATE, broken, broken, this);
}

// sinartisi leitourgias tou oximatos analisis
// (orisma vector me ta codes apo ta katestramena oximata kai pointer se neo kosmo
// gia ton neo giro tis eksomeiwsis)
Vehicle* AnalyseVehicle::operation(World *w, std::vector<int>& damaged) {

    // an einai sti vasi
    if (isatbase()) {
        std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is at the base " 
            << dimx << "," << dimy << std::endl;
        return new AnalyseVehicle(dimx, dimy, MOVE, isbroken(), false, this);
    }

    // an einai katestrameno
    if (isbroken()) {
         std::cout << "#" << getcode() << " (" << repr_char() << ")" << " is broken at " 
            << dimx << "," << dimy << std::endl;
        return new AnalyseVehicle(dimx, dimy, OPERATE, isbroken(), false, this);
    }

    Ground **panel = world->groundpanel();
    Ground **otherpanel = w->groundpanel();
    int bx = world->getbasex();
    int by = world->getbasey();
    int miningdamage = rand() % 10; // rand timi gia to an tha pathei zimia kata tin eksoriksi
    bool mined = false;

    // an i periektikotita se palladio einai panw apo 0.5 kane eksoriksi
    if (panel[dimx][dimy].get_palladio_content() > 0.5 && panel[dimx][dimy].getpalladiounits() > 0) {
        mined = true;
        int cargo = palladio_cargo + iridio_cargo + leukoxriso_cargo;

        // ipologismos tou fortiou pou tha eksaxthei vasi tou megistou fortiou
        // pou ehei to oxima analisis
        if (cargo + panel[dimx][dimy].getpalladiounits() > max_cargo) {
            // menei ipoloipo posotitas sto simeio tou edafous
            int tmp = (cargo + panel[dimx][dimy].getpalladiounits()) - max_cargo;
            palladio_cargo += panel[dimx][dimy].getpalladiounits() - tmp;
            otherpanel[dimx][dimy].setpalladiounits(tmp);

            total_cargo_mined += panel[dimx][dimy].getpalladiounits() - tmp;
            std::cout << "#" << code << " (" << repr_char() << ")" << " mined "
                << panel[dimx][dimy].getpalladiounits() - tmp << " paladio units " 
                << "at " << dimx << "," << dimy << std::endl;

        } else {
            // ginetai eksoriksi olis tis posotitas sto simeio edafous
            palladio_cargo += panel[dimx][dimy].getpalladiounits();
            otherpanel[dimx][dimy].setpalladiounits(0);
            total_cargo_mined += panel[dimx][dimy].getpalladiounits();

            std::cout << "#" << code << " (" << repr_char() << ")" << " mined "
                << panel[dimx][dimy].getpalladiounits() << " paladio units "
                << "at " << dimx << "," << dimy << std::endl;
        }
    }

    // an i periektikotita se iridio einai panw apo 0.5 kane eksoriksi
    if (panel[dimx][dimy].get_iridio_content() > 0.5 && panel[dimx][dimy].getiridiounits() > 0) {
        mined = true;
        int cargo = palladio_cargo + iridio_cargo + leukoxriso_cargo;

        // ipologismos tou fortiou pou tha eksaxthei vasi tou megistou fortiou
        // pou ehei to oxima analisis
        if (cargo + panel[dimx][dimy].getiridiounits() > max_cargo) {
            // eksoriksi merikis posotitas
            int tmp = (cargo + panel[dimx][dimy].getiridiounits()) - max_cargo;
            iridio_cargo += panel[dimx][dimy].getiridiounits() - tmp;
            otherpanel[dimx][dimy].setiridiounits(tmp);

            total_cargo_mined += panel[dimx][dimy].getiridiounits() - tmp;
            std::cout << "#" << code << " (" << repr_char() << ")" << " mined "
                << panel[dimx][dimy].getiridiounits() - tmp << " iridio units "
                << "at " << dimx << "," << dimy << std::endl;

        } else {
            // ginetai eksoriksi olis tis posotitas sto simeio edafous
            iridio_cargo += panel[dimx][dimy].getiridiounits();
            otherpanel[dimx][dimy].setiridiounits(0);
            total_cargo_mined += panel[dimx][dimy].getiridiounits();

            std::cout << "#" << code << " (" << repr_char() << ")" << " mined "
                << panel[dimx][dimy].getiridiounits() << " iridio units "
                << "at " << dimx << "," << dimy << std::endl;
        }
    }

    // an i periektikotita se leukoxriso einai panw apo 0.5 kane eksoriksi
    if (panel[dimx][dimy].get_leukoxriso_content() > 0.5 && panel[dimx][dimy].getleukoxrisounits() > 0) {
        mined = true;
        int cargo = palladio_cargo + iridio_cargo + leukoxriso_cargo;

        // ipologismos tou fortiou pou tha eksaxthei vasi tou megistou fortiou
        // pou ehei to oxima analisis
        if (cargo + panel[dimx][dimy].getleukoxrisounits() > max_cargo) {
            // eksoriksi merikis posotitas
            int tmp = (cargo + panel[dimx][dimy].getleukoxrisounits()) - max_cargo;
            leukoxriso_cargo += panel[dimx][dimy].getleukoxrisounits() - tmp;
            otherpanel[dimx][dimy].setleukoxrisounits(tmp);

            total_cargo_mined += panel[dimx][dimy].getleukoxrisounits() - tmp;
            std::cout << "#" << code << " (" << repr_char() << ")" << " mined "
                << panel[dimx][dimy].getleukoxrisounits() - tmp << " leukoxriso units "
                << "at " << dimx << "," << dimy << std::endl;

        } else {
            // ginetai eksoriksi olis tis posotitas sto simeio edafous
            leukoxriso_cargo += panel[dimx][dimy].getleukoxrisounits();
            otherpanel[dimx][dimy].setleukoxrisounits(0);
            total_cargo_mined += panel[dimx][dimy].getleukoxrisounits();

            std::cout << "#" << code << " (" << repr_char() << ")" << " mined "
                << panel[dimx][dimy].getleukoxrisounits() << " leukoxriso units "
                << "at " << dimx << "," << dimy << std::endl;
        }
    }
    

    int cargo = palladio_cargo + iridio_cargo + leukoxriso_cargo;
    if (cargo == max_cargo) {
        // an eftase sto megisto fortio tote metakinitai sti vasi gia topothetisi fortiou
        std::cout << "#" << code << " (" << repr_char() << ")" << " cargo full. Moved to base."
            << std::endl;

        // fortio vasis
        int bpaladio = panel[bx][by].getpalladiounits();
        int biridio = panel[bx][by].getiridiounits();
        int bleukoxriso = panel[bx][by].getleukoxrisounits();

        // prostetei to fortio tou oximatos sto fortio tis vasis
        otherpanel[bx][by].setpalladiounits(bpaladio + palladio_cargo);
        otherpanel[bx][by].setiridiounits(biridio + iridio_cargo);
        otherpanel[bx][by].setleukoxrisounits(bleukoxriso + leukoxriso_cargo);

        // midenizetai to fortio tou oximatos
        palladio_cargo = 0;
        iridio_cargo = 0;
        leukoxriso_cargo = 0;

        // antigrafi tou oximatos sto kosmo gia to neo giro
        return new AnalyseVehicle(bx, by, MOVE, false, false, this);
    }

    bool damage = false;
    if (mined) {
        // an egine eksoriksi ipologizei an epathe zimia sti diarkeia tis eksoriksis
        if (miningdamage > 7) {
            // epathe zimia
            damage = true;
            damaged.push_back(getcode());
            std::cout << "#" << code << " (" << repr_char() << ")" 
                << " broken during mining operation" << std::endl;
        }
    }

    // antigrafi tou oximatos sto kosmo gia to neo giro
    return new AnalyseVehicle(dimx, dimy, MOVE, damage, damage, this);
}