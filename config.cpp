#include <Arduino.h> // for Serial

#include "button.h"
#include "config.h"

void null_btn(lv_event_t *e) {
  Button *self = static_cast<Button *>(lv_event_get_user_data(e));
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
