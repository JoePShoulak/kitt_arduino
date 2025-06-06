#include "buttons.h"
#include <Arduino.h>

ButtonSquare::ButtonSquare(const char *label_text, lv_color_t color)
    : label(label_text), color(color)
{
    Serial.print("Creating ButtonSquare: ");
    Serial.println(label);
}