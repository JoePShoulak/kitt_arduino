#include "popup.h"
#include "colors.h"
#include "config.h"

static void ok_event_cb(lv_event_t* e) {
    lv_obj_t* overlay = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
    if (overlay) {
        lv_obj_del(overlay);
    }
}

lv_obj_t* show_error_popup(lv_obj_t* parent_tile, const char* msg) {
    if (!parent_tile) return nullptr;

    lv_obj_t* overlay = lv_obj_create(parent_tile);
    lv_obj_remove_style_all(overlay);
    lv_obj_set_size(overlay, lv_obj_get_width(parent_tile), lv_obj_get_height(parent_tile));
    lv_obj_set_style_bg_color(overlay, BLACK, 0);
    lv_obj_set_style_bg_opa(overlay, LV_OPA_50, 0);
    lv_obj_add_flag(overlay, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_pad_all(overlay, 0, 0);
    lv_obj_set_style_radius(overlay, 0, 0);
    lv_obj_set_style_border_width(overlay, 0, 0);
    lv_obj_center(overlay);

    // use flex column layout
    lv_obj_set_layout(overlay, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(overlay, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(overlay, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t* box = lv_obj_create(overlay);
    lv_obj_remove_style_all(box);
    lv_obj_set_size(box, POPUP_WIDTH, POPUP_HEIGHT);
    lv_obj_set_style_bg_color(box, WHITE, 0);
    lv_obj_set_style_bg_opa(box, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(box, 10, 0);
    lv_obj_set_style_pad_all(box, 20, 0);
    lv_obj_set_style_pad_row(box, 20, 0);
    lv_obj_set_layout(box, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(box, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(box, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_center(box);

    lv_obj_t* label = lv_label_create(box);
    lv_label_set_text(label, msg);
    lv_obj_set_style_text_color(label, BLACK, 0);

    lv_obj_t* btn = lv_btn_create(box);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 80, 40);
    lv_obj_set_style_radius(btn, 5, 0);
    lv_obj_set_style_bg_color(btn, GREEN, 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);

    lv_obj_t* btn_lbl = lv_label_create(btn);
    lv_label_set_text(btn_lbl, "OK");
    lv_obj_center(btn_lbl);

    lv_obj_add_event_cb(btn, ok_event_cb, LV_EVENT_CLICKED, overlay);

    return overlay;
}

