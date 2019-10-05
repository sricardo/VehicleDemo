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

void Vehicle::closeTrunk() const
{
    Serial.print("Closing vehicle's trunk...");

    for (unsigned int delay = SERVO_FOR_TRUNK_DELAY_MIN ; delay <= SERVO_FOR_TRUNK_DELAY_MAX ; delay+=SERVO_FOR_TRUNK_DELAY_STEP_FOR_CLOSE) {
        digitalWrite(SERVO_FOR_TRUNK_PIN, HIGH);
        delayMicroseconds(delay);
        digitalWrite(SERVO_FOR_TRUNK_PIN, LOW);
        delayMicroseconds(SERVO_FOR_TRUNK_DELAY-delay);
    }

    Serial.println("OK");
}

void Vehicle::openTrunk() const
{
    Serial.print("Opening vehicle's trunk...");

    for (unsigned int delay = SERVO_FOR_TRUNK_DELAY_MAX; delay >= SERVO_FOR_TRUNK_DELAY_MIN ; delay-=SERVO_FOR_TRUNK_DELAY_STEP_FOR_OPEN) {
        digitalWrite(SERVO_FOR_TRUNK_PIN, HIGH);
        delayMicroseconds(delay);
        digitalWrite(SERVO_FOR_TRUNK_PIN, LOW);
        delayMicroseconds(SERVO_FOR_TRUNK_DELAY-delay);
    }
    
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