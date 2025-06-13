#ifndef CONFIG_H
#define CONFIG_H

#include "button.h"
#include "indicator.h"
#include <Arduino_GigaDisplay.h>

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

void intro_btn_cb(lv_event_t *e);
void explode_btn_cb(lv_event_t *e);
void joseph_btn_cb(lv_event_t *e);
void shoe_btn_cb(lv_event_t *e);
void michelle_btn_cb(lv_event_t *e);
void shawn_btn_cb(lv_event_t *e);
void theme_btn_cb(lv_event_t *e);
void turbo_boost_btn_cb(lv_event_t *e);
void auto_cruise_btn_cb(lv_event_t *e);
void normal_cruise_btn_cb(lv_event_t *e);
void pursuit_btn_cb(lv_event_t *e);
void evade_btn_cb(lv_event_t *e);
void btn24v_cb(lv_event_t *e);
void inverter_btn_cb(lv_event_t *e);
void gps_btn_cb(lv_event_t *e);
void radio_btn_cb(lv_event_t *e);
void usb_btn_cb(lv_event_t *e);
void lighting_btn_cb(lv_event_t *e);
void motor_override_cb(lv_event_t *e);
void blackout_cb(lv_event_t *e);
void voice_mode_cb(lv_event_t *e);
bool validate_24v(lv_event_t *e);
bool validate_motor(lv_event_t *e);
bool validate_inverter(lv_event_t *e);
bool validate_voice_mode(lv_event_t *e);

const ButtonData button_panel1[BUTTON_COUNT] = {
    {"TURBO BOOST", turbo_boost_btn_cb, false, true},
    {"THEME", theme_btn_cb, false},
    {"INTRO", intro_btn_cb, false},         {"EXPLODE", explode_btn_cb, false},
    {"MICHELLE", michelle_btn_cb, false},   {"SHAWN", shawn_btn_cb, false},
    {"JOSEPH", joseph_btn_cb, false},       {"SHOE", shoe_btn_cb, false},
};

const ButtonData button_panel2[BUTTON_COUNT] = {
    {"MOTOR", motor_override_cb, true, true, true},
    {"EVADE", evade_btn_cb, true, true},
    {"24V MODE", btn24v_cb, true, true},
    {"INVERTER", inverter_btn_cb, true, true},
    {"GPS", gps_btn_cb, true, false, true},   {"RADIO", radio_btn_cb, true, false, true},
    {"USB", usb_btn_cb, true, false, true},   {"LIGHTING", lighting_btn_cb, true},
};

// ==== Voice tile configuration ====
const ButtonData voice_buttons[3] = {
    {"AUTO CRUISE", auto_cruise_btn_cb, true, true},
    {"NORMAL CRUISE", normal_cruise_btn_cb, true, true, true},
    {"PURSUIT", pursuit_btn_cb, true, true},
};

// ==== Visualiser configuration ====
#define CIRCLE_DIAMETER 60
#define COLUMN_WIDTH (CIRCLE_DIAMETER * 6 / 5)
#define CENTER_WIDTH ((480 - CIRCLE_DIAMETER * 2 - SPACING * 4) * 9 / 10)
#define GRID_WIDTH (COLUMN_WIDTH * 2 + CENTER_WIDTH + SPACING * 4)
#define BUTTON_HEIGHT 85
#define VISUALISER_HEIGHT (GRID_HEIGHT - BUTTON_HEIGHT * 3 - SPACING * 5)

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
extern GaugeTile *gaugeTile;
extern GaugeTile *leftGaugeTile;
extern Button *motor_btn;
extern Button *blackout_btn;
extern Button *btn24v;
extern Button *inverter_btn;
extern bool blackout;
extern GigaDisplayBacklight backlight;
extern lv_obj_t *blackout_overlay;

#endif
