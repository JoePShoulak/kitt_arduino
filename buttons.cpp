#include "buttons.h"
#include <Arduino.h>

ButtonSquare::ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row, lv_style_t *style)
  : label(data.label), color(data.color)
{
  Serial.print("Creating ButtonSquare: ");
  Serial.println(label);

  // Create the button
  btn = lv_btn_create(parent_grid);

  // Apply the full style
  lv_obj_add_style(btn, style, 0);

  // Set button background color (preserves per-button color override)
  lv_obj_set_style_bg_color(btn, color, 0);

  // Grid placement
  lv_obj_set_grid_cell(btn,
    LV_GRID_ALIGN_STRETCH, grid_col, 1,
    LV_GRID_ALIGN_STRETCH, grid_row, 1);

  // Create label
  label_obj = lv_label_create(btn);
  lv_label_set_text(label_obj, label);
  lv_obj_center(label_obj);
}

