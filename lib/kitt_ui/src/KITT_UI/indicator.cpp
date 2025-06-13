#include "indicator.h"
#include "colors.h"
#include "config.h"

Indicator::Indicator(const IndicatorData &data, lv_obj_t *parent) : data(data) {
  lv_obj_t *indicator = lv_obj_create(parent);
  set_style(indicator);
  lv_obj_set_style_bg_color(indicator, data.dark, 0);

  lv_obj_t *lbl = lv_label_create(indicator);
  lv_obj_set_style_text_color(lbl, BLACK, 0);
  lv_label_set_text(lbl, data.label);
  lv_obj_center(lbl);

  this->indicator = indicator;
}

void Indicator::toggle(bool on) {
  lv_obj_set_style_bg_color(this->indicator, on ? data.light : data.dark, 0);
}

void Indicator::set_style(lv_obj_t *obj) {
  lv_obj_remove_style_all(obj);
  lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
  lv_obj_set_style_radius(obj, CIRCLE_DIAMETER / 2, 0);
  lv_obj_set_size(obj, CIRCLE_DIAMETER * 6 / 5, CIRCLE_DIAMETER);
}
