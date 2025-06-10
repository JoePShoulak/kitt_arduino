#ifndef POPUP_H
#define POPUP_H

#include "lvgl_wrapper.h"

lv_obj_t *show_error_popup(lv_obj_t *parent_tile, const char *msg);
lv_obj_t *show_fullscreen_popup(lv_obj_t *parent);

#endif
