#include <Arduino.h>
#include <button.h>
#include "config.h"
#include <popup.h>
#include "audio_helper.h"
#include "validators.h"

bool null_validate(lv_event_t *e) { return true; }

bool validate_48v(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));

  if (self->isToggled() && motor_btn->isToggled())
  {
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    lv_obj_t *tile = lv_obj_get_parent(grid);
    show_error_popup(tile, "Cannot deactivate 48V MODE while MOTOR is ON");
    audio_play("error.wav");

    return false;
  }

  if (!self->isToggled() && inverter_btn && inverter_btn->isToggled())
  {
    Serial.println("ERROR: Cannot activate 48V MODE while INVERTER is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    lv_obj_t *tile = lv_obj_get_parent(grid);
    show_error_popup(tile, "Cannot activate 48V MODE while INVERTER is ON");
    audio_play("error.wav");

    return false;
  }

  return true;
}

bool validate_motor(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));

  if (!self->isToggled() && !btn48v->isToggled())
  {
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    lv_obj_t *tile = lv_obj_get_parent(grid);
    show_error_popup(tile, "Cannot activate MOTOR while 48V MODE is OFF");
    audio_play("error.wav");

    return false;
  }

  return true;
}

bool validate_inverter(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));

  if (!self->isToggled() && btn48v->isToggled())
  {
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    lv_obj_t *tile = lv_obj_get_parent(grid);
    show_error_popup(tile, "Cannot activate INVERTER while 48V MODE is ON");
    audio_play("error.wav");

    return false;
  }

  return true;
}

bool validate_cruise_mode(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));

  if (self->isToggled())
  {
    audio_play("error.wav"); // TODO: Change this to be a new shorter clip: "but we're already in that mode!"

    return false;
  }

  return true;
}
