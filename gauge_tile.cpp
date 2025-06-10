#include "gauge_tile.h"
#include "gauge.h"
#include "colors.h"
#include "config.h"

GaugeTile::GaugeTile(lv_obj_t *tileview, int row_id, const char *const *labels,
                     int count)
    : gauge_count(count) {
  tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
  lv_obj_set_style_bg_color(tile, BLACK, 0);

  lv_obj_t *container = lv_obj_create(tile);
  lv_obj_remove_style_all(container);
  lv_obj_set_size(container, GRID_WIDTH, GRID_HEIGHT);
  lv_obj_center(container);
  lv_obj_set_layout(container, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_all(container, SPACING, 0);
  lv_obj_set_style_pad_row(container, SPACING, 0);

  gauges = new Gauge *[gauge_count];
  for (int i = 0; i < gauge_count; ++i) {
    gauges[i] = new Gauge(container, labels[i]);
  }
}

GaugeTile::~GaugeTile() {
  for (int i = 0; i < gauge_count; ++i) {
    delete gauges[i];
  }
  delete[] gauges;
}

Gauge *GaugeTile::getGauge(int idx) const {
  if (idx < 0 || idx >= gauge_count)
    return nullptr;
  return gauges[idx];
}
