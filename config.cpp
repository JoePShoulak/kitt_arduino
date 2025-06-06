#include <Arduino.h> // for Serial

#include "buttons.h"
#include "config.h"

void null_btn(lv_event_t *e) {
  ButtonSquare* self = static_cast<ButtonSquare*>(lv_event_get_user_data(e));
  if (self) {
    if (self->isToggleable()) {
      Serial.print("Button ");
      Serial.print(self->isToggled() ? "On: " : "Off: ");
    } else {
      Serial.print("Button pressed: ");
    }
    Serial.println(self->getLabel());
  }
}
