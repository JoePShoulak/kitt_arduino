// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>

#include "button.h"
#include "button_panel.h"
#include "config.h"
#include "voice_scene.h"
#include "voice_visualiser.h"

#include <GigaAudio.h>

GigaAudio audio("USB DISK"); // replace with name of USB volume

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;

unsigned long last_viz_update = 0;
const float voice_pattern[] = {0.05f, 0.12f, 0.25f, 0.4f, 0.65f, 0.5f, 0.3f, 0.15f};
const size_t voice_pattern_len = sizeof(voice_pattern) / sizeof(voice_pattern[0]);
size_t voice_pattern_idx = 0;

void make_panel(ButtonData const* config, lv_obj_t* tileview, int row_id) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    new ButtonPanel(tile, config);
}

ButtonData const voice_buttons[3] = {
    { "AUTO CRUISE", null_btn, true, 1000 },
    { "NORMAL CRUISE", null_btn, true, 1000 },
    { "PURSUIT", null_btn, true, 1000 },
};

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init(); // Initialize LVGL
  tft.begin(); // Initialize Giga Display
  TouchDetector.begin();

  auto* canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);
  
  auto* tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  make_panel(button_panel1, tiles, 0);
  lv_obj_t* voice_tile = create_voice_tile(tiles, 1, voice_buttons);
  make_panel(button_panel2, tiles, 2);

  lv_obj_set_tile_id(tiles, 1, 0, LV_ANIM_OFF); // start on voice tile
  LV_UNUSED(voice_tile); 

  if (!audio.load("kitt_shoe.wav")) {  // replace with name of file to play
    if (audio.hasError()) Serial.println(audio.errorMessage());
    else Serial.println("Cannot load WAV file");
    return;
  }
  audio.play();

}

void loop() {
  lv_timer_handler();
  unsigned long now = millis();
  if (now - last_viz_update > 100) {
    last_viz_update = now;
    VoiceVisualiser* viz = get_voice_visualiser();
    if (viz) {
      viz->set_cols_active(voice_pattern[voice_pattern_idx]);
      voice_pattern_idx = (voice_pattern_idx + 1) % voice_pattern_len;
    }
  }
  if (audio.isFinished()) {
    audio.play(); // restart the playback when it is complete
    Serial.println("Restarting . . .");
  }
}
