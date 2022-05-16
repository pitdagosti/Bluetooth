#include <ArduinoBLE.h>
#include "Nicla_System.h"
using namespace nicla;

BLEService NiclaService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic NiclaCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
//BLEDescriptor NiclaDescriptor("19B10001-E8F2-537E-4F6C-D104768A1214", 0x00, 127);
void setup() {
  Serial.begin(9600);
  begin();
  leds.begin();
  //while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Nicla");
  BLE.setAdvertisedService(NiclaService);

  // add the characteristic to the service
  NiclaService.addCharacteristic(NiclaCharacteristic);
  //NiclaCharacteristic.addDescriptor(NiclaDescriptor);

  // add service
  BLE.addService(NiclaService);

  // set the initial value for the characeristic:
  NiclaCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE Nicla Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  int blue = 128;
  int green = 73;
  int red = 255;
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (NiclaCharacteristic.written()) {
        if (NiclaCharacteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          leds.setColor(blue, green, red);    // will turn the LED on
        } else {                              // a 0 value
          Serial.println(F("LED off"));
          leds.setColor(off);                 // will turn the LED off
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
