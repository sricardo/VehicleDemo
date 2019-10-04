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

#define SERIAL_BAUDRATE 9600

using namespace demo;

static Vehicle vehicle;         // Creates the Vehicle
static BLEManager bleManager;   // Creates the BLE Manager

/** \brief Handler managing connection 
 *  \param central the central connected
 */
void blePeripheralConnectHandler(BLEDevice central)
{
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
}

/** \brief Handler managing disconnection 
 *  \param central the central disconnected
 */
void blePeripheralDisconnectHandler(BLEDevice central)
{
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
}

/** \brief Handler managing vehicle lights command reception
 *  \param central the sender
 *  \param characteristic the characteristic that has received the command
 */
void vehicleLightsCommandCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    unsigned char value = (unsigned char)(*(characteristic.value()));

    Serial.print("Vehicle lights command received: ");

    switch(value) {
    case LightsMode::OFF:
        Serial.println("OFF");
        break;
    case LightsMode::ON:
        Serial.println("ON");
        break;
    case LightsMode::BLINKING:
        Serial.println("BLINKING");
        break;
    default:
        Serial.print(value);
        Serial.println(" (unknown value)");
        return;
    }

    vehicle.applyLightsMode((LightsMode)value);
}

/** \brief Handler managing vehicle radio command reception
 *  \param central the sender
 *  \param characteristic the characteristic that has received the command
 */
void vehicleRadioCommandCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    bool value = characteristic.value();

    Serial.print("Vehicle radio command received: ");

    switch(value) {
    case false:
        Serial.println("OFF");
        vehicle.disableRadio();
        break;
    case true:
        Serial.println("ON");
        vehicle.enableRadio();
        break;
    }
}

/** \brief Handler managing vehicle shock sensitivity setting reception
 *  \param central the sender
 *  \param characteristic the characteristic that has received the command
 */
void vehicleShockSensitivitySettingCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    unsigned char value = (unsigned char)(*(characteristic.value()));

    Serial.print("Vehicle shock sensitivity setting received: ");
    Serial.println(value);

    if (value >= 0 && value <= 100) {
        vehicle.settings.shockSensitivity = value;
    }
}

/** \brief Handler managing vehicle temperature unit setting reception
 *  \param central the sender
 *  \param characteristic the characteristic that has received the command
 */
void vehicleTemperatureUnitSettingCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    unsigned char value = (unsigned char)(*(characteristic.value()));

    Serial.print("Vehicle temperature unit setting received: ");

    switch(value) {
    case TemperatureUnit::CELSIUS:
        Serial.println("CELSIUS");
        break;
    case TemperatureUnit::FARENHEIT:
        Serial.println("FARENHEIT");
        break;
    default:
        Serial.print(value);
        Serial.println(" (unknown value)");
        return;
    }

    vehicle.settings.tempUnit = (TemperatureUnit)value;
}

/** \brief Handler managing vehicle trunk command reception
 *  \param central the sender
 *  \param characteristic the characteristic that has received the command
 */
void vehicleTrunkCommandCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    bool value = characteristic.value();

    Serial.print("Vehicle trunk command received: ");

    switch(value) {
    case false:
        Serial.println("CLOSE");
        vehicle.closeTrunk();
        break;
    case true:
        Serial.println("OPEN");
        vehicle.openTrunk();
        break;
    }
}

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    
    if (bleManager.initBLE(BLE_LOCAL_NAME)) {
        BLE.advertise();
        Serial.println("BLE device active, waiting for connections...");
    } else {
        Serial.println("ERROR: BLE DEVICE IS NOT ACTIVE !!!");
    }

    Serial.print("Assigning event handlers for connected/disconnected to peripherical...");
    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    Serial.println("OK");

    Serial.print("Assigning event handlers for characteristics...");
    bleManager.vehicleLightsCommandCharacteristic.setEventHandler(BLEWritten, vehicleLightsCommandCharacteristicWritten);
    bleManager.vehicleRadioCommandCharacteristic.setEventHandler(BLEWritten, vehicleRadioCommandCharacteristicWritten);
    bleManager.vehicleShockSensitivitySettingCharacteristic.setEventHandler(BLEWritten, vehicleShockSensitivitySettingCharacteristicWritten);
    bleManager.vehicleTemperatureUnitSettingCharacteristic.setEventHandler(BLEWritten, vehicleTemperatureUnitSettingCharacteristicWritten);
    bleManager.vehicleTrunkCommandCharacteristic.setEventHandler(BLEWritten, vehicleTrunkCommandCharacteristicWritten);
    Serial.println("OK");
}

void loop()
{
    BLE.poll();
}