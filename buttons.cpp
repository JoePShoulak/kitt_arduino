#include "buttons.h"
#include <Arduino.h>

static void btn_event_cb(lv_event_t * e) {
    ButtonSquare* self = static_cast<ButtonSquare*>(lv_event_get_user_data(e));
    if (self) self->handlePress();
}

ButtonSquare::ButtonSquare(lv_obj_t *parent_grid, const ButtonData &data, uint8_t grid_col, uint8_t grid_row)
    : label(data.label), color(data.color), toggleable(data.toggleable)
{
    Serial.print("Creating ButtonSquare: ");
    Serial.println(label);

    lv_style_init(&style);
    lv_style_set_radius(&style, 0);
    lv_style_set_border_width(&style, 0);
    lv_style_set_shadow_width(&style, 0);
    lv_style_set_outline_width(&style, 0);
    lv_style_set_pad_all(&style, 0);
    lv_style_set_text_color(&style, BLACK);
    lv_style_set_text_font(&style, &lv_font_montserrat_14);

    btn = lv_btn_create(parent_grid);
    lv_obj_add_style(btn, &style, 0);
    lv_obj_set_style_bg_color(btn, color, 0);

    lv_obj_set_grid_cell(btn,
        LV_GRID_ALIGN_STRETCH, grid_col, 1,
        LV_GRID_ALIGN_STRETCH, grid_row, 1);

    label_obj = lv_label_create(btn);
    lv_label_set_text(label_obj, label);
    lv_obj_center(label_obj);

    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, this);
}

void ButtonSquare::handlePress() {
    Serial.print("Button pressed: ");
    Serial.println(label);

    if (toggleable) {
        toggled = !toggled;
        updateVisual();
    }
}

void ButtonSquare::updateVisual() {
    if (toggleable) {
        if (toggled) {
            lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), 0); // bright red when on
        } else {
            lv_obj_set_style_bg_color(btn, color, 0); // original color when off
        }
    }
}
