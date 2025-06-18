// button_tile.cpp

#include "button_tile.h"
#include <lvgl.h>
#include <config.h>

ButtonTile::ButtonTile(lv_obj_t *parent, ButtonData const *config)
{
  lv_obj_t *grid = lv_obj_create(parent); // Grid container
  lv_obj_remove_style_all(grid);          // no background/border
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_size(grid, PANEL_GRID_WIDTH, PANEL_GRID_HEIGHT);
  lv_obj_center(grid); // center the grid on screen

  // Define grid - 2 columns of PANEL_BUTTON_SIZE, 5 rows of PANEL_BUTTON_SIZE
  static lv_coord_t col_dsc[] = {PANEL_BUTTON_SIZE, PANEL_BUTTON_SIZE, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {PANEL_BUTTON_SIZE, PANEL_BUTTON_SIZE, PANEL_BUTTON_SIZE,
                                 PANEL_BUTTON_SIZE, PANEL_BUTTON_SIZE, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

  // Set equal padding around grid and between buttons
  lv_obj_set_style_pad_all(grid, SPACING, 0);    // margin to edges
  lv_obj_set_style_pad_row(grid, SPACING, 0);    // spacing between rows
  lv_obj_set_style_pad_column(grid, SPACING, 0); // spacing between columns

  for (int i = 0; i < BUTTON_COUNT; ++i)
    buttons[i] = new Button(grid, config[i], i % 2, i / 2);
};

ButtonTile *ButtonTile::createTile(lv_obj_t *tileview, int row_id, ButtonData const *config)
{
  auto *tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
  lv_obj_set_style_bg_color(tile, BLACK, 0);
  return new ButtonTile(tile, config);
}

ButtonTile::~ButtonTile() { delete[] buttons; }
