#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino_GigaDisplay.h>
#include <button.h>
#include <gauge.h>
#include <indicator.h>
#include <config.h>
#include "callbacks.h"
#include "validators.h"

enum LEFT_GAUGES
{
    tach,
    motor_current,
    peripheral_current
};

const GaugeData left_gauges[3] = {
    {"TACH", "RPM", 0, 6000, GaugeMode::NORMAL},
    {"MOTOR CURRENT", "A", 0, 10, GaugeMode::NORMAL},
    {"PERIPHERAL CURRENT", "A", 0, 5, GaugeMode::NORMAL},
};

enum RIGHT_GAUGES
{
    battery_voltage,
    battery_current,
    time_remaining,
    connection_strength,
    temperature
};

const GaugeData right_gauges[5] = {
    {"BATTERY VOLTAGE", "V", 0, 60, GaugeMode::NORMAL},
    {"BATTERY CURRENT", "A", 0, 20, GaugeMode::NORMAL},
    {"TIME REMAINING", "H", 0, 10, GaugeMode::REVERSED},
    {"CONNECTION STRENGTH", "db", -135, -35, GaugeMode::REVERSED},
    {"TEMPERATURE", "C", 0, 100, GaugeMode::CENTERED},
};

enum LEFT_BUTTONS
{
    turbo_boost,
    theme,
    intro,
    explode,
    michelle,
    shawn,
    joseph,
    shoe
};

const ButtonData left_buttons[BUTTON_COUNT] = {
    {"TURBO BOOST", turbo_boost_btn_cb, validate_always, false, true},
    {"THEME", theme_btn_cb, validate_always, false},
    {"INTRO", intro_btn_cb, validate_always, false},
    {"EXPLODE", explode_btn_cb, validate_always, false},
    {"MICHELLE", michelle_btn_cb, validate_always, false},
    {"SHAWN", shawn_btn_cb, validate_always, false},
    {"JOSEPH", joseph_btn_cb, validate_always, false},
    {"SHOE", shoe_btn_cb, validate_always, false},
};

enum RIGHT_BUTTONS
{
    motor,
    evade,
    v48,
    inverter,
    gps,
    radio,
    usb,
    lighting
};

const ButtonData right_buttons[BUTTON_COUNT] = {
    {"MOTOR", motor_override_cb, validate_motor, true, true, true},
    {"EVADE", evade_btn_cb, validate_always, false, true},
    {"48V MODE", btn48v_cb, validate_48v, true, true, true},
    {"INVERTER", inverter_btn_cb, validate_inverter, true, true},
    {"GPS", gps_btn_cb, validate_always, true, false, true},
    {"RADIO", radio_btn_cb, validate_always, true, false, true},
    {"USB", usb_btn_cb, validate_always, true, false, true},
    {"LIGHTING", lighting_btn_cb, validate_always, true},
};

enum VOICE_BUTTONS
{
    auto_cruise,
    normal_cruise,
    pursuit
};

// ==== Voice tile configuration ====
const ButtonData voice_buttons[3] = {
    {"AUTO CRUISE", auto_cruise_btn_cb, validate_cruise_mode, true, true},
    {"NORMAL CRUISE", normal_cruise_btn_cb, validate_cruise_mode, true, true, true},
    {"PURSUIT", pursuit_btn_cb, validate_cruise_mode, true, true},
};

enum INDICATORS
{
    aud,
    lts,
    b1,
    b2,
    ble,
    rad,
    cur,
    tmp
};

static const IndicatorData indicators[8] = {
    {"AUD", ORANGE_DARK, ORANGE},
    {"LTS", ORANGE_DARK, ORANGE},
    {"B1", RED_DARK, RED},
    {"B2", RED_DARK, RED},

    {"BLE", ORANGE_DARK, ORANGE},
    {"RAD", ORANGE_DARK, ORANGE},
    {"CUR", RED_DARK, RED},
    {"TMP", RED_DARK, RED}};

#endif
