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

        /** \brief Initializes the BLE, that is :<br>
         *  - begins initialization
         *  - sets the local name for peripherical advertises
         *  - sets the UUID for the service this peripherical advertises
         *  - adds the characteristics to the services
         *  - adds the services to BLE
         *  - assigns event handlers for connected/disconnected to peripherical
         *  - assigns event handlers for characteristics
         *  - sets initial values for the characteristics
         *  \param BLELocalName the local name for peripherical advertises
         *  \return true if BLE is well initialized, false otherwise
         */
        bool initBLE(const char* BLELocalName);

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

        BLEService device2Mobile; /**< BLE Service for device to mobile communications */
        BLEService mobile2Device; /**< BLE Service for mobile to device communications */

        BLEUnsignedCharCharacteristic   vehicleLightsCommandCharacteristic;             /**< BLE characteristic for vehicle lights command */
        BLEBoolCharacteristic           vehicleRadioCommandCharacteristic;              /**< BLE characteristic for vehicle radio command */
        BLEUnsignedCharCharacteristic   vehicleShockSensitivitySettingCharacteristic;   /**< BLE characteristic for vehicle shock sensitivity setting */
        BLEUnsignedCharCharacteristic   vehicleTemperatureUnitSettingCharacteristic;    /**< BLE characteristic for vehicle temperature unit setting */
        BLEBoolCharacteristic           vehicleTrunkCommandCharacteristic;              /**< BLE characteristic for vehicle trunk command */

        BLEShortCharacteristic          vehiclePitchDataCharacteristic;                 /**< \brief BLE characteristic for vehicle pitch data */
        BLEShortCharacteristic          vehicleRollDataCharacteristic;                  /**< \brief BLE characteristic for vehicle roll data */
        BLEBoolCharacteristic           vehicleShockDetectionDataCharacteristic;        /**< \brief BLE characteristic for vehicle shock detection data */  
        BLEShortCharacteristic          vehicleTemperatureDataCharacteristic;           /**< \brief BLE characteristic for vehicle temperature data */
        BLEUnsignedCharCharacteristic   vehicleTrunkStateDataCharacteristic;            /**< \brief BLE characteristic for vehicle trunk state data */
    };
}

#endif