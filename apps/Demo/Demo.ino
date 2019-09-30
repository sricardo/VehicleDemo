/******************************************************************************
Demo.ino

Vehicle interface for the demo

Serge Ricardo @ RedFabriQ
September 27, 2019

Description:
Demonstration application of Kirrk by Mobioos.
All communications are over BLE

Features:
- Trunk commands and status
- Lights management
- Enable/Disable the radio
- Read and send the temperature (unit configurable)
- Read and send pitch and roll
- Shock detection (sensitivity configurable)

https://github.com/sricardo/VehicleDemo.git
******************************************************************************/

#include "src/BLEManager.h"

using namespace demo;

static BLEManager bleManager; // Creates the BLE Manager
static Vehicle vehicle;       // Creates the Vehicle

void setup()
{
}

void loop()
{
}