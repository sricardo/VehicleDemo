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
    /** \brief Lights mode */
    enum LightsMode
    {
        OFF = 0,
        ON = 1,
        BLINKING = 2
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

        /** \brief Sets lights mode
         *  \param mode lights mode to apply
         */
        void setLightsMode(LightsMode mode);
        /** \brief Apply lights mode */
        void applyLightsMode();

        // TODO lights under the vehicle
        // allumage + couleur

        /** \brief Disables the radio */
        void disableRadio() const;
        /** \brief Enables the radio */
        void enableRadio() const;

        /** \brief Applies the shock sensitivity settings to the IMU */
        void applyShockSensitivity();
        /** \brief Gets shock detected value 
         *  \return the shock detected value
         */
        bool getShockDetected() const;
        /** \brief Sets shock detected and time */
        void setShockDetected();
        /** \brief Resets the shock detection */
        void resetShockDetected();

        /** \brief Reads the temperature from the IMU 
         *  \return the temperature, in Celsius or Farenheit, depending on the vehicle settings
         */
        short int readTemperature();

        Settings settings;      /**< Vehicle settings */

    private:
        bool radioON;               /**< Current radio's status */
        bool shockDetected;         /**< Indicates if a shock has been detected */
        unsigned long shockTime;    /**< Last shock time */
        short int pitch;            /**< Current pitch angle */
        short int roll;             /**< Current roll angle */
        short int temperature;      /**< Current temperature */
        LightsMode lightsMode;      /**< Current mode of the lights */
        LSM6DS3 imu;                /**< IMU */
        TrunkState trunkStatus;     /**< Vehicle trunk status */
        unsigned long trunkTimer;   /**< Vehicle trunk timer when opened */    
    };
}

#endif