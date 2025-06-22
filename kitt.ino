// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include <lvgl.h>

#include "src/helpers/audio_helper.h"
#include "src/helpers/ble_helper.h"
#include "src/ui/UI.h"
#include "src/config/data.h"
#include "src/hardware/Scanner.h"

GigaDisplay_GFX tft;
Arduino_GigaDisplayTouch TouchDetector;

void setup()
{
  Serial.begin(115200); // Initialize Serial
  tft.begin();          // Initialize Giga Display
  TouchDetector.begin();
  ble_init();
  ui.init();
  audio_init(); // must come after ui, as it inits some of its elements with audio refs
}

void loop()
{
  lv_timer_handler(); // handles ui timers
  audio.update();     // needed for audio to play correctly
  ble_update();       // sends dummmy BLE data for now, for testing

  if (scanner.running())
    scanner.update(); // animates the scanner, if on
}
