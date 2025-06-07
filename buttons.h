#ifndef BUTTONS_H
#define BUTTONS_H

#include <lvgl.h>

#define WHITE lv_color_hex(0xFFFFFF)
#define YELLOW lv_color_hex(0xFFFF66)
#define RED lv_color_hex(0x990000)
#define GREEN lv_color_hex(0x66FF66)
#define BLACK lv_color_hex(0x000000)

using button_callback = void (*)(lv_event_t*);

struct ButtonData {
    const char *label;
    lv_color_t color;
    button_callback callback;
    bool toggleable; // <--- this was added to enable toggling
    uint16_t long_press_time; // ms, 0 = normal click
};

class ButtonSquare {
public:
    ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row);
    void handlePress();
    void updateVisual();
    void eventHandler(lv_event_t* e);

    bool isToggleable() const { return toggleable; }
    bool isToggled() const { return toggled; }

    const char *getLabel() const { return label; }
    lv_color_t getColor() const { return color; }
    lv_obj_t *getLVButton() const { return btn; }

private:
    const char *label;
    lv_color_t color;
    lv_obj_t *btn;
    lv_obj_t *label_obj;
    lv_style_t style;

    uint16_t long_press_time = 0;
    uint32_t press_start = 0;
    bool long_press_handled = false;

    bool toggleable; // <--- new field
    bool toggled = false; // <--- new field
};

#endif
