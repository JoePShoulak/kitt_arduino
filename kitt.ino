// kitt.ino

#include "audio_helper.h"
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplay.h>
#include <lvgl.h>

#include "config.h"
#include <popup.h>
#include <voice_synth.h>
#include <UI.h>

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;   
GigaDisplayBacklight backlight;
bool blackout = false;

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init();            // Initialize LVGL
  tft.begin();          // Initialize Giga Display
  TouchDetector.begin();
  backlight.begin();
  ui.init(audio);
  if (voiceTile && voiceTile->getIndicator(0) &&
      voiceTile->getIndicator(0)->getLVObj()) {
    lv_obj_t *aud_obj = voiceTile->getIndicator(0)->getLVObj();
    lv_obj_add_flag(aud_obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(aud_obj, aud_indicator_cb, LV_EVENT_ALL, nullptr);
  }

  Serial.println();
}

void loop() {
  lv_timer_handler();
  audio_loop();
}
