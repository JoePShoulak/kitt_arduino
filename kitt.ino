// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <lvgl.h>

#include "src/helpers/audio_helper.h"
#include "src/helpers/ble_helper.h"
#include "src/ui/UI.h"
#include "src/config/data.h"
#include "src/hardware/Hardware.h"
#include "src/helpers/serial_helper.h"

void setup()
{
  serial_init();

  print_init_status("BLE", ble_init());
  print_init_status("UI", ui.init());

  audio_init(); // must come after ui to init some ui elements with audio refs. Should come last because of ready clip. (void)
}

void loop()
{
  lv_timer_handler(); // handles ui timers
  audio.update();     // needed for audio to play correctly
  ble_update();       // sends dummmy BLE data for now, for testing

  hardware.update();
}
