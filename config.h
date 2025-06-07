#ifndef CONFIG_H
#define CONFIG_H

#include "buttons.h"

#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); 

const ButtonData button_panel1[BUTTON_COUNT] = {
    { "TURBO BOOST", null_btn, true, 1000 },
    { "MAP SYSTEM", null_btn, true, 0 },
    { "SKI MODE", null_btn, false, 1000 },
    { "VOLTAGE OUTPUT", null_btn, true, 0 },
    { "VITAL SCAN", null_btn, false, 0 },
    { "EVADE", null_btn, false, 0 },
    { "RANGE BRITE", null_btn, false, 0 },
    { "RADAR IMAGE", null_btn, false, 0 },
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    { "BAD DOLPHINS", null_btn, true, 1000 },
    { "NERVE GAS", null_btn, true, 0 },
    { "SHARKS", null_btn, false, 1000 },
    { "CUTE OTTERS", null_btn, true, 0 },
    { "EMERGENCY METH", null_btn, false, 0 },
    { "SCARLETT JOHANSSON", null_btn, true, 1000 },
    { "BROWNIES", null_btn, false, 0 },
    { "POT BROWNIES", null_btn, false, 0 },
};

#endif
