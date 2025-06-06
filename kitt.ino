#include <Arduino_GigaDisplay_GFX.h>
#include <lvgl.h>

// Initialize display object
GigaDisplay_GFX tft;

// Button labels (matching your reference image)
const char *button_labels[] = {
    "TURBO BOOST",
    "MAP SYSTEM",
    "SKI MODE",
    "VOLTAGE OUTPUT",
    "VITAL SCAN",
    "EVADE",
    "RANGE BRITE",
    "RADAR IMAGE",
    "MISSILE",
    "SMOKE RELEASE"
};

const uint8_t NUM_BUTTONS = sizeof(button_labels) / sizeof(button_labels[0]);

// Button background colors (matching your reference image)
const lv_color_t button_colors[] = {
    lv_color_hex(0x990000), // TURBO BOOST
    lv_color_hex(0xFFFF66), // MAP SYSTEM
    lv_color_hex(0xFFFFFF), // SKI MODE
    lv_color_hex(0xFFFF66), // VOLTAGE OUTPUT
    lv_color_hex(0x66FF66), // VITAL SCAN
    lv_color_hex(0x66FF66), // EVADE
    lv_color_hex(0x66FF66), // RANGE BRITE
    lv_color_hex(0x66FF66), // RADAR IMAGE
    lv_color_hex(0x990000), // MISSILE
    lv_color_hex(0x990000)  // SMOKE RELEASE
};

// Styles
static lv_style_t style_kitt_button;
static lv_style_t style_arrow_button;

// Create the KITT button grid layout with left/right arrows
void create_kitt_panel(lv_obj_t *parent) {
    // Make background black
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    // Initialize button style
    lv_style_init(&style_kitt_button);
    lv_style_set_radius(&style_kitt_button, 0); // square corners
    lv_style_set_border_width(&style_kitt_button, 0); // no border
    lv_style_set_shadow_width(&style_kitt_button, 0); // no shadow
    lv_style_set_outline_width(&style_kitt_button, 0); // no outline
    lv_style_set_pad_all(&style_kitt_button, 0); // no padding
    lv_style_set_text_color(&style_kitt_button, lv_color_hex(0x000000)); // black text
#if LV_FONT_MONTSERRAT_20
    lv_style_set_text_font(&style_kitt_button, &lv_font_montserrat_20);
#else
    lv_style_set_text_font(&style_kitt_button, &lv_font_montserrat_14); // fallback
#endif

    // Initialize arrow button style
    lv_style_init(&style_arrow_button);
    lv_style_set_radius(&style_arrow_button, 0);
    lv_style_set_bg_color(&style_arrow_button, lv_color_hex(0x333333)); // dark gray
    lv_style_set_border_width(&style_arrow_button, 0);
    lv_style_set_shadow_width(&style_arrow_button, 0);
    lv_style_set_outline_width(&style_arrow_button, 0);
    lv_style_set_pad_all(&style_arrow_button, 0);
    lv_style_set_text_color(&style_arrow_button, lv_color_hex(0xFFFFFF));
#if LV_FONT_MONTSERRAT_20
    lv_style_set_text_font(&style_arrow_button, &lv_font_montserrat_20);
#else
    lv_style_set_text_font(&style_arrow_button, &lv_font_montserrat_14);
#endif

    // Calculate sizing
    int spacing = 20; // consistent margin and spacing
    int button_size = (800 - spacing * 6) / 5; // ~136 px
    int grid_width = button_size * 2 + spacing * 3;
    int grid_height = button_size * 5 + spacing * 6;

    // Create flex container to hold [left arrow] [grid] [right arrow]
    lv_obj_t *flex_row = lv_obj_create(parent);
    lv_obj_remove_style_all(flex_row); // no background/border
    lv_obj_set_size(flex_row, 480, 800); // FULL SCREEN
    lv_obj_set_pos(flex_row, 0, 0);      // flush to edges
    lv_obj_set_flex_flow(flex_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(flex_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(flex_row, 0, 0);
    lv_obj_set_style_pad_row(flex_row, 0, 0);
    lv_obj_set_style_pad_column(flex_row, 0, 0);

    // Left arrow button
    lv_obj_t *left_arrow = lv_btn_create(flex_row);
    lv_obj_add_style(left_arrow, &style_arrow_button, 0);
    lv_obj_set_size(left_arrow, 60, grid_height); // tall side button
    lv_obj_align(left_arrow, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_t *left_label = lv_label_create(left_arrow);
    lv_label_set_text(left_label, "<");
    lv_obj_center(left_label);

    // Grid container
    lv_obj_t *grid = lv_obj_create(flex_row);
    lv_obj_remove_style_all(grid); // no background/border
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_size(grid, grid_width, grid_height);

    // Define grid — 2 columns of button_size, 5 rows of button_size
    static lv_coord_t col_dsc[] = {button_size, button_size, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {button_size, button_size, button_size, button_size, button_size, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

    // Set equal padding around grid and between buttons
    lv_obj_set_style_pad_all(grid, spacing, 0);      // margin to edges (top = bottom = spacing)
    lv_obj_set_style_pad_row(grid, spacing, 0);      // spacing between rows
    lv_obj_set_style_pad_column(grid, spacing, 0);   // spacing between columns

    // Create buttons directly in the grid
    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_t *btn = lv_btn_create(grid);
        lv_obj_add_style(btn, &style_kitt_button, 0);

        // Per-button color:
        lv_obj_set_style_bg_color(btn, button_colors[i], 0);

        lv_obj_set_grid_cell(btn,
            LV_GRID_ALIGN_STRETCH, i % 2, 1,
            LV_GRID_ALIGN_STRETCH, i / 2, 1);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, button_labels[i]);
        lv_obj_center(label);
    }

    // Right arrow button
    lv_obj_t *right_arrow = lv_btn_create(flex_row);
    lv_obj_add_style(right_arrow, &style_arrow_button, 0);
    lv_obj_set_size(right_arrow, 60, grid_height); // tall side button
    lv_obj_align(right_arrow, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_t *right_label = lv_label_create(right_arrow);
    lv_label_set_text(right_label, ">");
    lv_obj_center(right_label);
}

void setup() {
    Serial.begin(115200);

    // Initialize LVGL
    lv_init();

    // Initialize Giga Display → this automatically sets up the LVGL display
    tft.begin();

    // Now you can use lv_scr_act() directly
    create_kitt_panel(lv_scr_act());
}

void loop() {
    lv_timer_handler();
    delay(5);
}
