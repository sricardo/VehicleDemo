/******************************************************************************
BLEConfig.h

BLE configuration for the demo

Serge Ricardo @ RedFabriQ
September 30, 2019

https://github.com/sricardo/VehicleDemo.git
******************************************************************************/

#ifndef BLE_CONFIG_H
#define BLE_CONFIG_H

#define BLE_LOCAL_NAME  "VEHICLE_DEMO"

#define DEVICE_TO_MOBILE_BLE_SERVICE_UUID "444D"
#define MOBILE_TO_DEVICE_BLE_SERVICE_UUID "4D44"

#define VEHICLE_LIGHTS_COMMAND_CHARACTERISTIC               "4C49"
#define VEHICLE_RADIO_COMMAND_CHARACTERISTIC                "5241"
#define VEHICLE_SHOCK_SENSITIVITY_SETTING_CHARACTERISTIC    "5343"
#define VEHICLE_TEMPERATURE_UNIT_SETTING_CHARACTERISTIC     "5554"
#define VEHICLE_TRUNK_COMMAND_CHARACTERISTIC                "434D"

#define VEHICLE_PITCH_DATA_CHARACTERISTIC           "4150"
#define VEHICLE_ROLL_DATA_CHARACTERISTIC            "4152"
#define VEHICLE_SHOCK_DETECTION_DATA_CHARACTERISTIC "4348"
#define VEHICLE_TEMPERATURE_DATA_CHARACTERISTIC     "5450"
#define VEHICLE_TRUNK_STATUS_DATA_CHARACTERISTIC    "4353"

#endif