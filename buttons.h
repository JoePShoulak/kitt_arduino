// buttons.h

#ifndef BUTTONS_H
#define BUTTONS_H

#include <lvgl.h>

// TODO: toggleable buttons, long press, etc.

#define WHITE lv_color_hex(0xFFFFFF)
#define YELLOW lv_color_hex(0xFFFF66)
#define RED lv_color_hex(0x990000)
#define GREEN lv_color_hex(0x66FF66)
#define BLACK lv_color_hex(0x000000)

// Function of the form `void callback(lv_event_t*)`
using button_callback = void (*)(lv_event_t*);

struct ButtonData {
  const char *label; // label text
  lv_color_t color; // bg color
  button_callback callback; // button obj
};

class ButtonSquare {
public:
  ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row);
  void handlePress();  // instance method to handle touch

  const char *getLabel() const { return label; } // label text
  lv_color_t getColor() const { return color; } // bg color
  lv_obj_t *getLVButton() const { return btn; } // button obj

private:
  const char *label; // label text
  lv_color_t color; // bg color
  lv_obj_t *btn; // button obj
  lv_obj_t *label_obj; // label obj
  lv_style_t style; // default style
};

#endif
