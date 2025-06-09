#include "voice_visualiser.h"
#include "colors.h"
#include "config.h"

VoiceVisualiser::VoiceVisualiser(lv_obj_t *parent) {
    viz = lv_obj_create(parent);
    lv_obj_remove_style_all(viz);
    lv_obj_set_style_bg_color(viz, BLACK, 0);
    lv_obj_set_style_bg_opa(viz, LV_OPA_COVER, 0);
    lv_obj_set_grid_cell(viz, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_style_pad_all(viz, 10, 0);
    lv_obj_set_style_pad_column(viz, 15, 0);
    lv_obj_set_layout(viz, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(viz, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(viz, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    make_column(0, 19);
    make_column(1, 29);
    make_column(2, 19);
}

void VoiceVisualiser::make_column(int id, int count) {
    lv_obj_t *col = lv_obj_create(viz);
    lv_obj_remove_style_all(col);
    lv_obj_set_size(col, LV_SIZE_CONTENT, VISUALISER_HEIGHT);
    lv_obj_set_style_pad_row(col, 4, 0);
    lv_obj_set_layout(col, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(col, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    int bar_h = 10;
    int bar_w = (CENTER_WIDTH - 50) / 3; // fit within the smaller visualizer
    int total = count * bar_h + (count - 1) * 4;
    int pad = (VISUALISER_HEIGHT - total) / 2;
    if (pad < 0)
        pad = 0;
    lv_obj_set_style_pad_top(col, pad, 0);
    lv_obj_set_style_pad_bottom(col, pad, 0);

    for (int i = 0; i < count; ++i) {
        lv_obj_t *bar = lv_obj_create(col);
        lv_obj_remove_style_all(bar);
        lv_obj_set_style_bg_color(bar, RED_DARK, 0);
        lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
        lv_obj_set_style_radius(bar, bar_h / 2, 0);
        lv_obj_set_size(bar, bar_w, bar_h);
    }

    cols[id] = col;
    col_count[id] = count;
}

void VoiceVisualiser::set_cols_active(float ratio_norm) {
    lv_obj_t *center = cols[1];
    int child_count = lv_obj_get_child_cnt(center);

    for (int n = 0; n < 3; ++n) {
        lv_obj_t *col = cols[n];
        int col_count = lv_obj_get_child_cnt(col);

        for (int i = 0; i < col_count; ++i) {
            lv_obj_t *child = lv_obj_get_child(col, i);

            int dist = child_count / 2 - i - (child_count - col_count) / 2;
            // int dist = child_count + i - col_count / 2;
            dist = dist < 0 ? -dist : dist;

            if (dist > ratio_norm * (child_count / 2)) {
                lv_obj_set_style_bg_color(child, RED_DARK, 0);
            } else {
                lv_obj_set_style_bg_color(child, RED, 0);
            }
        }
    }
}
