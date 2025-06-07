#include "voice_scene.h"
#include "buttons.h"

lv_obj_t* create_voice_tile(lv_obj_t* tileview, int row_id, ButtonData const* buttons) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    int spacing = 20;
    int button_size = (480 - spacing * 3) / 2; // bottom buttons width (screen width 480)
    int grid_width = button_size * 2 + spacing * 3;

    // Fill the screen height so the buttons sit at the very bottom
    int grid_height = 800;
    int viz_height = grid_height - button_size - spacing * 3;

    lv_obj_t* grid = lv_obj_create(tile);
    lv_obj_remove_style_all(grid);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_size(grid, grid_width, grid_height);
    lv_obj_center(grid);

    static lv_coord_t col_dsc[] = {button_size, button_size, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {viz_height, button_size, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
    lv_obj_set_style_pad_all(grid, spacing, 0);
    lv_obj_set_style_pad_row(grid, spacing, 0);
    lv_obj_set_style_pad_column(grid, spacing, 0);

    // Visualizer mockup using three columns of rounded rectangles
    lv_obj_t* viz = lv_obj_create(grid);
    lv_obj_remove_style_all(viz);
    lv_obj_set_style_bg_color(viz, BLACK, 0);
    lv_obj_set_style_bg_opa(viz, LV_OPA_COVER, 0);
    lv_obj_set_grid_cell(viz, LV_GRID_ALIGN_STRETCH, 0, 2,
                         LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_style_pad_all(viz, 10, 0);
    lv_obj_set_style_pad_column(viz, 15, 0);
    lv_obj_set_layout(viz, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(viz, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(viz, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    auto make_column = [&](int count) {
        lv_obj_t* col = lv_obj_create(viz);
        lv_obj_remove_style_all(col);
        lv_obj_set_size(col, LV_SIZE_CONTENT, viz_height);
        lv_obj_set_style_pad_row(col, 4, 0);
        lv_obj_set_layout(col, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(col, LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        int bar_h = 10;
        int bar_w = 100; // wider bars to fill more space
        int total = count * bar_h + (count - 1) * 4;
        int pad = (viz_height - total) / 2;
        if(pad < 0) pad = 0;
        lv_obj_set_style_pad_top(col, pad, 0);
        lv_obj_set_style_pad_bottom(col, pad, 0);

        for(int i = 0; i < count; ++i) {
            lv_obj_t* bar = lv_obj_create(col);
            lv_obj_remove_style_all(bar);
            lv_obj_set_style_bg_color(bar, RED_DARK, 0);
            lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
            lv_obj_set_style_radius(bar, bar_h / 2, 0);
            lv_obj_set_size(bar, bar_w, bar_h);
        }
    };

    // 3 columns: outer columns 19 bars, center column 37 bars
    make_column(19);
    make_column(37);
    make_column(19);

    // Two buttons at bottom row
    ButtonSquare* btn0 = new ButtonSquare(grid, buttons[0], 0, 1);
    ButtonSquare* btn1 = new ButtonSquare(grid, buttons[1], 1, 1);

    LV_UNUSED(btn0); // avoid unused warnings if compiled
    LV_UNUSED(btn1);

    return tile;
}
