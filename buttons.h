// buttons.h

#ifndef BUTTONS_H
#define BUTTONS_H

#include <lvgl.h>

#define WHITE lv_color_hex(0xFFFFFF)
#define YELLOW lv_color_hex(0xFFFF66)
#define RED lv_color_hex(0x990000)
#define GREEN lv_color_hex(0x66FF66)
#define BLACK lv_color_hex(0x000000)

// Function of the form `void callback(lv_event_t*)`
using button_callback = void (*)(lv_event_t*);

struct ButtonData {
  const char *label;
  lv_color_t color;
  button_callback callback;
};

class ButtonSquare {
public:
  ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row, lv_style_t *style);
  void handlePress();  // instance method to handle touch

  const char *getLabel() const { return label; }
  lv_color_t getColor() const { return color; }
  lv_obj_t *getLVButton() const { return btn; }

private:
  const char *label;
  lv_color_t color;
  lv_obj_t *btn;    // The button object
  lv_obj_t *label_obj; // The label object inside the button
};

#endif
