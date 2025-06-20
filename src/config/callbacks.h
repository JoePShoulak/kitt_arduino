#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <lvgl.h>

// Left button panel
void turbo_boost_btn_cb(lv_event_t *e);
void theme_btn_cb(lv_event_t *e);
void intro_btn_cb(lv_event_t *e);
void explode_btn_cb(lv_event_t *e);
void michelle_btn_cb(lv_event_t *e);
void shawn_btn_cb(lv_event_t *e);
void joseph_btn_cb(lv_event_t *e);
void shoe_btn_cb(lv_event_t *e);

// Right button panel
void motor_override_cb(lv_event_t *e);
void evade_btn_cb(lv_event_t *e);
void btn48v_cb(lv_event_t *e);
void inverter_btn_cb(lv_event_t *e);
void gps_btn_cb(lv_event_t *e);
void radio_btn_cb(lv_event_t *e);
void usb_btn_cb(lv_event_t *e);
void lighting_btn_cb(lv_event_t *e);

// Voice panel
void cruise_mode_cb(lv_event_t *e);
void auto_cruise_btn_cb(lv_event_t *e);
void normal_cruise_btn_cb(lv_event_t *e);
void pursuit_btn_cb(lv_event_t *e);

// Misc
void blackout_overlay_cb(lv_event_t *e);

#endif
