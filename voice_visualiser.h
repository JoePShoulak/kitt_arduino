#ifndef VOICE_VISUALIZER_H
#define VOICE_VISUALIZER_H

#include <lvgl.h>

#define SPACING 20
#define CIRCLE_DIAMETER 60
#define COLUMN_WIDTH (CIRCLE_DIAMETER * 6 / 5)
#define CENTER_WIDTH ((480 - CIRCLE_DIAMETER * 2 - SPACING * 4) * 9 / 10)
#define GRID_WIDTH (COLUMN_WIDTH * 2 + CENTER_WIDTH + SPACING * 4)
#define BUTTON_HEIGHT 85
#define GRID_HEIGHT 800
#define VISUALISER_HEIGHT (GRID_HEIGHT - BUTTON_HEIGHT * 3 - SPACING * 5)

class VoiceVisualiser {
    lv_obj_t* viz;
    lv_obj_t* cols[3];
    int col_count[3];

    void make_column(int id, int count);
    
public:
    VoiceVisualiser(lv_obj_t* parent);
    void set_cols_active(float ratio_norm);
};

#endif