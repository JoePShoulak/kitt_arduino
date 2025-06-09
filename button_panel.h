// button_panel.h

#ifndef BUTTON_PANEL_H
#define BUTTON_PANEL_H

#include "button.h"
#include "config.h"
#include <lvgl.h>

class ButtonPanel {
    Button *buttons[BUTTON_COUNT];

  public:
    ButtonPanel(lv_obj_t *parent, ButtonData const *config);

    static ButtonPanel *createTile(lv_obj_t *tileview, int row_id, ButtonData const *config);

    Button *getButton(uint8_t index) { return index < BUTTON_COUNT ? buttons[index] : nullptr; }

    ~ButtonPanel();
};

#endif
