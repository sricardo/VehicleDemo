#include "Vehicle.h"

using namespace demo;

Vehicle::Vehicle():
    radioON(false),
    shockDetected(false),
    pitch(0),
    roll(0),
    temperature(0),
    lightsMode(LightsMode::OFF),
    trunkStatus(TrunkState::CLOSED)
{
    settings.shockSensitivity = 0;
    settings.tempUnit = TemperatureUnit::CELSIUS;
}

void Vehicle::openTrunk() const
{
    // TODO
    Serial.print("Opening vehicle's trunk...");

    Serial.println("OK");
}

void Vehicle::closeTrunk() const
{
    // TODO
    Serial.print("Closing vehicle's trunk...");

    Serial.println("OK");
}

void Vehicle::applyLightsMode(LightsMode mode)
{
    // TODO
    lightsMode = mode;
}

void Vehicle::disableRadio() const
{
    // TODO
    Serial.print("Disabling vehicle's radio...");

    Serial.println("OK");
}

void Vehicle::enableRadio() const
{
    // TODO
    Serial.print("Enabling vehicle's radio...");

    Serial.println("OK");
}

bool Vehicle::checkShockDetected() const
{
    // TODO
    return false;
}

void Vehicle::resetShockDetected()
{
    shockDetected = false;
}