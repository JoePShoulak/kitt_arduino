// button_panel.h

#ifndef BUTTON_PANEL_H
#define BUTTON_PANEL_H

#include <lvgl.h>
#include "config.h"
#include "button.h"

class ButtonPanel {
  ButtonSquare* buttons[BUTTON_COUNT];

public:
  ButtonPanel(lv_obj_t* parent, ButtonData const* config);

  ~ButtonPanel();
};

#endif