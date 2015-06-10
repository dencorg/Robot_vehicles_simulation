#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <cstdlib>
#include <vector>

class World;

// katastasi oximatos
enum state {ENABLED, BROKEN};

// energeia pou tha ektelesei to oxima ston epomeno giro tis prosomeiwsis
enum todo {MOVE, OPERATE};

// abstract class gia ta vehicle tou kosmou
class Vehicle {

protected:
    // static vehicle variables
    static int total_num;   // sinolika oximata ston kosmo
    static int total_damages;   // sinolikes zimies oximatwn sto kosmo

    // private vehicle properties
    int code;   // kwdikos oxomatos
    int speed;  // taxitita pou kineitai to oxima
    state cur_state;    // katastasi oximatos
    todo next;  // epomeni energeia oximatos
    float access_ability;   // ikanotita prosvasis
    int damages;    // arithmos forwn pou ehei proklithei zimia sto oxima

    // thesi vehicle sto xarti
    int dimx;
    int dimy;

    // pointer pros ton kosmo ston opoio vrisketai to oxima
    World *world;

public:
    // static vehicle functions
    static int gettotal();
    static int gettotaldamages();
    static void totalstats();

    //Vehicle constructors
    // neo oxima
    Vehicle(int, int, World*);
    // antigrafi apo oxima
    Vehicle(int, int, todo, bool, bool, Vehicle*);

    // get functions
    int getcode();
    int getspeed();
    int getcurstate();
    todo gettodonext();
    float getaccessability();
    int getdamages();

    int getrow();
    int getcol();
    World* getworld();

    bool isbroken();    // true an einai xalasmeno 
    bool isatbase();    // true an einai sti vasi
    bool isatspot(int, int);    // true an einai sto simeio

    // thetei ton kosmo ston opoio iparxei to oxima
    void setworld(World *);

    // prokalei zimia sto oxima
    void damaged();

    // epidiorthwsi oximatos
    void fixed();

    // tipwnei info gia to vehicle -- virtual
    virtual void info();

    // abstract

    // sinartisi metakinisis -- virtual
    virtual Vehicle* move(std::vector<int>&) = 0;

     // sinartisi leitourgias -- virtual
    virtual Vehicle* operation(World*, std::vector<int>&) = 0;

    // char gia anaparastasi ston kosmo -- virtual
    virtual char repr_char() = 0;

};

#endif