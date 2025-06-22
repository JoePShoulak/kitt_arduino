#include "ble_helper.h"

#include <ArduinoBLE.h>

#include "../ui/tiles/voice_tile.h"
#include "../UI/UI.h"

#define POLLING_RATE 5000

BLEService kittService(BLE_UUID_SERVICE);
BLEStringCharacteristic errorChar(BLE_UUID_ERROR, BLERead | BLENotify, 20);
BLEStringCharacteristic data0(BLE_UUID_DATA_0, BLERead | BLENotify, 20);

int lastUpdated;

bool ble_init()
{
  if (!BLE.begin())
    return false;

  kittService.addCharacteristic(errorChar);
  kittService.addCharacteristic(data0); // voltage (dummy)

  BLE.setLocalName("KITT");
  BLE.setAdvertisedService(kittService);
  BLE.addService(kittService);
  BLE.advertise();

  lastUpdated = millis();

  return true;
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
    data0.writeValue("46.8");
  }
}
