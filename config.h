#ifndef CONFIG_H
#define CONFIG_H

#include <button.h>
#include <indicator.h>
#include <Arduino_GigaDisplay.h>
#include "callbacks.h"
#include "validators.h"

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

// ==== Visualiser configuration ====
#define CIRCLE_DIAMETER 60
#define COLUMN_WIDTH (CIRCLE_DIAMETER * 6 / 5)
#define CENTER_WIDTH ((480 - CIRCLE_DIAMETER * 2 - SPACING * 4) * 9 / 10)
#define GRID_WIDTH (COLUMN_WIDTH * 2 + CENTER_WIDTH + SPACING * 4)
#define BUTTON_HEIGHT 85
#define VISUALISER_HEIGHT (GRID_HEIGHT - BUTTON_HEIGHT * 3 - SPACING * 5)

static const char *const left_labels[] = {
    "RPM",
    "MOTOR CURRENT",
    "PERIPHERAL CURRENT"};

static const char *const right_labels[] = {
    "BATTERY VOLTAGE",
    "BATTERY CURRENT",
    "SOLAR VOLTAGE",
    "SOLAR CURRENT",
    "TEMPERATURE"};

const ButtonData button_tile1[BUTTON_COUNT] = {
    {"TURBO BOOST", turbo_boost_btn_cb, null_validate, false, true},
    {"THEME", theme_btn_cb, null_validate, false},
    {"INTRO", intro_btn_cb, null_validate, false},
    {"EXPLODE", explode_btn_cb, null_validate, false},
    {"MICHELLE", michelle_btn_cb, null_validate, false},
    {"SHAWN", shawn_btn_cb, null_validate, false},
    {"JOSEPH", joseph_btn_cb, null_validate, false},
    {"SHOE", shoe_btn_cb, null_validate, false},
};

const ButtonData button_tile2[BUTTON_COUNT] = {
    {"MOTOR", motor_override_cb, validate_motor, true, true, true},
    {"EVADE", evade_btn_cb, null_validate, false, true},
    {"48V MODE", btn48v_cb, validate_48v, true, true, true},
    {"INVERTER", inverter_btn_cb, validate_inverter, true, true},
    {"GPS", gps_btn_cb, null_validate, true, false, true},
    {"RADIO", radio_btn_cb, null_validate, true, false, true},
    {"USB", usb_btn_cb, null_validate, true, false, true},
    {"LIGHTING", lighting_btn_cb, null_validate, true},
};

// ==== Voice tile configuration ====
const ButtonData voice_buttons[3] = {
    {"AUTO CRUISE", auto_cruise_btn_cb, validate_cruise_mode, true, true},
    {"NORMAL CRUISE", normal_cruise_btn_cb, validate_cruise_mode, true, true, true},
    {"PURSUIT", pursuit_btn_cb, validate_cruise_mode, true, true},
};

static const IndicatorData indicators[8] = {
    {"AUD", ORANGE_DARK, ORANGE},
    {"LTS", ORANGE_DARK, ORANGE},
    {"B1", RED_DARK, RED},
    {"B2", RED_DARK, RED},

    {"GPS", ORANGE_DARK, ORANGE},
    {"RAD", ORANGE_DARK, ORANGE},
    {"CUR", RED_DARK, RED},
    {"TMP", RED_DARK, RED}};

// ==== Global UI references ====
class VoiceTile;
class GaugeTile;

extern VoiceTile *voiceTile;
extern GaugeTile *rightGaugeTile;
extern GaugeTile *leftGaugeTile;
extern Button *motor_btn;
extern Button *blackout_btn;
extern Button *btn48v;
extern Button *inverter_btn;
extern GigaDisplayBacklight backlight;
extern lv_obj_t *blackout_overlay;

#endif
