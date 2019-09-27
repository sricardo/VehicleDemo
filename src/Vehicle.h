/******************************************************************************
Vehicle.h

Vehicle interface for the demo

Serge Ricardo @ RedFabriQ
September 27, 2019

https://github.com/sricardo/VehicleDemo.git
******************************************************************************/

#ifndef VEHICLE_H
#define VEHICLE_H

#include "Arduino.h"

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
        uint8_t shockSensitivity;
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

        /** \brief Opens the trunk */
        void openTrunk() const;
        /** \brief Closes the trunk */
        void closeTrunk() const;

        /** \brief Applies lights mode */
        void applyLightsMode() const;

        /** \brief Disables the radio */
        void disableRadio() const;
        /** \brief Enables the radio */
        void enableRadio() const;

        
        /** \brief Sends trunk status over BLE */
        void sendTrunkStatus() const;

        /** \brief Checks if a shock has been detected 
         *  \return true if a shock has been detected, false otherwise
         */
        bool checkShockDetected() const;
        /** \brief Resets the shock detection */
        void resetShockDetected();
        /** \brief Sends the shock detection value over BLE */
        void sendShockDetected() const;

        /** \brief Sends the temperature over BLE */
        void sendTemperature() const;

        /** \brief Sends pitch angle over BLE */
        void sendPitch() const;

        /** \brief Sends roll angle over BLE */
        void sendRoll() const;

        Settings settings;      /**< Vehicle settings */

    private:
        bool radioON;           /**< Current radio's status */
        bool shockDetected;     /**< Indicates if a shock has been detected */
        int16_t pitch;          /**< Current pitch angle */
        int16_t roll;           /**< Current roll angle */
        int16_t temperature;    /**< Current temperature */
        LightsMode lightsMode;  /**< Current mode of the lights */
        TrunkState trunkStatus; /**< Vehicle trunk status */
    };
}

#endif