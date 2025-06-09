// button_panel.h

#ifndef BUTTON_PANEL_H
#define BUTTON_PANEL_H

#include <lvgl.h>
#include "config.h"
#include "button.h"

class ButtonPanel {
  Button* buttons[BUTTON_COUNT];

public:
  ButtonPanel(lv_obj_t* parent, ButtonData const* config);

  Button* getButton(uint8_t index) { return index < BUTTON_COUNT ? buttons[index] : nullptr; }

  ~ButtonPanel();
};

#endif