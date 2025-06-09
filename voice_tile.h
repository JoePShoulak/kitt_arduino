#ifndef VOICE_TILE_H
#define VOICE_TILE_H

#include "button.h"
#include "indicator.h"
#include "voice_visualiser.h"
#include <lvgl.h>

class VoiceTile {
    lv_obj_t *tile;
    VoiceVisualiser *visualiser;
    Indicator *indicators[8];
    Button *buttons[3];

  public:
    VoiceTile(lv_obj_t *tileview, int row_id, ButtonData const *button_data);

    lv_obj_t *getTile() const { return tile; }
    VoiceVisualiser *getVisualiser() const { return visualiser; }
    Indicator *getIndicator(int index) const {
        return (index >= 0 && index < 8) ? indicators[index] : nullptr;
    }
    Button *getButton(int index) const {
        return (index >= 0 && index < 3) ? buttons[index] : nullptr;
    }

    ~VoiceTile();
};

#endif
