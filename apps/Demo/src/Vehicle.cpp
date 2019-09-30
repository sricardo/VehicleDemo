#include "Vehicle.h"

using namespace demo;

Vehicle::Vehicle() : radioON(false), shockDetected(false), pitch(0), roll(0), temperature(0), lightsMode(LightsMode::OFF), trunkStatus(TrunkState::CLOSED)
{
    settings.shockSensitivity = 0;
    settings.tempUnit = TemperatureUnit::CELSIUS;
}

void Vehicle::openTrunk() const
{
    // TODO
}

void Vehicle::closeTrunk() const
{
    // TODO
}

void Vehicle::applyLightsMode() const
{
    // TODO
}

void Vehicle::disableRadio() const
{
    // TODO
}

void Vehicle::enableRadio() const
{
    // TODO
}

void Vehicle::sendTrunkStatus() const
{
    // TODO
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

void Vehicle::sendShockDetected() const
{
    // TODO
}

void Vehicle::sendTemperature() const
{
    // TODO
}

void Vehicle::sendPitch() const
{
    // TODO
}

void Vehicle::sendRoll() const
{
    // TODO
}