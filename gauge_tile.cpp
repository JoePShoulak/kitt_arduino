#include "gauge_tile.h"
#include "config.h"

static const char *gauge_labels[6] = {
    "G1", "G2", "G3", "G4", "G5", "G6"};

GaugeTile::GaugeTile(lv_obj_t *tileview, int row_id) {
  tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
  lv_obj_set_style_bg_color(tile, BLACK, 0);

  lv_obj_t *grid = lv_obj_create(tile);
  lv_obj_remove_style_all(grid);
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_size(grid, GRID_HEIGHT, 480); // treat as landscape grid
  lv_obj_center(grid);

  static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
  lv_obj_set_style_pad_all(grid, SPACING, 0);
  lv_obj_set_style_pad_row(grid, SPACING, 0);
  lv_obj_set_style_pad_column(grid, SPACING, 0);

  int idx = 0;
  for (int col = 0; col < 2; ++col) {
    for (int row = 0; row < 3; ++row) {
      gauges[idx] = new Gauge(grid, gauge_labels[idx]);
      lv_obj_set_grid_cell(gauges[idx]->getContainer(), LV_GRID_ALIGN_CENTER, col, 1,
                           LV_GRID_ALIGN_CENTER, row, 1);
      gauges[idx]->rotate(900);
      idx++;
    }
  }
}

GaugeTile::~GaugeTile() {
  for (auto &g : gauges) {
    delete g;
  }
}
