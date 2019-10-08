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
- Start/Stop the vehicle (ignition)
- Lights management
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
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LIGHTS_TRUNK_RED, HIGH);
    digitalWrite(LIGHTS_TRUNK_GREEN, LOW);
}

/** \brief Handler managing disconnection 
 *  \param central the central disconnected
 */
void blePeripheralDisconnectHandler(BLEDevice central)
{
    Serial.print("Disconnected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LIGHTS_TRUNK_RED, LOW);
    digitalWrite(LIGHTS_TRUNK_GREEN, LOW);
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

    vehicle.setLightsMode((LightsMode)value);
}

/** \brief Handler managing vehicle ignition command reception
 *  \param central the sender
 *  \param characteristic the characteristic that has received the command
 */
void vehicleIgnitionCommandCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    bool value = characteristic.value();

    Serial.print("Vehicle ignition command received: ");

    switch(value) {
    case false :                                       //BUG !! ca ne passe jamais à bas.. 
        Serial.println("OFF");
        vehicle.stop();
        break;
    case true:
        Serial.println("ON");
        vehicle.start();
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

    vehicle.applyShockSensitivity();
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


    //Initialisation of the PIN mode
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LIGHTS_FRONT_LEFT_PIN, OUTPUT);
    pinMode(LIGHTS_FRONT_RIGHT_PIN, OUTPUT);
    pinMode(LIGHTS_BACK_LEFT_PIN, OUTPUT);
    pinMode(LIGHTS_BACK_RIGHT_PIN, OUTPUT);
    pinMode(IGNITION_PIN, OUTPUT);
    pinMode(SERVO_FOR_TRUNK_PIN, OUTPUT);
    pinMode(LIGHTS_BELLOW_RED, OUTPUT);
    pinMode(LIGHTS_TRUNK_RED, OUTPUT);
    pinMode(LIGHTS_TRUNK_GREEN, OUTPUT);

    // Put all the PIN to LOW
    digitalWrite(LIGHTS_FRONT_LEFT_PIN,LOW);
    digitalWrite(LIGHTS_FRONT_RIGHT_PIN,LOW);
    digitalWrite(LIGHTS_BACK_LEFT_PIN,LOW);
    digitalWrite(LIGHTS_BACK_RIGHT_PIN,LOW);
    digitalWrite(IGNITION_PIN,LOW);
    digitalWrite(LIGHTS_BELLOW_RED,LOW);
    digitalWrite(LIGHTS_TRUNK_RED,LOW);
    digitalWrite(LIGHTS_FRONT_LEFT_PIN,LOW);
    digitalWrite(LIGHTS_TRUNK_GREEN,LOW); 

    // Put the servo of the trunk to low mode 
    for (unsigned int i = 0 ; i <= 10 ; i+=1) {
        digitalWrite(SERVO_FOR_TRUNK_PIN, HIGH);
        delayMicroseconds(SERVO_FOR_TRUNK_DELAY_MAX);
        digitalWrite(SERVO_FOR_TRUNK_PIN, LOW);
        delayMicroseconds(SERVO_FOR_TRUNK_DELAY-SERVO_FOR_TRUNK_DELAY_MAX );
    }

    if (bleManager.initBLE(BLE_LOCAL_NAME)) {
        Serial.println("BLE device active, waiting for connections...");
    } else {
        Serial.println("ERROR: BLE DEVICE IS NOT ACTIVE !!!");
        return;
    }

    Serial.print("Assigning event handlers for connected/disconnected to peripherical...");
    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    Serial.println("OK");

    Serial.print("Assigning event handlers for characteristics...");
    bleManager.vehicleIgnitionCommandCharacteristic.setEventHandler(BLEWritten, vehicleIgnitionCommandCharacteristicWritten);
    bleManager.vehicleLightsCommandCharacteristic.setEventHandler(BLEWritten, vehicleLightsCommandCharacteristicWritten);
    bleManager.vehicleShockSensitivitySettingCharacteristic.setEventHandler(BLEWritten, vehicleShockSensitivitySettingCharacteristicWritten);
    bleManager.vehicleTemperatureUnitSettingCharacteristic.setEventHandler(BLEWritten, vehicleTemperatureUnitSettingCharacteristicWritten);
    bleManager.vehicleTrunkCommandCharacteristic.setEventHandler(BLEWritten, vehicleTrunkCommandCharacteristicWritten);
    Serial.println("OK");

    BLE.advertise();
    vehicle.initIMU();
}

void loop()
{
    BLE.poll();
    bleManager.sendVehicleShockDetected(vehicle.readShockDetected(), true);
    bleManager.sendVehicleTemperature(vehicle.readTemperature(), true);
    bleManager.sendVehicleTrunkState(vehicle.getTrunkStatus(), true);
    vehicle.applyLightsMode();
    vehicle.autoCloseTrunk();
    vehicle.resetShockDetected();
    
}
