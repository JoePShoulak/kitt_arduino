#include "serial_helper.h"

#include <Arduino.h>

#define BAUD_RATE 115200

void serial_init()
{
  Serial.begin(BAUD_RATE); // Initialize Serial
  Serial.println("✅ Serial initialized!");
}

void print_init_status(const char *name, bool status)
{
  if (status)
  {
    Serial.print("✅ ");
    Serial.print(name);
    Serial.println(" Initialized!");
  }
  else
  {
    Serial.print("❌");
    Serial.print(" Failed to initialize ");
    Serial.println(name);
  }
}