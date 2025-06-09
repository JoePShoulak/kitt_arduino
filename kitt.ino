// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>
#include <GigaAudio.h>

#include "button.h"
#include "button_panel.h"
#include "config.h"
#include "voice_scene.h"


// GigaAudio audio("USB DISK"); // replace with name of USB volume

// List of audio files to play in sequence
const char *audio_files[] = {"intro.wav", "explode.wav", "shoe.wav"};
const int audio_file_count = sizeof(audio_files) / sizeof(audio_files[0]);
int current_audio_index = 0;

// Helper to load the current audio file
bool load_current_audio() {
  if (!audio.load(const_cast<char*>(audio_files[current_audio_index]))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(audio_files[current_audio_index]);
    }
    return false;
  }
  return true;
}

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;

void make_panel(ButtonData const* config, lv_obj_t* tileview, int row_id) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    new ButtonPanel(tile, config);
}

ButtonData const voice_buttons[3] = {
    { "AUTO CRUISE", null_btn, true, true },
    { "NORMAL CRUISE", null_btn, true, true },
    { "PURSUIT", null_btn, true, true },
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
  // TODO: Make the voice tile a class so we can store the visualiser and indicators
  // and update them from the voice tile to reflect things like voice state, indicators, etc.
  lv_obj_t* voice_tile = create_voice_tile(tiles, 1, voice_buttons);
  make_panel(button_panel2, tiles, 2);

  lv_obj_set_tile_id(tiles, 1, 0, LV_ANIM_OFF); // start on voice tile

  // if (!audio.load("shoe.wav")) {  // replace with name of file to play
  //   if (audio.hasError()) Serial.println(audio.errorMessage());
  //   else Serial.println("Cannot load WAV file");
  //   return;
  // }
  // audio.play();

}

void loop() {
  lv_timer_handler();
//   if (audio.isFinished()) {
//     audio.play(); // restart the playback when it is complete
//     Serial.println("Restarting . . .");
//    }
}
