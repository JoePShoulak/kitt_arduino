#ifndef CONFIG_H
#define CONFIG_H

#include "buttons.h"

#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); 

const ButtonData button_panel1[BUTTON_COUNT] = {
    { "TURBO BOOST", RED, null_btn, true, true },
    { "MAP SYSTEM", YELLOW, null_btn, false, false },
    { "SKI MODE", WHITE, null_btn, false, false },
    { "VOLTAGE OUTPUT", YELLOW, null_btn, false, false },
    { "VITAL SCAN", GREEN, null_btn, false, false },
    { "EVADE", GREEN, null_btn, false, false },
    { "RANGE BRITE", GREEN, null_btn, false, false },
    { "RADAR IMAGE", GREEN, null_btn, false, false },
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    { "BAD DOLPHINS", RED, null_btn, true, true },
    { "NERVE GAS", YELLOW, null_btn, false, false },
    { "SHARKS", WHITE, null_btn, false, false },
    { "CUTE OTTERS", YELLOW, null_btn, false, false },
    { "EMERGENCY METH", GREEN, null_btn, false, false },
    { "SCARLETT JOHANSSON", RED, null_btn, true, true },
    { "BROWNIES", GREEN, null_btn, false, false },
    { "POT BROWNIES", GREEN, null_btn, false, false },
};

#endif
