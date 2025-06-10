// kitt.ino

#include "audio_helper.h"
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplay.h>
#include <lvgl.h>
#include <math.h>

#include "config.h"
#include "popup.h"
#include "voice_synth.h"
#include "UI.h"

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

  ui.init();

  // audio_setup();
}

void loop() {
  lv_timer_handler();
  // audio_loop();

  if (blackout) {
    GDTpoint_t points[GT911_MAX_CONTACTS];
    uint8_t contacts = TouchDetector.getTouchPoints(points);
    if (contacts > 0) {
      blackout = false;
      backlight.set(255);
      if (blackout_btn && blackout_btn->isToggled()) {
        blackout_btn->handlePress();
      }
    }
  }
}
