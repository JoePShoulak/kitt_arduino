#include "gauge.h"

#include "config.h"

static constexpr int SEG_COUNT = 10;
static constexpr int SEG_HEIGHT = 20; // px
static constexpr int SEG_WIDTH = 40;  // px (approx 1x2 ratio)
static constexpr int SEG_GAP = 4;

lv_color_t Gauge::get_dark_color(int idx) {
  if (idx < 4)
    return GREEN_DARK;
  if (idx < 7)
    return YELLOW_DARK;
  return RED_DARK;
}

lv_color_t Gauge::get_light_color(int idx) {
  if (idx < 4)
    return GREEN;
  if (idx < 7)
    return YELLOW;
  return RED;
}

Gauge::Gauge(lv_obj_t *parent, const char *label) {
  container = lv_obj_create(parent);
  lv_obj_remove_style_all(container);
  lv_obj_set_style_pad_all(container, 0, 0);
  lv_obj_set_style_pad_row(container, 4, 0);
  lv_obj_set_layout(container, LV_LAYOUT_GRID);
  static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {LV_SIZE_CONTENT, LV_SIZE_CONTENT, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(container, col_dsc, row_dsc);

  label_obj = lv_label_create(container);
  lv_label_set_text(label_obj, label);
  lv_obj_set_style_text_color(label_obj, WHITE, 0);
  lv_obj_set_style_text_align(label_obj, LV_TEXT_ALIGN_RIGHT, 0);
  lv_obj_set_grid_cell(label_obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_START, 0, 1);

  lv_obj_t *row = lv_obj_create(container);
  lv_obj_remove_style_all(row);
  lv_obj_set_layout(row, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_style_pad_column(row, SEG_GAP, 0);
  lv_obj_set_grid_cell(row, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 1, 1);

  for (int i = 0; i < SEG_COUNT; ++i) {
    lv_obj_t *seg = lv_obj_create(row);
    lv_obj_remove_style_all(seg);
    lv_obj_set_style_bg_color(seg, get_dark_color(i), 0);
    lv_obj_set_style_bg_opa(seg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(seg, 3, 0);
    lv_obj_set_size(seg, SEG_WIDTH, SEG_HEIGHT);
    segments[i] = seg;
  }
}

void Gauge::setLevel(float level) {
  if (level < 0.f)
    level = 0.f;
  if (level > 1.f)
    level = 1.f;
  int active = (int)roundf(level * SEG_COUNT);
  for (int i = 0; i < SEG_COUNT; ++i) {
    lv_obj_set_style_bg_color(segments[i], i < active ? get_light_color(i) : get_dark_color(i), 0);
  }
}


