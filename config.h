#ifndef CONFIG_H
#define CONFIG_H

#include "button.h"
#include "indicator.h"

// PANEL DATA
#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); 

const ButtonData button_panel1[BUTTON_COUNT] = {
    { "TURBO BOOST", null_btn, true, true, true },
    { "MAP SYSTEM", null_btn, true, false },
    { "SKI MODE", null_btn, false, true },
    { "VOLTAGE OUTPUT", null_btn, true, false },
    { "VITAL SCAN", null_btn, false, false },
    { "EVADE", null_btn, false, false },
    { "RANGE BRITE", null_btn, false, false },
    { "RADAR IMAGE", null_btn, false, false },
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    { "BAD DOLPHINS", null_btn, true, true, true },
    { "NERVE GAS", null_btn, true, false },
    { "SHARKS", null_btn, false, true },
    { "CUTE OTTERS", null_btn, true, false },
    { "EMERGENCY METH", null_btn, false, false },
    { "SCARLETT JOHANSSON", null_btn, true, true, true },
    { "BROWNIES", null_btn, false, false },
    { "POT BROWNIES", null_btn, false, false },
};

// VIZ DATA
#define SPACING 20
#define CIRCLE_DIAMETER 60
#define COLUMN_WIDTH (CIRCLE_DIAMETER * 6 / 5)
#define CENTER_WIDTH ((480 - CIRCLE_DIAMETER * 2 - SPACING * 4) * 9 / 10)
#define GRID_WIDTH (COLUMN_WIDTH * 2 + CENTER_WIDTH + SPACING * 4)
#define BUTTON_HEIGHT 85
#define GRID_HEIGHT 800
#define VISUALISER_HEIGHT (GRID_HEIGHT - BUTTON_HEIGHT * 3 - SPACING * 5)

static const IndicatorData indicators[8] = {
    { "AIR", ORANGE_DARK, ORANGE },
    { "OIL", ORANGE_DARK, ORANGE },
    { "P1", RED_DARK, RED },
    { "P2", RED_DARK, RED },
    { "S1", ORANGE_DARK, ORANGE },
    { "S2", ORANGE_DARK, ORANGE },
    { "P3", RED_DARK, RED },
    { "P4", RED_DARK, RED }
};

#endif
