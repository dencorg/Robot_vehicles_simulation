#ifndef GROUND_H
#define GROUND_H

#include <iostream>
#include <cstdlib>

// class gia ena simeio sto edafos tou kosmou
class Ground {

private:
    int ground_units;   // monades sto edafos

    // periektikotites sistatikwn
    float palladio_content;
    float iridio_content;
    float leukoxriso_content;

    // monades gia kathe sistatiko
    int palladio_units;
    int iridio_units;
    int leukoxriso_units;

    float access_danger;    // epikindinotita prosvasis
    bool flag;  // simaia kindinou
    bool base;  // true an to simeio einai i basi

public:
    // constructor
    Ground();

    // dwse tis posotites twn sistatikwn sto edafos
    int getpalladiounits();
    int getiridiounits();
    int getleukoxrisounits();

    // dwse tis periektikotites sistatikwn
    float get_palladio_content();
    float get_iridio_content();
    float get_leukoxriso_content();

    // thetoun tis posotites sistatikwn sto edafos
    void setpalladiounits(int);
    void setiridiounits(int);
    void setleukoxrisounits(int);

    float getaccessdanger();    // epistrefei tin epikindinotita
    bool hasflag(); // true an ehei simaia kindinou
    bool isbase();  // true an to simeio einai vasi
    void info();    // plirofories gia to simeio sto edafos

    // thetei simaia kindinou
    void setflag();

    // kanei to simeio vasi gia tin eksomoiwsi
    void setbase();
};

#endif