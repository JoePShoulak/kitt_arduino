// kitt.ino

#include "audio_helper.h"
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay_GFX.h>
#include <lvgl.h>
#include <math.h>

#include "config.h"
#include "popup.h"
#include "voice_synth.h"
#include "UI.h"

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init();            // Initialize LVGL
  tft.begin();          // Initialize Giga Display
  TouchDetector.begin();

  ui.init();

  // audio_setup();
}

void loop() {
  lv_timer_handler();
  // audio_loop();
}
