#ifndef BUTTONS_H
#define BUTTONS_H

#include <lvgl.h>

#define WHITE lv_color_hex(0xFFFFFF)
#define YELLOW lv_color_hex(0xFFFF66)
#define RED lv_color_hex(0x990000)
#define GREEN lv_color_hex(0x66FF66)

class ButtonSquare {
public:
ButtonSquare(const char *label_text, lv_color_t color);
  const char *getLabel() const { return label; }
  lv_color_t getColor() const { return color; }

private:
  const char *label;
  lv_color_t color;
  lv_obj_t *btn; // Will store the LVGL button later
};

#endif
