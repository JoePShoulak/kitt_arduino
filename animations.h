#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <lvgl.h>
#include "config.h"

// Forward declaration from the GigaAudio library
class GigaAudio;

void gauge_anim_cb(lv_timer_t *t);
void voice_anim_cb(lv_timer_t *t);

#endif
