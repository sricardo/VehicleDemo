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
void Vehicle::setLightsMode(LightsMode mode)
{
    Serial.print("Setting light mode: ");
    lightsMode = mode;

    switch(mode) {
    case LightsMode::OFF:
        Serial.println("OFF");
        break;
    case LightsMode::ON:
        Serial.println("ON");
        break;
    case LightsMode::BLINKING:
        Serial.println("BLINKING");
        break;
    }
}

void Vehicle::applyLightsMode()
{
    static char blinkLedState                   = LOW;
    static unsigned long blinkTime, currentTime = 0;

    switch(lightsMode) {
    case LightsMode::OFF:
        if (blinkLedState == HIGH || blinkTime != 0) {
            blinkLedState = LOW;
            digitalWrite(LIGHTS_PIN, blinkLedState);
            blinkTime = 0;
        }
        break;
    case LightsMode::ON:
        if (blinkLedState == LOW || blinkTime != 0) {
            blinkLedState = HIGH;
            digitalWrite(LIGHTS_PIN, blinkLedState);
            blinkTime = 0;
        }
        break;
    case LightsMode::BLINKING:
        currentTime = millis();

        if (currentTime - blinkTime >= LIGHTS_BLINK_DURATION) {
            blinkLedState = (blinkLedState == LOW) ? HIGH : LOW;
            digitalWrite(LIGHTS_PIN, blinkLedState);
            blinkTime = currentTime;
        }

        break;
    }
}

void Vehicle::disableRadio() const
{
    Serial.print("Disabling vehicle's radio...");
    digitalWrite(RADIO_PIN, LOW);
    Serial.println("OK");
}

void Vehicle::enableRadio() const
{
    Serial.print("Enabling vehicle's radio...");
    digitalWrite(RADIO_PIN, HIGH);
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