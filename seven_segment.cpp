#include "seven_segment.h"
#include "colors.h"

static const int DIGIT_WIDTH = 60;


static lv_obj_t *create_seg(lv_obj_t *parent, int x, int y, int w, int h,
                            lv_color_t color_off) {
  lv_obj_t *seg = lv_obj_create(parent);
  lv_obj_remove_style_all(seg);
  lv_obj_set_pos(seg, x, y);
  lv_obj_set_size(seg, w, h);
  lv_obj_set_style_bg_color(seg, color_off, 0);
  lv_obj_set_style_bg_opa(seg, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(seg, 0, 0);
  lv_obj_set_style_radius(seg, 2, 0);
  return seg;
}

void SevenSegmentDisplay::createDigit(lv_obj_t *parent, int idx) {
  const int w = DIGIT_WIDTH;
  const int h = 120;
  const int t = 12;
  lv_color_t off = RED_DARK;
  lv_obj_t *digit = lv_obj_create(parent);
  lv_obj_remove_style_all(digit);
  lv_obj_set_size(digit, w, h);
  lv_obj_set_style_bg_opa(digit, LV_OPA_TRANSP, 0);
  lv_obj_set_style_pad_all(digit, 0, 0);

  segments[idx][0] = create_seg(digit, t, 0, w - 2 * t, t, off);         // top
  segments[idx][1] = create_seg(digit, w - t, t, t, h / 2 - t, off);     // top-right
  segments[idx][2] = create_seg(digit, w - t, h / 2, t, h / 2 - t, off); // bottom-right
  segments[idx][3] = create_seg(digit, t, h - t, w - 2 * t, t, off);     // bottom
  segments[idx][4] = create_seg(digit, 0, h / 2, t, h / 2 - t, off);     // bottom-left
  segments[idx][5] = create_seg(digit, 0, t, t, h / 2 - t, off);         // top-left
  segments[idx][6] = create_seg(digit, t, h / 2 - t / 2, w - 2 * t, t, off); // middle
}

SevenSegmentDisplay::SevenSegmentDisplay(lv_obj_t *parent, const char *labelText) {
  container = lv_obj_create(parent);
  lv_obj_remove_style_all(container);
  lv_obj_set_width(container, lv_pct(100));
  lv_obj_set_height(container, 180); // larger than before
  lv_obj_set_layout(container, LV_LAYOUT_NONE);
  lv_obj_set_style_pad_all(container, 0, 0);

  lv_obj_t *row = lv_obj_create(container);
  lv_obj_remove_style_all(row);
  lv_obj_set_layout(row, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(row, 12, 0);
  lv_obj_set_style_pad_all(row, 0, 0);
  lv_obj_set_size(row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_align(row, LV_ALIGN_TOP_MID, 0, 0);

  for (int i = 0; i < 3; ++i) {
    createDigit(row, i);
  }

  label = lv_label_create(container);
  lv_label_set_text(label, labelText ? labelText : "");
  lv_obj_set_style_text_color(label, WHITE, 0);
  // Use the default 14pt font since larger fonts may not be compiled
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_width(label, LV_SIZE_CONTENT);
  // Place the label to the right of the digit row with some margin
  lv_obj_align_to(label, row, LV_ALIGN_OUT_RIGHT_BOTTOM, DIGIT_WIDTH, 0);

  setValue(0);
}

static const uint8_t digit_masks[10] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111  // 9
};

void SevenSegmentDisplay::setValue(int value) {
  if (value < 0)
    value = 0;
  if (value > 999)
    value = 999;
  int vals[3] = {value / 100, (value / 10) % 10, value % 10};
  for (int d = 0; d < 3; ++d) {
    uint8_t mask = digit_masks[vals[d]];
    for (int s = 0; s < 7; ++s) {
      lv_color_t color = (mask & (1 << s)) ? RED : RED_DARK;
      lv_obj_set_style_bg_color(segments[d][s], color, 0);
    }
  }
}
