#ifndef VOICE_SCENE_H
#define VOICE_SCENE_H

#include <lvgl.h>
#include "button.h"

lv_obj_t* create_voice_tile(lv_obj_t* tileview, int row_id, ButtonData const* buttons);

class VoiceVisualiser;

#endif
