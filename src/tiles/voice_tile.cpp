#include "voice_tile.h"

#include <config.h>

#include "../config/data.h"

VoiceTile::VoiceTile(lv_obj_t *tileview, int row_id, ButtonData const *button_data)
{
  tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
  lv_obj_set_style_bg_color(tile, BLACK, 0);
  lv_obj_clear_flag(tile, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_scrollbar_mode(tile, LV_SCROLLBAR_MODE_OFF);

  grid = lv_obj_create(tile);
  lv_obj_remove_style_all(grid);
  lv_obj_clear_flag(grid, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_scrollbar_mode(grid, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_size(grid, GRID_WIDTH, GRID_HEIGHT);
  lv_obj_center(grid);

  static lv_coord_t col_dsc[] = {COLUMN_WIDTH, CENTER_WIDTH, COLUMN_WIDTH, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {VISUALISER_HEIGHT, BUTTON_HEIGHT, BUTTON_HEIGHT, BUTTON_HEIGHT, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
  lv_obj_set_style_pad_all(grid, SPACING, 0);
  lv_obj_set_style_pad_row(grid, SPACING, 0);
  lv_obj_set_style_pad_column(grid, SPACING, 0);

  for (int side = 0; side < 2; ++side)
  {
    int col = side == 0 ? 0 : 2;
    lv_obj_t *column = lv_obj_create(grid);
    lv_obj_remove_style_all(column);
    lv_obj_clear_flag(column, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(column, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_grid_cell(column, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_STRETCH, 0, 4);
    lv_obj_set_layout(column, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(column, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(column, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_width(column, COLUMN_WIDTH);

    for (int i = 0; i < 4; ++i)
      indicators[side * 4 + i] = new Indicator(::indicators[side * 4 + i], column);
  }

  visualiser = new VoiceVisualiser(grid);
  visualiser->setLevel(0.0f); // FIXME: Fix this over in UI

  buttons[0] = new Button(grid, button_data[0], 1, 1, ORANGE_DARK, ORANGE);
  buttons[1] = new Button(grid, button_data[1], 1, 2, GREEN_DARK, GREEN);
  buttons[2] = new Button(grid, button_data[2], 1, 3, BLUE_DARK, BLUE);
}

VoiceTile::~VoiceTile()
{
  for (auto &btn : buttons)
    delete btn;

  for (auto &ind : indicators)
    delete ind;

  delete visualiser;
}
