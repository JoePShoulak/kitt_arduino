#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino_GigaDisplay.h>
#include <button.h>

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