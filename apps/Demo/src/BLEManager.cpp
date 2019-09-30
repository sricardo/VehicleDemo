#include "BLEManager.h"

using namespace demo;

BLEManager::BLEManager(const char* BLELocalName)
{
    Serial.println("Creating BLE Manager...");
    Serial.print("Starting BLE...");

    if (!BLE.begin()) {
        Serial.println("failed");
    } else {
        Serial.println("OK");

        Serial.print("Creating BLE services...");
        device2Mobile = BLEService(DEVICE_TO_MOBILE_BLE_SERVICE_UUID);
        mobile2Device = BLEService(MOBILE_TO_DEVICE_BLE_SERVICE_UUID);
        Serial.println("OK");
        
        Serial.print("Setting advertised local name and service UUIDs...");
        BLE.setLocalName(BLELocalName);
        BLE.setAdvertisedService(device2Mobile);
        BLE.setAdvertisedService(mobile2Device);
        Serial.println("OK");

        Serial.println("BLE Manager created");
    }

    
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