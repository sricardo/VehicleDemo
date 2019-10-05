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

        /** \brief Closes the trunk */
        void closeTrunk() const;
        /** \brief Opens the trunk */
        void openTrunk() const;


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

        /** \brief Checks if a shock has been detected 
         *  \return true if a shock has been detected, false otherwise
         */
        bool checkShockDetected() const;
        /** \brief Resets the shock detection */
        void resetShockDetected();

        Settings settings;      /**< Vehicle settings */

    private:
        bool radioON;                   /**< Current radio's status */
        bool shockDetected;             /**< Indicates if a shock has been detected */
        short int pitch;                /**< Current pitch angle */
        short int roll;                 /**< Current roll angle */
        short int temperature;          /**< Current temperature */
        LightsMode lightsMode;          /**< Current mode of the lights */
        TrunkState trunkStatus;         /**< Vehicle trunk status */
    };
}

#endif