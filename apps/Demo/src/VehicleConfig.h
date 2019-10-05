/******************************************************************************
VehicleConfig.h

Vehicle configuration for the demo

Serge Ricardo @ RedFabriQ
September 30, 2019

https://github.com/sricardo/VehicleDemo.git
******************************************************************************/

#ifndef VEHICLE_CONFIG_H
#define VEHICLE_CONFIG_H

#define IMU_BUS_TYPE    I2C_MODE
#define IMU_INPUT_ARG   0x6A

#define LIGHTS_BLINK_DURATION 500
#define LIGHTS_PIN              4 // TODO

#define RADIO_PIN 5 // TODO

#define SERVO_FOR_TRUNK_DELAY                   20000
#define SERVO_FOR_TRUNK_DELAY_MAX               1450
#define SERVO_FOR_TRUNK_DELAY_MIN               850
#define SERVO_FOR_TRUNK_DELAY_STEP_FOR_CLOSE    30
#define SERVO_FOR_TRUNK_DELAY_STEP_FOR_OPEN     20
#define SERVO_FOR_TRUNK_PIN                     12

#endif