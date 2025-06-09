#include "gauge.h"

const lv_color_t Gauge::dark_colors[GAUGE_SEG_COUNT] = {
    GREEN_DARK, GREEN_DARK, GREEN_DARK, GREEN_DARK,
    YELLOW_DARK, YELLOW_DARK, YELLOW_DARK,
    RED_DARK, RED_DARK, RED_DARK};

const lv_color_t Gauge::lit_colors[GAUGE_SEG_COUNT] = {
    GREEN, GREEN, GREEN, GREEN,
    YELLOW, YELLOW, YELLOW,
    RED, RED, RED};

Gauge::Gauge(lv_obj_t *parent, const char *text) {
  container = lv_obj_create(parent);
  lv_obj_remove_style_all(container);
  lv_obj_set_layout(container, LV_LAYOUT_GRID);
  static lv_coord_t col_dsc[] = {GAUGE_WIDTH, 60, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {GAUGE_HEIGHT, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(container, col_dsc, row_dsc);
  lv_obj_set_size(container, GAUGE_WIDTH + 60, GAUGE_HEIGHT);

  lv_obj_t *bar_cont = lv_obj_create(container);
  lv_obj_remove_style_all(bar_cont);
  lv_obj_set_grid_cell(bar_cont, LV_GRID_ALIGN_START, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);
  lv_obj_set_layout(bar_cont, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(bar_cont, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(bar_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(bar_cont, GAUGE_SPACING, 0);

  for (int i = 0; i < GAUGE_SEG_COUNT; ++i) {
    lv_obj_t *bar = lv_obj_create(bar_cont);
    lv_obj_remove_style_all(bar);
    lv_obj_set_style_bg_color(bar, dark_colors[i], 0);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
    lv_obj_set_size(bar, GAUGE_SEG_W, GAUGE_SEG_H * 2);
    bars[i] = bar;
  }

  label = lv_label_create(container);
  lv_obj_set_grid_cell(label, LV_GRID_ALIGN_END, 1, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_color(label, WHITE, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
}

void Gauge::setLevel(float level) {
  if (level < 0.f)
    level = 0.f;
  if (level > 1.f)
    level = 1.f;
  int lit = (int)(level * GAUGE_SEG_COUNT + 0.5f);
  for (int i = 0; i < GAUGE_SEG_COUNT; ++i) {
    lv_color_t col = i < lit ? lit_colors[i] : dark_colors[i];
    lv_obj_set_style_bg_color(bars[i], col, 0);
  }
}

void Gauge::rotate(int16_t angle10) {
  lv_coord_t w = lv_obj_get_width(container);
  lv_coord_t h = lv_obj_get_height(container);
  lv_obj_set_size(container, h, w); // swap to avoid cropping
  lv_obj_set_style_transform_pivot_x(container, h / 2, 0);
  lv_obj_set_style_transform_pivot_y(container, w / 2, 0);
  lv_obj_set_style_transform_angle(container, angle10, 0);
}
