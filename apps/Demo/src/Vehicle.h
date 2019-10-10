/******************************************************************************
Vehicle.h

Vehicle interface for the demo

Serge Ricardo @ RedFabriQ
September 27, 2019

https://github.com/sricardo/VehicleDemo.git
******************************************************************************/

#ifndef VEHICLE_H
#define VEHICLE_H

#include <Arduino.h>
#include <SparkFunLSM6DS3.h>
#include "VehicleConfig.h"

/** \brief Demo elements namespace */
namespace demo
{
    /** \brief Lights color */
    enum LightsColor
    {
        NONE = 0,
        GREEN = 1,
        RED = 2
    };

    /** \brief Lights mode */
    enum LightsMode
    {
        OFF = 0,
        ON = 1,
        BLINKING = 2,
        BLINKING_1S = 3
    };

    /** \brief Temperature unit */
    enum TemperatureUnit
    {
        CELSIUS = 0,
        FARENHEIT = 1
    };

    /** \brief Different possible states of the vehicle trunk */
    enum TrunkState
    {
        CLOSED = 0,
        OPENED = 1,
        OPENING = 2,
        CLOSING = 3
    };

    /** \brief Holds the settings the vehicle uses to do calculations */ 
    struct Settings
    {
        unsigned char shockSensitivity;
        TemperatureUnit tempUnit;
    };

    /** \brief Core operational class of the vehicle interface <br>
     *   Listens to commands and sends metrics over BLE
     */
    class Vehicle
    {
    public:
        /** \brief Constructor */
        Vehicle();
        /** \brief Destructor */
        ~Vehicle() = default;

        /** \brief Initializes IMU for shock detection
         *  \return false if something goes wrong, else otherwise
         */
        bool initIMU();

        /** \brief Closes the trunk */
        void closeTrunk();
        /** \brief Opens the trunk */
        void openTrunk();
        /** \brief Gets the trunk state
         *  \return the trunk state
         */
        TrunkState getTrunkStatus() const;
        /** \brief Close trunk automatically */
        void autoCloseTrunk();

        /** \brief Sets lights HIGH or LOW
         *  \param ulVal HIGH or LOW
         */
        void setLights(uint32_t ulVal) const;
        /** \brief Sets trunk lights
         *  \param color the color to apply
         */
        void setTrunkLights(LightsColor color) const;
        /** \brief Sets lights mode
         *  \param mode lights mode to apply
         */
        void setLightsMode(LightsMode mode);
        /** \brief Apply lights mode */
        void applyLightsMode();

        /** \brief Starts the vehicle */
        void start();
        /** \brief Stops the vehicle */
        void stop();

        /** \brief Applies the shock sensitivity settings to the IMU */
        void applyShockSensitivity();
        /** \brief Reads shock detected value 
         *  \return the shock detected value
         */
        bool readShockDetected(bool resumeLightAfter);
        /** \brief Sets shock detected and time */
        void setShockDetected();
        /** \brief Resets the shock detection */
        void resetShockDetected();

        /** \brief Reads the temperature from the IMU 
         *  \return the temperature, in Celsius or Farenheit, depending on the vehicle settings
         */
        float readTemperature();

        Settings settings; /**< Vehicle settings */

    private:
        /** \brief Computes shock threshold from the sensitivity expressed in percentage to IMU range
         *  \return the computed threshold
         */
        uint8_t computeShockThreshold() const;        

        bool ignitionON;            /**< Current ignition status */
        bool shockDetected;         /**< Indicates if a shock has been detected */
        unsigned long shockTime;    /**< Last shock time */
        short int pitch;            /**< Current pitch angle */
        short int roll;             /**< Current roll angle */
        float temperature;          /**< Current temperature */
        LightsMode lightsMode;      /**< Current mode of the lights */
        LSM6DS3 imu;                /**< IMU */
        TrunkState trunkStatus;     /**< Vehicle trunk status */
        unsigned long trunkTimer;   /**< Vehicle trunk timer when opened */    
    };
}

#endif