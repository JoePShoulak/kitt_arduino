// button_tile.h

#ifndef button_tile_H
#define button_tile_H

#include <lvgl.h>
#include <button.h>
#include "../../config/data.h"

class ButtonTile
{
public:
  ButtonTile(lv_obj_t *parent, ButtonData const *config);
  ~ButtonTile();

  static ButtonTile *createTile(lv_obj_t *tileview, int row_id, ButtonData const *config);
  Button *buttons[BUTTON_COUNT];
};

#endif
