// audio_helper.cpp
#include "audio_helper.h"

#include <lvgl.h>

#include "../misc/animations.h"
#include "../UI/UI.h"

GigaAudio audio("USB DISK");

void aud_ind_cb(lv_event_t *e)
{
  if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    audio.stop();
}

void audio_init()
{
  lv_obj_add_event_cb(ui.voiceTile->indicators[INDICATORS::aud]->getObj(), aud_ind_cb, LV_EVENT_CLICKED, &audio);
  lv_timer_create(voice_anim_cb, 50, &audio);
}

void audio_play(const char *file)
{
  if (audio.isPlaying())
    audio.stop();

  if (audio.load(const_cast<char *>(file)))
    audio.play();
}
