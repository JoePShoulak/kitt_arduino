#include "voice_scene.h"
#include "buttons.h"

lv_obj_t* create_voice_tile(lv_obj_t* tileview, int row_id, ButtonData const* buttons) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    int spacing = 20;
    int button_size = (480 - spacing * 3) / 2; // bottom buttons width (screen width 480)
    int grid_width = button_size * 2 + spacing * 3;
    int grid_height = 800; // full screen height

    lv_obj_t* grid = lv_obj_create(tile);
    lv_obj_remove_style_all(grid);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_size(grid, grid_width, grid_height);
    lv_obj_center(grid);

    static lv_coord_t col_dsc[] = {button_size, button_size, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {600, button_size, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
    lv_obj_set_style_pad_all(grid, spacing, 0);
    lv_obj_set_style_pad_row(grid, spacing, 0);
    lv_obj_set_style_pad_column(grid, spacing, 0);

    // Visualizer mockup using rounded rectangles
    lv_obj_t* viz = lv_obj_create(grid);
    lv_obj_remove_style_all(viz);
    lv_obj_set_style_bg_color(viz, BLACK, 0);
    lv_obj_set_grid_cell(viz, LV_GRID_ALIGN_STRETCH, 0, 2,
                         LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_style_pad_all(viz, 10, 0);
    lv_obj_set_layout(viz, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(viz, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(viz, LV_FLEX_ALIGN_SPACE_EVENLY,
                          LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);

    static int heights[5] = {150, 300, 450, 300, 150};
    for(int i = 0; i < 5; ++i) {
        lv_obj_t* bar = lv_obj_create(viz);
        lv_obj_remove_style_all(bar);
        lv_obj_set_style_bg_color(bar, GREEN, 0);
        lv_obj_set_style_radius(bar, 10, 0);
        lv_obj_set_size(bar, 30, heights[i]);
    }

    // Two buttons at bottom row
    ButtonSquare* btn0 = new ButtonSquare(grid, buttons[0], 0, 1);
    ButtonSquare* btn1 = new ButtonSquare(grid, buttons[1], 1, 1);

    LV_UNUSED(btn0); // avoid unused warnings if compiled
    LV_UNUSED(btn1);

    return tile;
}
