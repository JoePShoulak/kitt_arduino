#include "ble_helper.h"

#include <ArduinoBLE.h>

#include "../ui/tiles/voice_tile.h"
#include "../UI/UI.h"

#define POLLING_RATE 5000

BLEService kittService(BLE_UUID_SERVICE);
BLEStringCharacteristic errorChar(BLE_UUID_ERROR, BLERead | BLENotify, 20);
BLEStringCharacteristic voltageChar(BLE_UUID_DATA, BLERead | BLENotify, 20);

int lastUpdated;

void ble_start()
{
  if (!BLE.begin())
  {
    Serial.println("BLE init failed");
    while (1)
      ;
  }

  BLE.setLocalName("KITT");
  kittService.addCharacteristic(errorChar);
  kittService.addCharacteristic(voltageChar);
  BLE.setAdvertisedService(kittService);
  BLE.addService(kittService);
  BLE.advertise();

  lastUpdated = millis();

  Serial.println("BLE error broadcaster started");
}

void ble_update()
{
  BLEDevice central = BLE.central();
  int now = millis();

  if (now - lastUpdated < POLLING_RATE)
    return;

  lastUpdated = now;

  ui.voiceTile->indicators[ble]->toggle(central.connected());

  if (central.connected())
  {
    errorChar.writeValue("Overheat");
    voltageChar.writeValue("46.8");
  }
}
