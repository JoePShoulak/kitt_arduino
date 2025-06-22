// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include <lvgl.h>

#define SCANNER_DATA_PIN 6
#include "src/hardware/Scanner.h"
#include "src/helpers/audio_helper.h"
#include "src/UI.h"
#include "src/helpers/ble_helper.h"

GigaDisplay_GFX tft;
Arduino_GigaDisplayTouch TouchDetector;
Scanner scanner(10);

void setup()
{
  Serial.begin(115200); // Initialize Serial
  tft.begin();          // Initialize Giga Display
  TouchDetector.begin();
  ui.init();
  audio_init();
  scanner.begin(true);
  ble_start();

  audio_play("ready.wav"); // also inits the audio
}

void loop()
{
  // check states
  ui.rightButtonTile->button(7)->isToggled() ? scanner.start() : scanner.stop();

  // update
  lv_timer_handler();
  audio.update();
  scanner.update();
  ble_update();
}
