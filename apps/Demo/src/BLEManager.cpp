#include "BLEManager.h"

using namespace demo;

BLEManager::BLEManager():
    device2Mobile(BLEService(DEVICE_TO_MOBILE_BLE_SERVICE_UUID)),
    mobile2Device(BLEService(MOBILE_TO_DEVICE_BLE_SERVICE_UUID)),
    vehicleIgnitionCommandCharacteristic(BLEBoolCharacteristic(VEHICLE_IGNITION_COMMAND_CHARACTERISTIC, BLEWrite)),
    vehicleLightsCommandCharacteristic(BLEUnsignedCharCharacteristic(VEHICLE_LIGHTS_COMMAND_CHARACTERISTIC, BLEWrite)),
    vehicleShockSensitivitySettingCharacteristic(BLEUnsignedCharCharacteristic(VEHICLE_SHOCK_SENSITIVITY_SETTING_CHARACTERISTIC, BLEWrite)),
    vehicleTemperatureUnitSettingCharacteristic(BLEUnsignedCharCharacteristic(VEHICLE_TEMPERATURE_UNIT_SETTING_CHARACTERISTIC, BLEWrite)),
    vehicleTrunkCommandCharacteristic(BLEBoolCharacteristic(VEHICLE_TRUNK_COMMAND_CHARACTERISTIC, BLEWrite)),
    vehiclePitchDataCharacteristic(BLEShortCharacteristic(VEHICLE_PITCH_DATA_CHARACTERISTIC, BLERead | BLENotify)),
    vehicleRollDataCharacteristic(BLEShortCharacteristic(VEHICLE_ROLL_DATA_CHARACTERISTIC, BLERead | BLENotify)),
    vehicleShockDetectionDataCharacteristic(BLEBoolCharacteristic(VEHICLE_SHOCK_DETECTION_DATA_CHARACTERISTIC, BLERead | BLENotify)),
    vehicleTemperatureDataCharacteristic(BLEShortCharacteristic(VEHICLE_TEMPERATURE_DATA_CHARACTERISTIC, BLERead | BLENotify)),
    vehicleTrunkStateDataCharacteristic(BLEUnsignedCharCharacteristic(VEHICLE_TRUNK_STATUS_DATA_CHARACTERISTIC, BLERead | BLENotify))
{
}

bool BLEManager::initBLE(const char* BLELocalName)
{
    Serial.print("Starting BLE...");

    if (!BLE.begin()) {
        Serial.println("failed");
        return false;
    }

    Serial.println("OK");

    Serial.print("Setting the local name peripherical advertises: ");
    Serial.println(BLELocalName);
    BLE.setLocalName(BLELocalName);
    
    setServicesAndCharacteristics();

    Serial.print("Setting initial values for the characteristic...");
    vehiclePitchDataCharacteristic.writeValue(0);
    vehicleRollDataCharacteristic.writeValue(0);
    vehicleShockDetectionDataCharacteristic.writeValue(false);  
    vehicleTemperatureDataCharacteristic.writeValue(0);
    vehicleTrunkStateDataCharacteristic.writeValue(0);
    Serial.println("OK");

    return true;
}

void BLEManager::sendVehiclePitch(short int pitch)
{
    vehiclePitchDataCharacteristic.writeValue(pitch);
}

void BLEManager::sendVehicleRoll(short int roll)
{
    vehicleRollDataCharacteristic.writeValue(roll);
}
        
void BLEManager::sendVehicleShockDetected(bool shockDetected, bool onlyOnChange)
{
    static bool lastShockDetected = false;

    if (onlyOnChange && (lastShockDetected == shockDetected)) {
        return;
    }

    Serial.print("Sending vehicle's shock detection...");
    vehicleShockDetectionDataCharacteristic.writeValue(shockDetected);
    lastShockDetected = shockDetected;
    Serial.println("OK");
}

void BLEManager::sendVehicleTemperature(short int temperature, bool onlyOnChange)
{
    static short int lastSentTemperature = 0;

    if (onlyOnChange && (lastSentTemperature == temperature)) {
        return;
    }

    Serial.print("Sending vehicle's temperature...");
    vehicleTemperatureDataCharacteristic.writeValue(temperature);
    lastSentTemperature = temperature;
    Serial.println("OK");
}

void BLEManager::sendVehicleTrunkState(TrunkState vehicleTrunkState, bool onlyOnChange)
{
    static TrunkState lastSentTrunkState = TrunkState::CLOSED;

    if (onlyOnChange && (lastSentTrunkState == vehicleTrunkState)) {
        return;
    }

    Serial.print("Sending vehicle's trunk state...");
    vehicleTrunkStateDataCharacteristic.writeValue(vehicleTrunkState);
    lastSentTrunkState = vehicleTrunkState;
    Serial.println("OK");
}

void BLEManager::setServicesAndCharacteristics()
{
    Serial.print("Setting the UUIDs for the services this peripherical advertises...");
    BLE.setAdvertisedService(device2Mobile);
    BLE.setAdvertisedService(mobile2Device);
    Serial.println("OK");

    Serial.print("Adding the characteristics to the services...");
    device2Mobile.addCharacteristic(vehiclePitchDataCharacteristic);
    device2Mobile.addCharacteristic(vehicleRollDataCharacteristic);
    device2Mobile.addCharacteristic(vehicleShockDetectionDataCharacteristic);
    device2Mobile.addCharacteristic(vehicleTemperatureDataCharacteristic);
    device2Mobile.addCharacteristic(vehicleTrunkStateDataCharacteristic);

    mobile2Device.addCharacteristic(vehicleIgnitionCommandCharacteristic);
    mobile2Device.addCharacteristic(vehicleLightsCommandCharacteristic);
    mobile2Device.addCharacteristic(vehicleShockSensitivitySettingCharacteristic);
    mobile2Device.addCharacteristic(vehicleTemperatureUnitSettingCharacteristic);
    mobile2Device.addCharacteristic(vehicleTrunkCommandCharacteristic);
    Serial.println("OK");

    Serial.print("Adding services...");
    BLE.addService(device2Mobile);
    BLE.addService(mobile2Device);
    Serial.println("OK");
}