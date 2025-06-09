#ifndef CONFIG_H
#define CONFIG_H

#include "button.h"
#include "indicator.h"

// PANEL DATA
#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); 

const ButtonData button_panel1[BUTTON_COUNT] = {
    { "TURBO BOOST", null_btn, true, 1000, true },
    { "MAP SYSTEM", null_btn, true, 0 },
    { "PRINTER", null_btn, true, 0 },
    { "VOLTAGE OUTPUT", null_btn, true, 0 },
    { "VITAL SCAN", null_btn, false, 0 },
    { "EVADE", null_btn, false, 0 },
    { "RANGE BRITE", null_btn, false, 0 },
    { "RADAR IMAGE", null_btn, false, 0 },
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    { "MOTOR", null_btn, true, 1000, true },
    { "BLACKOUT", null_btn, true, 1000 },
    { "24V MODE", null_btn, true, 1000 },
    { "INVERTER", null_btn, true, 1000 },
    { "GPS", null_btn, true, 0, true },
    { "RADIO", null_btn, true, 0, true },
    { "USB", null_btn, true, 0, true },
    { "LIGHTING", null_btn, true, 0 },
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
