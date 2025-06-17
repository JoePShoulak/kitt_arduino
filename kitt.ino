// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include <lvgl.h>

#define SCANNER_DATA_PIN 6
#include "Scanner.h"
#include "audio_helper.h"
#include "UI.h"

GigaDisplay_GFX tft;
Arduino_GigaDisplayTouch TouchDetector;
GigaDisplayBacklight backlight;
Scanner scanner(10);

void setup()
{
  Serial.begin(115200); // Initialize Serial
  lv_init();            // Initialize LVGL
  tft.begin();          // Initialize Giga Display
  TouchDetector.begin();
  backlight.begin();
  ui.init(audio);
  audio_play("ready.wav"); // also inits the audio
}

void loop()
{
  lv_timer_handler();
  audio.update();
  scanner.update();
}
