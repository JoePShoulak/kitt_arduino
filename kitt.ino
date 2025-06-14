// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include <lvgl.h>
#include "audio_helper.h"
#include "UI.h"

GigaDisplay_GFX tft;
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
}

void loop() {
  lv_timer_handler();
  audio_loop();
}
