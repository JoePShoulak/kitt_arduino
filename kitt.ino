// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>

#include "buttons.h"
#include "config.h"

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch  TouchDetector;

static lv_style_t style_button_square;

// Create the KITT button grid layout
void create_kitt_panel(lv_obj_t *parent) {
    // Make background black
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    // Initialize button style
    lv_style_init(&style_button_square);
    lv_style_set_radius(&style_button_square, 0); // square corners
    lv_style_set_border_width(&style_button_square, 0); // no border
    lv_style_set_shadow_width(&style_button_square, 0); // no shadow
    lv_style_set_outline_width(&style_button_square, 0); // no outline
    lv_style_set_pad_all(&style_button_square, 0); // no padding
    lv_style_set_text_color(&style_button_square, lv_color_hex(0x000000)); // black text
    lv_style_set_text_font(&style_button_square, &lv_font_montserrat_14);

    // Calculate sizing
    int spacing = 20; // consistent margin and spacing
    int button_size = (800 - spacing * 6) / 5; // ~136 px
    int grid_width = button_size * 2 + spacing * 3;
    int grid_height = button_size * 5 + spacing * 6;

    // Grid container (now direct child of parent, centered)
    lv_obj_t *grid = lv_obj_create(parent);
    lv_obj_remove_style_all(grid); // no background/border
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_size(grid, grid_width, grid_height);
    lv_obj_center(grid); // center the grid on screen

    // Define grid — 2 columns of button_size, 5 rows of button_size
    static lv_coord_t col_dsc[] = {button_size, button_size, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {button_size, button_size, button_size, button_size, button_size, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

    // Set equal padding around grid and between buttons
    lv_obj_set_style_pad_all(grid, spacing, 0);      // margin to edges (top = bottom = spacing)
    lv_obj_set_style_pad_row(grid, spacing, 0);      // spacing between rows
    lv_obj_set_style_pad_column(grid, spacing, 0);   // spacing between columns

    // Create ButtonSquare instances → fully move all button logic into ButtonSquare
    ButtonSquare *squares[BUTTON_COUNT];

    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        squares[i] = new ButtonSquare(grid, button_data[i], i % 2, i / 2, &style_button_square);
    }
}

void setup() {
    Serial.begin(115200); // Initialize Serial
    lv_init(); // Initialize LVGL
    tft.begin(); // Initialize Giga Display
    TouchDetector.begin();
    create_kitt_panel(lv_scr_act()); // Display our page
    Serial.println("KITT panel created");
    Serial.println();
}

void loop() {
    lv_timer_handler();
    delay(5);
}
