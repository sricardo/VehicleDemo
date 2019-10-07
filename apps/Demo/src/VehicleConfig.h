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

#define IMU_CTRL1_XL    0x60 // ODR_XL = 416 Hz, FS_XL = 2g
#define IMU_TAP_CFG     0x0F // Tap detection on X, Y, Z axis with latch mode
#define IMU_TAP_THS_6D  0x02 // Tap threshold
#define IMU_INT_DUR2    0x0F // Quiet and Shock time windows (1 LSB corresponds to 8/ODR_XL time)
#define IMU_WAKE_UP_THS 0x00 // Single Tap
#define IMU_MD1_CFG     0x40 // Interrupt driven to INT1 pin
#define IMU_INT1_PIN    2    // Pin used for interrupt

#define LIGHTS_BLINK_DURATION 500
#define LIGHTS_PIN              4 // TODO

#define IGNITION_PIN 5 // TODO

#define SERVO_FOR_TRUNK_DELAY                   20000
#define SERVO_FOR_TRUNK_DELAY_MAX               1450
#define SERVO_FOR_TRUNK_DELAY_MIN               850
#define SERVO_FOR_TRUNK_DELAY_STEP_FOR_CLOSE    30
#define SERVO_FOR_TRUNK_DELAY_STEP_FOR_OPEN     20
#define SERVO_FOR_TRUNK_PIN                     12

#define SHOCK_DURATION_IN_MS 3000
#define SHOCK_PIN 2

#define TRUNK_OPEN_DURATION_IN_MS 3000

#endif