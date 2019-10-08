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

#define DEVICE_TO_MOBILE_BLE_SERVICE_UUID "f3b877a8-7fd3-4b61-b08f-a7bd82479ca9"
#define MOBILE_TO_DEVICE_BLE_SERVICE_UUID "9a089684-ef6d-4594-84c5-c87585ea7f31"

#define VEHICLE_IGNITION_COMMAND_CHARACTERISTIC             "a2dc4ff1-cd70-4f54-8163-4ac748eef5f0"
#define VEHICLE_LIGHTS_COMMAND_CHARACTERISTIC               "ae07725b-8579-4cc4-ac83-664d473eeed7"
#define VEHICLE_SHOCK_SENSITIVITY_SETTING_CHARACTERISTIC    "c486b8ba-ec6f-49c3-b547-7a4881edbf7a"
#define VEHICLE_TEMPERATURE_UNIT_SETTING_CHARACTERISTIC     "82b76226-bd7d-4199-b3a5-88ead0a9e764"
#define VEHICLE_TRUNK_COMMAND_CHARACTERISTIC                "8cae83cb-c99d-4863-ad70-813bbb6b5bd4"

#define VEHICLE_PITCH_DATA_CHARACTERISTIC           "c62265d6-1eff-4647-917b-95c1917cddc0"
#define VEHICLE_ROLL_DATA_CHARACTERISTIC            "fd8ad5db-c318-4b31-b00d-2f19c4c4b41a"
#define VEHICLE_SHOCK_DETECTION_DATA_CHARACTERISTIC "78732939-3b1b-402f-9ae3-f8e47fc5c4cd"
#define VEHICLE_TEMPERATURE_DATA_CHARACTERISTIC     "3dd8ef5a-a68f-44b7-b899-e3d32cd7cc9f"
#define VEHICLE_TRUNK_STATUS_DATA_CHARACTERISTIC    "fa3c53d4-64d4-4862-8efd-661dcd4fa6bb"

#endif