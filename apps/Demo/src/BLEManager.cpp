#include "BLEManager.h"

using namespace demo;

BLEManager::BLEManager()
{
    Serial.print("Creating BLE Manager...");
    device2Mobile = BLEService(DEVICE_TO_MOBILE_BLE_SERVICE_UUID);
    mobile2Device = BLEService(MOBILE_TO_DEVICE_BLE_SERVICE_UUID);
    Serial.println("OK");;
}

void BLEManager::sendPitch(short int pitch) const
{
    // TODO
    Serial.print("Sending vehicle's pitch...");

    Serial.println("OK");;
}

void BLEManager::sendRoll(short int roll) const
{
    // TODO
    Serial.print("Sending vehicle's roll...");

    Serial.println("OK");;
}
        
void BLEManager::sendVehicleShockDetected(bool shockDetected) const
{
    // TODO
    Serial.print("Sending vehicle's shock detection...");

    Serial.println("OK");;
}

void BLEManager::sendVehicleTemperature(short int temperature) const
{
    // TODO
    Serial.print("Sending vehicle's temperature...");

    Serial.println("OK");;
}

void BLEManager::sendVehicleTrunkState(TrunkState vehicleTrunkState) const
{
    // TODO
    Serial.print("Sending vehicle's trunk state...");

    Serial.println("OK");;
}