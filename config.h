#ifndef CONFIG_H
#define CONFIG_H

#include "buttons.h"

#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); 

const ButtonData button_panel1[BUTTON_COUNT] = {
    { "TURBO BOOST", RED, null_btn, true, 1000 },
    { "MAP SYSTEM", YELLOW, null_btn, false, 0 },
    { "SKI MODE", WHITE, null_btn, false, 0 },
    { "VOLTAGE OUTPUT", YELLOW, null_btn, false, 0 },
    { "VITAL SCAN", GREEN, null_btn, false, 0 },
    { "EVADE", GREEN, null_btn, false, 0 },
    { "RANGE BRITE", GREEN, null_btn, false, 0 },
    { "RADAR IMAGE", GREEN, null_btn, false, 0 },
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    { "BAD DOLPHINS", RED, null_btn, true, 1000 },
    { "NERVE GAS", YELLOW, null_btn, false, 0 },
    { "SHARKS", WHITE, null_btn, false, 0 },
    { "CUTE OTTERS", YELLOW, null_btn, false, 0 },
    { "EMERGENCY METH", GREEN, null_btn, false, 0 },
    { "SCARLETT JOHANSSON", RED, null_btn, true, 1000 },
    { "BROWNIES", GREEN, null_btn, false, 0 },
    { "POT BROWNIES", GREEN, null_btn, false, 0 },
};

#endif
