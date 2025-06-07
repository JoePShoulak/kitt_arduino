#ifndef CONFIG_H
#define CONFIG_H

#include "buttons.h"

#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); 

const ButtonData button_panel1[BUTTON_COUNT] = {
    { "TURBO BOOST", RED, null_btn, true },
    { "MAP SYSTEM", YELLOW, null_btn, false },
    { "SKI MODE", WHITE, null_btn, false },
    { "VOLTAGE OUTPUT", YELLOW, null_btn, false },
    { "VITAL SCAN", GREEN, null_btn, false },
    { "EVADE", GREEN, null_btn, false },
    { "RANGE BRITE", GREEN, null_btn, false },
    { "RADAR IMAGE", GREEN, null_btn, false },
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    { "BAD DOLPHINS", RED, null_btn, true },
    { "NERVE GAS", YELLOW, null_btn, false },
    { "SHARKS", WHITE, null_btn, false },
    { "CUTE OTTERS", YELLOW, null_btn, false },
    { "EMERGENCY METH", GREEN, null_btn, false },
    { "SCARLETT JOHANSSON", RED, null_btn, true },
    { "BROWNIES", GREEN, null_btn, false },
    { "POT BROWNIES", GREEN, null_btn, false },
};

#endif
