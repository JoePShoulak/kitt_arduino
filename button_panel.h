// button_panel.h

#ifndef BUTTON_PANEL_H
#define BUTTON_PANEL_H

#include <lvgl.h>
#include "buttons.h"

#define BUTTON_COUNT 8

class ButtonPanel {
  ButtonSquare* buttons[BUTTON_COUNT];

public:
  ButtonPanel(lv_obj_t* parent, ButtonData const* config);

  ~ButtonPanel();
};

#endif