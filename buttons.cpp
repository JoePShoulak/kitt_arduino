// buttons.cpp

#include "buttons.h"
#include <Arduino.h>

/* Member constructor */
ButtonSquare::ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row)
  : label(data.label), color(data.color)
{
  Serial.print("Creating ButtonSquare:");
  Serial.println(label);

  // Initialize button style
  lv_style_init(&style);
  lv_style_set_radius(&style, 0); // square corners
  lv_style_set_border_width(&style, 0); // no border
  lv_style_set_shadow_width(&style, 0); // no shadow
  lv_style_set_outline_width(&style, 0); // no outline
  lv_style_set_pad_all(&style, 0); // no padding
  lv_style_set_text_color(&style, BLACK); // black text
  lv_style_set_text_font(&style, &lv_font_montserrat_14);

  btn = lv_btn_create(parent_grid); // Create the button
  lv_obj_add_style(btn, &style, 0); // Apply the full style
  lv_obj_set_style_bg_color(btn, color, 0); // Set button background color

  // Grid placement
  lv_obj_set_grid_cell(btn,
    LV_GRID_ALIGN_STRETCH, grid_col, 1,
    LV_GRID_ALIGN_STRETCH, grid_row, 1);

  // Create label
  label_obj = lv_label_create(btn);
  lv_label_set_text(label_obj, label);
  lv_obj_center(label_obj);

  // Attach instance-aware event callback
  if (data.callback) 
    lv_obj_add_event_cb(btn, data.callback, LV_EVENT_CLICKED, this);
}

/* Instance handler */
void ButtonSquare::handlePress() {
  Serial.print("Button pressed: ");
  Serial.println(label);
}
