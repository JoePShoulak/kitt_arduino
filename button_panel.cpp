// button_panel.cpp

#include "button_panel.h"
#include <lvgl.h>

ButtonPanel::ButtonPanel(lv_obj_t *parent, ButtonData const *config) {
  // Calculate sizing
  int button_size = PANEL_BUTTON_SIZE; // ~136 px
  int grid_width = PANEL_GRID_WIDTH;
  int grid_height = PANEL_GRID_HEIGHT;

  // Grid container (now direct child of parent, centered)
  lv_obj_t *grid = lv_obj_create(parent);
  lv_obj_remove_style_all(grid); // no background/border
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_size(grid, grid_width, grid_height);
  lv_obj_center(grid); // center the grid on screen

  // Define grid - 2 columns of button_size, 5 rows of button_size
  static lv_coord_t col_dsc[] = {button_size, button_size,
                                 LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {button_size, button_size,
                                 button_size, button_size,
                                 button_size, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

  // Set equal padding around grid and between buttons
  lv_obj_set_style_pad_all(grid, SPACING, 0);    // margin to edges
  lv_obj_set_style_pad_row(grid, SPACING, 0);    // spacing between rows
  lv_obj_set_style_pad_column(grid, SPACING, 0); // spacing between columns

  for (int i = 0; i < BUTTON_COUNT; ++i) {
    buttons[i] = new Button(grid, config[i], i % 2, i / 2);
  }
};

ButtonPanel::~ButtonPanel() {
  for (int i = 0; i < BUTTON_COUNT; ++i) {
    delete buttons[i];
  }
}

ButtonPanel *ButtonPanel::createTile(lv_obj_t *tileview, int row_id,
                                     ButtonData const *config) {
  auto *tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
  lv_obj_set_style_bg_color(tile, BLACK, 0);
  return new ButtonPanel(tile, config);
}
