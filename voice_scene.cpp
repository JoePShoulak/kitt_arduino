#include "voice_scene.h"
#include "button.h"
#include "voice_visualiser.h"
#include "indicator.h"
#include "config.h"

static VoiceVisualiser* g_visualiser = nullptr;
static lv_timer_t* viz_timer = nullptr;

static const float voice_pattern[] = {
    0.05f, 0.12f, 0.25f, 0.4f, 0.65f, 0.5f, 0.3f, 0.15f
};
static const size_t voice_pattern_len = sizeof(voice_pattern) / sizeof(voice_pattern[0]);
static size_t voice_pattern_idx = 0;

static void voice_timer_cb(lv_timer_t* timer) {
    LV_UNUSED(timer);
    if (!g_visualiser) return;
    g_visualiser->set_cols_active(voice_pattern[voice_pattern_idx]);
    voice_pattern_idx = (voice_pattern_idx + 1) % voice_pattern_len;
}


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
    Indicator* indicator_objs[8];

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

        for (int i = 0; i < 4; ++i) 
            indicator_objs[side * 4 + i] = new Indicator(indicators[side * 4 + i], column);
    }

    auto viz = new VoiceVisualiser(grid);
    g_visualiser = viz;

    if (!viz_timer)
        viz_timer = lv_timer_create(voice_timer_cb, 100, nullptr);

    // debug initial state
    viz->set_cols_active(voice_pattern[0]);
    indicator_objs[0]->toggle(true);
    indicator_objs[2]->toggle(true);

    // Three stacked buttons in the centre column with custom colours
    Button* btn0 = new Button(grid, buttons[0], 1, 1, ORANGE_DARK, ORANGE);
    Button* btn1 = new Button(grid, buttons[1], 1, 2, GREEN_DARK, GREEN);
    Button* btn2 = new Button(grid, buttons[2], 1, 3, BLUE_DARK, BLUE);

    return tile;
}
