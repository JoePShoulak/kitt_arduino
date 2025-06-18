#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino_GigaDisplay.h>
#include <button.h>
#include <gauge.h>
#include <indicator.h>
#include "callbacks.h"
#include "validators.h"
#include <config.h>

const GaugeData left_gauges[3] = {
    {"TACH", "RPM"},
    {"MOTOR CURRENT", "A"},
    {"PERIPHERAL CURRENT", "A"},
};

const GaugeData right_gauges[5] = {
    {"BATTERY VOLTAGE", "V"},
    {"BATTERY CURRENT", "A"},
    {"SOLAR VOLTAGE", "V"},
    {"SOLAR CURRENT", "A"},
    {"TEMPERATURE", "C"},
};

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
