/******************************************************************************
BLEManager.h

BLE manager for the demo

Serge Ricardo @ RedFabriQ
September 30, 2019

https://github.com/sricardo/VehicleDemo.git
******************************************************************************/

#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <ArduinoBLE.h>
#include "BLEConfig.h"
#include "Vehicle.h"

namespace demo
{
    /** \brief Class managing all BLE communication */
    class BLEManager
    {
    public:
        /** \brief Constructor */
        BLEManager();
        /** \brief Destructor */
        ~BLEManager() = default;

        /** \brief Sends the given pitch angle over BLE
         *  \param pitch the given pitch
         */
        void sendPitch(short int pitch) const;
        /** \brief Sends the given roll angle over BLE 
         *  \param roll the given roll
         */
        void sendRoll(short int roll) const;
        /** \brief Sends the given shock detection over BLE
         *  \param shockDetected the given shock detection
         */
        void sendVehicleShockDetected(bool shockDetected) const;
        /** \brief Sends the given temperature over BLE
         *  \param temperature the given temperature
         */
        void sendVehicleTemperature(short int temperature) const;
        /** \brief Sends the given trunk state over BLE 
         *  \param vehicleTrunkState the given trunk state
         */
        void sendVehicleTrunkState(TrunkState vehicleTrunkState) const;

    private:
        BLEService device2Mobile; /**< BLE Service for device to mobile communications */
        BLEService mobile2Device; /**< BLE Service for mobile to device communications */
    };
}

#endif