#ifndef BUTTON_H
#define BUTTON_H

#include <lvgl.h>
#include "colors.h"

using button_callback = void (*)(lv_event_t*);

struct ButtonData {
    const char *label;
    button_callback callback;
    bool toggleable;
    uint16_t long_press_time; // ms, 0 = short press
    bool start_active = false;
};

class Button {
public:
    Button(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row);
    Button(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row,
                 lv_color_t color_off, lv_color_t color_on);
    void handlePress();
    void updateVisual();
    void eventHandler(lv_event_t* e);

    bool isToggleable() const { return toggleable; }
    bool isToggled() const { return toggled; }

    const char *getLabel() const { return label; }
    lv_obj_t *getLVButton() const { return btn; }

private:
    const char *label;
    button_callback callback;
    lv_obj_t *btn;
    lv_obj_t *label_obj;
    lv_style_t style;

    lv_color_t color_off;
    lv_color_t color_on;

    uint16_t long_press_time = 0;
    uint32_t press_start = 0;
    bool long_press_handled = false;

    bool toggleable;
    bool toggled = false;
};

#endif
