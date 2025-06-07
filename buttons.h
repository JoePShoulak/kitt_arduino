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
    bool toggleable; // <--- enables toggling
    bool long_press; // if true the button requires a long press
};

class ButtonSquare {
public:
    ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row);
    void onPress();
    void onRelease();
    void updateVisual();

    const char *getLabel() const { return label; }
    lv_color_t getColor() const { return color; }
    lv_obj_t *getLVButton() const { return btn; }

private:
    const char *label;
    lv_color_t color;
    lv_obj_t *btn;
    lv_obj_t *label_obj;
    lv_style_t style;

    bool toggleable;
    bool long_press;
    bool toggled = false;
    unsigned long press_start = 0;
};

#endif
