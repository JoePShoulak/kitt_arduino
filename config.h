#ifndef CONFIG_H
#define CONFIG_H

#include "buttons.h"

#define BUTTON_COUNT 10

const ButtonData button_data[BUTTON_COUNT] = {
    { "TURBO BOOST", RED },
    { "MAP SYSTEM", YELLOW },
    { "SKI MODE", WHITE },
    { "VOLTAGE OUTPUT", YELLOW },
    { "VITAL SCAN", GREEN },
    { "EVADE", GREEN },
    { "RANGE BRITE", GREEN },
    { "RADAR IMAGE", GREEN },
    { "MISSILE", RED },
    { "SMOKE RELEASE", RED }
};

#endif