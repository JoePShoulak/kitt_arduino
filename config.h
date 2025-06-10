#ifndef CONFIG_H
#define CONFIG_H

#include "button.h"
#include "indicator.h"

// ==== Layout constants ====
#define SPACING 20
#define GRID_HEIGHT 800
#define POPUP_WIDTH 300
#define POPUP_HEIGHT 220

// ==== Button panel configuration ====
#define BUTTON_COUNT 8
#define PANEL_BUTTON_SIZE ((GRID_HEIGHT - SPACING * 6) / (BUTTON_COUNT / 2))
#define PANEL_GRID_WIDTH (PANEL_BUTTON_SIZE * 2 + SPACING * 3)
#define PANEL_GRID_HEIGHT (PANEL_BUTTON_SIZE * (BUTTON_COUNT / 2) + SPACING * 6)

void null_btn(lv_event_t *e);

const ButtonData button_panel1[BUTTON_COUNT] = {
    {"TURBO BOOST", null_btn, false, true}, {"MAP SYSTEM", null_btn, true},
    {"PRINTER", null_btn, true},           {"VOLTAGE OUTPUT", null_btn, true},
    {"VITAL SCAN", null_btn, false},       {"EVADE", null_btn, false},
    {"RANGE BRITE", null_btn, false},      {"RADAR IMAGE", null_btn, false},
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    {"MOTOR", null_btn, true, true, true},
    {"BLACKOUT", null_btn, true, true},
    {"24V MODE", null_btn, true, true},
    {"INVERTER", null_btn, true, true},
    {"GPS", null_btn, true, false, true},
    {"RADIO", null_btn, true, false, true},
    {"USB", null_btn, true, false, true},
    {"LIGHTING", null_btn, true},
};

// ==== Voice tile configuration ====
const ButtonData voice_buttons[3] = {
    {"AUTO CRUISE", null_btn, true, true},
    {"NORMAL CRUISE", null_btn, true, true, true},
    {"PURSUIT", null_btn, true, true},
};

// ==== Visualiser configuration ====
#define CIRCLE_DIAMETER 60
#define COLUMN_WIDTH (CIRCLE_DIAMETER * 6 / 5)
#define CENTER_WIDTH ((480 - CIRCLE_DIAMETER * 2 - SPACING * 4) * 9 / 10)
#define GRID_WIDTH (COLUMN_WIDTH * 2 + CENTER_WIDTH + SPACING * 4)
#define BUTTON_HEIGHT 85
#define VISUALISER_HEIGHT (GRID_HEIGHT - BUTTON_HEIGHT * 3 - SPACING * 5)

static const IndicatorData indicators[8] = {
    {"AIR", ORANGE_DARK, ORANGE}, {"OIL", ORANGE_DARK, ORANGE},
    {"P1", RED_DARK, RED},        {"P2", RED_DARK, RED},
    {"S1", ORANGE_DARK, ORANGE},  {"S2", ORANGE_DARK, ORANGE},
    {"P3", RED_DARK, RED},        {"P4", RED_DARK, RED}};

// ==== Global UI references ====
class VoiceTile;
class GaugeTile;

extern VoiceTile *voiceTile;
extern GaugeTile *gaugeTile;
extern GaugeTile *leftGaugeTile;
extern Button *motor_btn;
extern Button *btn24v;
extern Button *inverter_btn;
extern Button *blackout_btn;

#define BACKLIGHT_PIN D9
void turnDisplayOff();
void turnDisplayOn();
void blackout_cb(lv_event_t *e);
void blackout_touch_cb(lv_event_t *e);

// ==== Event callbacks ====
void motor_override_cb(lv_event_t *e);
void voice_mode_cb(lv_event_t *e);
bool validate_24v(lv_event_t *e);
bool validate_motor(lv_event_t *e);
bool validate_inverter(lv_event_t *e);
bool validate_voice_mode(lv_event_t *e);

#endif
