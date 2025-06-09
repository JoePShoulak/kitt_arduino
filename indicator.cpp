#include "indicator.h"
#include "colors.h"
#include "config.h"

Indicator::Indicator(const IndicatorData& data, lv_obj_t* parent) : data(data) {
void Indicator::initStyle(lv_obj_t* obj) {
    lv_obj_remove_style_all(obj);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(obj, CIRCLE_DIAMETER / 2, 0);
    lv_obj_set_style_bg_color(obj, data.dark, 0);
    lv_obj_set_size(obj, CIRCLE_DIAMETER * 6 / 5, CIRCLE_DIAMETER);
}

    initStyle(indicator);

    lv_obj_t* lbl = lv_label_create(indicator);
    lv_obj_set_style_text_color(lbl, BLACK, 0);
    lv_label_set_text(lbl, data.label);
    lv_obj_center(lbl);

    this->indicator = indicator;
}

void Indicator::style(lv_obj_t* parent) {
    lv_obj_t* indicator = lv_obj_create(parent);
    lv_obj_remove_style_all(indicator);
    lv_obj_set_style_bg_opa(indicator, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(indicator, CIRCLE_DIAMETER / 2, 0);
    lv_obj_set_style_bg_color(indicator, data.dark, 0);
    lv_obj_set_size(indicator, CIRCLE_DIAMETER * 6 / 5, CIRCLE_DIAMETER);
}
