#include "gauge.h"
#include "colors.h"
#include <ctype.h>

Gauge::Gauge(lv_obj_t *parent, const char *label) {
  container = lv_obj_create(parent);
  lv_obj_remove_style_all(container);
  lv_obj_set_layout(container, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
  // Place children from the top of the container so the label appears above
  // the row of bars. Align cross axis to the end so the gauge bars stick to
  // the right edge while the label uses right text alignment.
  lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_all(container, 0, 0);
  lv_obj_set_style_pad_row(container, 0, 0);
  lv_obj_set_width(container, lv_pct(100));

  label_obj = lv_label_create(container);
  char buf[32];
  int i = 0;
  if (label) {
    for (; label[i] && i < 31; ++i) {
      buf[i] = toupper((unsigned char)label[i]);
    }
  }
  buf[i] = '\0';
  lv_label_set_text(label_obj, buf);
  lv_obj_set_style_text_color(label_obj, WHITE, 0);
  // Use the default 14pt font to avoid missing font errors
  lv_obj_set_style_text_font(label_obj, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_align(label_obj, LV_TEXT_ALIGN_RIGHT, 0);
  lv_obj_set_width(label_obj, lv_pct(100));
  lv_obj_set_style_pad_bottom(label_obj, 0, 0);
  lv_obj_set_style_pad_right(label_obj, 0, 0);
  lv_obj_set_style_pad_top(label_obj, 0, 0);
  // Drop the label further so it sits immediately above the bar row
  lv_obj_set_style_translate_y(label_obj, 24, 0);

  lv_obj_t *row = lv_obj_create(container);
  lv_obj_remove_style_all(row);
  lv_obj_set_layout(row, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  // Align the row's children from left to right but keep them anchored to the
  // bottom of the row so the segments sit neatly in a line.
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(row, 2, 0);
  lv_obj_set_style_pad_row(row, 0, 0);
  lv_obj_set_width(row, LV_SIZE_CONTENT);

  int h = 20;
  int w = 40;
  for (int n = 0; n < 10; ++n) {
    lv_obj_t *bar = lv_obj_create(row);
    lv_obj_remove_style_all(bar);
    lv_obj_set_style_radius(bar, 3, 0);
    lv_obj_set_size(bar, w, h);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
    lv_color_t dark, light;
    if (n < 4) {
      dark = GREEN_DARK;
      light = GREEN;
    } else if (n < 7) {
      dark = YELLOW_DARK;
      light = YELLOW;
    } else {
      dark = RED_DARK;
      light = RED;
    }
    dark_colors[n] = dark;
    light_colors[n] = light;
    lv_obj_set_style_bg_color(bar, dark, 0);
    bars[n] = bar;
  }
}

void Gauge::setValue(float norm) {
  if (norm < 0.f)
    norm = 0.f;
  if (norm > 1.f)
    norm = 1.f;
  int active = (int)(norm * 10 + 0.5f);
  for (int n = 0; n < 10; ++n) {
    lv_obj_set_style_bg_color(bars[n], n < active ? light_colors[n] : dark_colors[n], 0);
  }
}
