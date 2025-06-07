// buttons.cpp

#include "buttons.h"
#include <Arduino.h>

/* Static callback: routes event to instance method */
static void btn_event_cb(lv_event_t * e) {
    ButtonSquare* self = static_cast<ButtonSquare*>(lv_event_get_user_data(e));
    if (self) self->handlePress();
}

/* Member constructor */
ButtonSquare::ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row, lv_style_t *style)
  : label(data.label), color(data.color)
{
    Serial.print("Creating ButtonSquare:");
    Serial.println(label);
    
    btn = lv_btn_create(parent_grid); // Create the button
    lv_obj_add_style(btn, style, 0); // Apply the full style
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
    if (data.callback) {
        lv_obj_add_event_cb(btn, data.callback, LV_EVENT_CLICKED, this);
    }
}

/* Instance handler */
void ButtonSquare::handlePress() {
    Serial.print("Button pressed: ");
    Serial.println(label);
}
