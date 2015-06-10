#include "Ground.h"
#include <cassert>

Ground::Ground() {
    // arxikopoiisi twn metavlitwn
    ground_units = 100;
    flag = false;
    base = false;

    // ipologismos access_danger
    int access_tmp = 1 + rand() % 9;
    access_danger = access_tmp * 0.1;

    // ipologismos periektikotitwn me rand()
    int pc = 0;
    int ic = 0;
    int lc = 0;
    pc = rand() % 11;
    int remain = 10 - pc;
    if (remain != 0) {
        ic = rand() % remain;
        lc = 10 - (pc + ic);
    }

    palladio_content = pc * 0.1;
    iridio_content = ic * 0.1;
    leukoxriso_content = lc * 0.1;

    // assertion gia sigouria oti athroizoun se 1
    assert(palladio_content + iridio_content + leukoxriso_content == 1);

    // monades sistatikwn sto simeio
    palladio_units = palladio_content * ground_units;
    iridio_units = iridio_content * ground_units;
    leukoxriso_units = leukoxriso_content * ground_units;
}

// monades palladio
int Ground::getpalladiounits() {
    return palladio_units;
}

// monades iridio
int Ground::getiridiounits() {
    return iridio_units;
}

// monades leukoxrisou    
int Ground::getleukoxrisounits() {
    return leukoxriso_units;
}

// periektikotita palladiou
float Ground::get_palladio_content() {
    return palladio_content;
}

// periektikotita iridiou
float Ground::get_iridio_content() {
    return iridio_content;
}

// periektikotita leukoxrisou
float Ground::get_leukoxriso_content(){
    return leukoxriso_content;
}

// epikindinotita prosvasis
float Ground::getaccessdanger() {
    return access_danger;
}

// an ehei simaia kindinou epistrefei true
bool Ground::hasflag() {
    return flag;
}

// an einai basi epistrefei true
bool Ground::isbase() {
    return base;
}

// sinolikes plirofories gia to edafos
void Ground::info() {
    std::cout << "*** Ground spot INFO ***" << std::endl;
    if (isbase()) {
        std::cout << "Here is the Base." << std::endl;
    } else {
        std::cout << "CONTENTS: Palladio: " << palladio_content << " -- Iridio: " << iridio_content << " -- Leukoxriso: " << leukoxriso_content << std::endl; 
        std::cout << "UNITS: Palladio: " << getpalladiounits() << " -- Iridio: " << getiridiounits() << " -- Leukoxriso: " << getleukoxrisounits() << std::endl; 
        std::cout << "Access danger is " << access_danger << std::endl;
        if (hasflag())
            std::cout << "Has a danger flag!" << std::endl;
        else
            std::cout << "No danger flag." << std::endl;
    }
}

// einai basi
void Ground::setbase() {
    base = true;
}

// ehei simaia kindinou
void Ground::setflag() {
    flag = true;
}

// ehei pu monades palladiou
void Ground::setpalladiounits(int pu) {
    palladio_units = pu;
}

// ehei iu monades iridiou
void Ground::setiridiounits(int iu) {
    iridio_units = iu;
}

// ehei lu monades leukoxrisou
void Ground::setleukoxrisounits(int lu) {
    leukoxriso_units = lu;
}