#ifndef BUTTON_H
#define BUTTON_H

#include "colors.h"
#include "lvgl_wrapper.h"

using button_callback = void (*)(lv_event_t *);
using validate_callback = bool (*)(lv_event_t *);

struct ButtonData {
  const char *label;
  button_callback callback;
  bool toggleable;
  bool severe = false; // hold for one second before triggering if true
  bool start_active = false;
  const char *audio_on = nullptr;  // optional wav to play when toggled on
  const char *audio_off = nullptr; // optional wav to play when toggled off
};

class Button {
public:
  Button(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col,
         uint8_t grid_row);
  Button(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col,
         uint8_t grid_row, lv_color_t color_off, lv_color_t color_on);
  void setCallback(button_callback cb);
  void setValidate(validate_callback cb);
  void handlePress();
  void updateVisual();
  void eventHandler(lv_event_t *e);

  bool isToggleable() const { return toggleable; }
  bool isToggled() const { return toggled; }

  const char *getLabel() const { return label; }
  lv_obj_t *getLVButton() const { return btn; }

private:
  const char *label;
  button_callback callback;
  validate_callback validate;
  lv_obj_t *btn;
  lv_obj_t *label_obj;
  lv_style_t style;

  void set_style();

  lv_color_t color_off;
  lv_color_t color_on;

  const char *sound_on = nullptr;
  const char *sound_off = nullptr;

  static const uint16_t LONG_PRESS_DURATION = 1000; // ms
  bool severe = false;
  uint32_t press_start = 0;
  bool long_press_handled = false;

  bool toggleable;
  bool toggled = false;
};

#endif
