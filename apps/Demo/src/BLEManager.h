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
        void sendVehiclePitch(short int pitch);
        /** \brief Sends the given roll angle over BLE 
         *  \param roll the given roll
         */
        void sendVehicleRoll(short int roll);
        /** \brief Sends the given shock detection over BLE
         *  \param shockDetected the given shock detection
         *  \param onlyOnChange indicates if data must be sent only if it has changed
         */
        void sendVehicleShockDetected(bool shockDetected, bool onlyOnChange = true);
        /** \brief Sends the given temperature over BLE
         *  \param temperature the given temperature
         *  \param onlyOnChange indicates if data must be sent only if it has changed
         */
        void sendVehicleTemperature(short int temperature, bool onlyOnChange = true);
        /** \brief Sends the given trunk state over BLE 
         *  \param vehicleTrunkState the given trunk state
         *  \param onlyOnChange indicates if data must be sent only if it has changed
         */
        void sendVehicleTrunkState(TrunkState vehicleTrunkState, bool onlyOnChange = true);

        BLEService device2Mobile; /**< BLE Service for device to mobile communications */
        BLEService mobile2Device; /**< BLE Service for mobile to device communications */

        BLEBoolCharacteristic           vehicleIgnitionCommandCharacteristic;           /**< BLE characteristic for vehicle ignition command */
        BLEUnsignedCharCharacteristic   vehicleLightsCommandCharacteristic;             /**< BLE characteristic for vehicle lights command */
        BLEUnsignedCharCharacteristic   vehicleShockSensitivitySettingCharacteristic;   /**< BLE characteristic for vehicle shock sensitivity setting */
        BLEUnsignedCharCharacteristic   vehicleTemperatureUnitSettingCharacteristic;    /**< BLE characteristic for vehicle temperature unit setting */
        BLEBoolCharacteristic           vehicleTrunkCommandCharacteristic;              /**< BLE characteristic for vehicle trunk command */

        BLEShortCharacteristic          vehiclePitchDataCharacteristic;                 /**< \brief BLE characteristic for vehicle pitch data */
        BLEShortCharacteristic          vehicleRollDataCharacteristic;                  /**< \brief BLE characteristic for vehicle roll data */
        BLEBoolCharacteristic           vehicleShockDetectionDataCharacteristic;        /**< \brief BLE characteristic for vehicle shock detection data */  
        BLEShortCharacteristic          vehicleTemperatureDataCharacteristic;           /**< \brief BLE characteristic for vehicle temperature data */
        BLEUnsignedCharCharacteristic   vehicleTrunkStateDataCharacteristic;            /**< \brief BLE characteristic for vehicle trunk state data */
    
    private:
        void setServicesAndCharacteristics();
    };
}

#endif