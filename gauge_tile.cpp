#include "gauge_tile.h"
#include "colors.h"

GaugeTile::GaugeTile(lv_obj_t *tileview, int row_id, const char *label) {
  tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
  lv_obj_set_style_bg_color(tile, BLACK, 0);

  gauge = new Gauge(tile, label);
  lv_obj_center(gauge->getContainer());
}

GaugeTile::~GaugeTile() { delete gauge; }


