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

#include "src/tiles/button_tile.h"

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
  scanner.begin(true);
  ble_start();

  audio_play("ready.wav"); // also inits the audio
}

void loop()
{
  // check states
  ui.getRightPanel()->getButton(7)->isToggled() ? scanner.start() : scanner.stop();

  // update
  lv_timer_handler();
  audio.update();
  scanner.update();
  ble_update();
}
