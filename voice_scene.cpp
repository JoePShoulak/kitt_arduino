#include "voice_scene.h"
#include "buttons.h"
#include "voice_visualiser.h"

lv_obj_t* create_voice_tile(lv_obj_t* tileview, int row_id, ButtonData const* buttons) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    lv_obj_t* grid = lv_obj_create(tile);
    lv_obj_remove_style_all(grid);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_size(grid, GRID_WIDTH, GRID_HEIGHT);
    lv_obj_center(grid);

    static lv_coord_t col_dsc[] = {COLUMN_WIDTH, CENTER_WIDTH, COLUMN_WIDTH, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {VISUALISER_HEIGHT, BUTTON_HEIGHT, BUTTON_HEIGHT, BUTTON_HEIGHT, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
    lv_obj_set_style_pad_all(grid, SPACING, 0);
    lv_obj_set_style_pad_row(grid, SPACING, 0);
    lv_obj_set_style_pad_column(grid, SPACING, 0);

    // left and right columns of indicator lights evenly spaced vertically
    static const char* left_labels[4] = {"AIR", "OIL", "P1", "P2"};
    static const char* right_labels[4] = {"S1", "S2", "P3", "P4"};
    for(int side = 0; side < 2; ++side) {
        int col = side == 0 ? 0 : 2;
        lv_obj_t* column = lv_obj_create(grid);
        lv_obj_remove_style_all(column);
        lv_obj_set_grid_cell(column, LV_GRID_ALIGN_CENTER, col, 1,
                             LV_GRID_ALIGN_STRETCH, 0, 4);
        lv_obj_set_layout(column, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(column, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(column, LV_FLEX_ALIGN_SPACE_EVENLY,
                              LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column, COLUMN_WIDTH);

        for(int i = 0; i < 4; ++i) {
            lv_obj_t* light = lv_obj_create(column);
            lv_obj_remove_style_all(light);
            lv_obj_set_style_bg_opa(light, LV_OPA_COVER, 0);
            lv_obj_set_style_radius(light, CIRCLE_DIAMETER / 2, 0);
            lv_obj_set_style_bg_color(light, i < 2 ? YELLOW_DARK : RED_DARK, 0);
            lv_obj_set_size(light, CIRCLE_DIAMETER * 6 / 5, CIRCLE_DIAMETER);

            lv_obj_t* lbl = lv_label_create(light);
            lv_obj_set_style_text_color(lbl, BLACK, 0);
            lv_label_set_text(lbl, side == 0 ? left_labels[i] : right_labels[i]);
            lv_obj_center(lbl);
        }
    }

    auto viz = new VoiceVisualiser(grid);

    // Three stacked buttons in the centre column with custom colours
    ButtonSquare* btn0 = new ButtonSquare(grid, buttons[0], 1, 1, GREEN_DARK, GREEN);
    ButtonSquare* btn1 = new ButtonSquare(grid, buttons[1], 1, 2, ORANGE_DARK, ORANGE);
    ButtonSquare* btn2 = new ButtonSquare(grid, buttons[2], 1, 3, BLUE_DARK, BLUE);

    LV_UNUSED(btn0); // avoid unused warnings if compiled
    LV_UNUSED(btn1);
    LV_UNUSED(btn2);

    return tile;
}
