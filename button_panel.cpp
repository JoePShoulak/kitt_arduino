// button_panel.cpp

#include <lvgl.h>
#include "button_panel.h"

ButtonPanel::ButtonPanel(lv_obj_t* parent, ButtonData const* config) {
  // Calculate sizing
  int spacing = 20; // consistent margin and spacing
  int button_size = (800 - spacing * 6) / (BUTTON_COUNT / 2); // ~136 px
  int grid_width = button_size * 2 + spacing * 3;
  int grid_height = button_size * (BUTTON_COUNT / 2) + spacing * 6;

  // Grid container (now direct child of parent, centered)
  lv_obj_t *grid = lv_obj_create(parent);
  lv_obj_remove_style_all(grid); // no background/border
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_size(grid, grid_width, grid_height);
  lv_obj_center(grid); // center the grid on screen

  // Define grid - 2 columns of button_size, 5 rows of button_size
  static lv_coord_t col_dsc[] = {button_size, button_size, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {button_size, button_size, button_size, button_size, button_size, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

  // Set equal padding around grid and between buttons
  lv_obj_set_style_pad_all(grid, spacing, 0);  // margin to edges (top = bottom = spacing)
  lv_obj_set_style_pad_row(grid, spacing, 0);  // spacing between rows
  lv_obj_set_style_pad_column(grid, spacing, 0);  // spacing between columns

  for (int i=0; i<BUTTON_COUNT; ++i) {
    buttons[i] = new Button(grid, config[i], i % 2, i / 2);
  }
};

ButtonPanel::~ButtonPanel() {
  for (int i=0; i<BUTTON_COUNT; ++i) {
    delete buttons[i];
  }
}
