#include "Vehicle.h"
#include "World.h"

// static variables
int Vehicle::total_num = 0;
int Vehicle::total_damages = 0;

// static functions
int Vehicle::gettotal() {
    return total_num;
}

int Vehicle::gettotaldamages() {
    return total_damages;
}

// total vehicles stats -- as static function
void Vehicle::totalstats() {
    std::cout << "*** VEHICLES GENERAL STATS ***" << std::endl;
    std::cout << "Total vehicles: " << total_num << std::endl;
    std::cout << "Total vehicles damages: " << total_damages << std::endl; 
}

// Vehicle constructor -- neo vechicle sti thesi x,y tou kosmou w (pointer sto kosmo)
Vehicle::Vehicle(int x, int y, World* w) {
    // arxikopoiisi metablitwn
    total_num++;
    code = total_num;
    cur_state = ENABLED;
    next = MOVE;
    speed = rand() % 3 + 1; // timi sto [1 , 3]
    access_ability = (1 + rand() % 9) * 0.1;    // timi sto [0.1 , 0.9]
    damages = 0;
    dimx = x;
    dimy = y;
    world = w;
}

// Vehicle constructor apo pointer sto oxima v
// vechicle sti thesi x,y, me td energeia ston epomeno giro,
// broken true an einai katestrameno, newdamage true an katastrafike ston amesws
// proigoumeno giro kai v o pointer pros sto oxima pou tha antigrafei
Vehicle::Vehicle(int x, int y, todo td, bool broken, bool newdamage, Vehicle *v) {
    // antigrafi stoixeiwn apo to oxima pou deixnei o v
    code = v->getcode();
    damages = v->getdamages();
    if (v->isbroken()) 
        cur_state = BROKEN;
    else
        cur_state = ENABLED;
    speed = v->getspeed();
    access_ability = v->getaccessability();
    world = v->getworld();
    next = td;
    dimx = x;
    dimy = y;
    // proklithike zimia sti diarkeia tou proigoumenou girou prosomoiwsis
    if (newdamage)
        damaged();
}

// get methods
int Vehicle::getcode() {
    return code;
}

int Vehicle::getspeed() {
    return speed;
}

int Vehicle::getcurstate() {
    return cur_state;
}

todo Vehicle::gettodonext() {
    return next;
}

float Vehicle::getaccessability() {
    return access_ability;
}

int Vehicle::getdamages() {
    return damages;
}

// epistrefei true an einai katestrameno
bool Vehicle::isbroken() {
    if (cur_state == BROKEN)
        return true;
    else
        return false;
}

// epistrefei true an einai sti vasi
bool Vehicle::isatbase() {
    if (dimx == world->getbasex() && dimy == world->getbasey())
        return true;
    else 
        return false;
}

// epistrefei true an einai sto simeio x,y
bool Vehicle::isatspot(int x, int y) {
    if (dimx == x && dimy == y)
        return true;
    else
        return false;
}

// epistrefei x row
int Vehicle::getrow() {
    return dimx;
}

// epistrefei y column
int Vehicle::getcol() {
    return dimy;
}

// epistrefei pointer tou kosmou
World* Vehicle::getworld() {
    return world;
}

// tipwnei vasikes plirofories gia to oxima
void Vehicle::info() {
    std::cout << "Position -> " << "Row: " << dimx << " Col: " << dimy << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Status: ";
    if (isbroken())
        std::cout << "BROKEN" << std::endl;
    else
        std::cout << "WORKING" << std::endl;
    std::cout << "Access ability: " << access_ability << std::endl;
    std::cout << "Damaged " << damages << " times" << std::endl;
}

// proklithike vlavi sto oxima
void Vehicle::damaged() {
    cur_state = BROKEN;
    damages++;  // auksanei tis zimies pou ehei ipostei
    total_damages++; // auksanei tis sinolikes zimies pou exoun ipostei ta oximata tou kosmou (static)
}

// epidiorthwsi oximatos
void Vehicle::fixed() {
    cur_state = ENABLED;
}

// orismos kosmou pou leitourgei kai kineitai to oxima
void Vehicle::setworld(World *w) {
    world = w;
}