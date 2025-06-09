// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>
#include <GigaAudio.h>

#include "button.h"
#include "button_panel.h"
#include "config.h"
#include "voice_tile.h"


// GigaAudio audio("USB DISK"); // replace with name of USB volume

// List of audio files to play in sequence
const char *audio_files[] = {"intro.wav", "explode.wav", "shoe.wav"};
const int audio_file_count = sizeof(audio_files) / sizeof(audio_files[0]);
int current_audio_index = 0;

// Helper to load the current audio file
// bool load_current_audio() {
//   if (!audio.load(const_cast<char*>(audio_files[current_audio_index]))) {
//     if (audio.hasError()) {
//       Serial.println(audio.errorMessage());
//     } else {
//       Serial.print("Cannot load WAV file ");
//       Serial.println(audio_files[current_audio_index]);
//     }
//     return false;
//   }
//   return true;
// }

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;
VoiceTile* voiceTile = nullptr;

void motor_override_cb(lv_event_t* e) {
  Serial.println("MOTOR override callback!");
}


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

  auto leftPanel = ButtonPanel::createTile(tiles, 0, button_panel1);
  voiceTile = new VoiceTile(tiles, 1, voice_buttons);
  auto rightPanel = ButtonPanel::createTile(tiles, 2, button_panel2);
  if (auto btn = rightPanel->getButton(0)) {
    btn->setCallback(motor_override_cb);
  }

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
