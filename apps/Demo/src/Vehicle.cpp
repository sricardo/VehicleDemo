#include "Vehicle.h"

using namespace demo;

Vehicle::Vehicle():
    ignitionON(false),
    shockDetected(false),
    shockTime(0),
    pitch(0),
    roll(0),
    temperature(0),
    lightsMode(LightsMode::OFF),
    imu(IMU_BUS_TYPE, IMU_INPUT_ARG),
    trunkStatus(TrunkState::CLOSED),
    trunkTimer(0)   

{
    settings.shockSensitivity = 0;
    settings.tempUnit = TemperatureUnit::CELSIUS;
}

bool Vehicle::initIMU()
{
    Serial.print("Configuring IMU...");

	if (imu.beginCore() != 0 ) {
		Serial.println("failed (error at beginCore)");
        return false;
	}

	uint8_t errorAccumulator = 0; // Error accumulation variable

    errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, IMU_CTRL1_XL);         	    // 1. Turns on the accelerometer
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, IMU_TAP_CFG);                  // 2. Enables tap detection
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_THS_6D, computeShockThreshold());    // 3. Sets tap threshold
    errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_INT_DUR2, IMU_INT_DUR2);         	    // 4. Sets Quiet and Shock time windows 
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_WAKE_UP_THS, IMU_WAKE_UP_THS);           // 5. Enables single or double tap
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_MD1_CFG, IMU_MD1_CFG);                   // 6. Single tap interrupt

    if (errorAccumulator) {
		Serial.println("failed (problem configuring the device)");
        return false;
	}

    Serial.println("OK");

    return true;
}

void Vehicle::closeTrunk()
{
    Serial.print("Closing vehicle's trunk...");
    trunkStatus = TrunkState::CLOSING;
    setTrunkLights(LightsColor::RED);

    for (unsigned int delay = SERVO_FOR_TRUNK_DELAY_MIN ; delay <= SERVO_FOR_TRUNK_DELAY_MAX ; delay+=SERVO_FOR_TRUNK_DELAY_STEP_FOR_CLOSE) {
        digitalWrite(SERVO_FOR_TRUNK_PIN, HIGH);
        delayMicroseconds(delay);
        digitalWrite(SERVO_FOR_TRUNK_PIN, LOW);
        delayMicroseconds(SERVO_FOR_TRUNK_DELAY-delay);
    }

    trunkStatus = TrunkState::CLOSED;
    Serial.println("OK");
}

void Vehicle::openTrunk()
{
    if (trunkStatus == TrunkState::OPENED || trunkStatus == TrunkState::OPENING) {
        return;
    }

    Serial.print("Opening vehicle's trunk...");
    trunkStatus = TrunkState::OPENING;
    setTrunkLights(LightsColor::GREEN);

    for (unsigned int delay = SERVO_FOR_TRUNK_DELAY_MAX; delay >= SERVO_FOR_TRUNK_DELAY_MIN ; delay-=SERVO_FOR_TRUNK_DELAY_STEP_FOR_OPEN) {
        digitalWrite(SERVO_FOR_TRUNK_PIN, HIGH);
        delayMicroseconds(delay);
        digitalWrite(SERVO_FOR_TRUNK_PIN, LOW);
        delayMicroseconds(SERVO_FOR_TRUNK_DELAY-delay);
    }
    
    trunkStatus = TrunkState::OPENED;
    trunkTimer = millis();
    Serial.println("OK");
}

TrunkState Vehicle::getTrunkStatus() const
{
    return trunkStatus;
}

void Vehicle::autoCloseTrunk()
{
    if ((trunkStatus == TrunkState::OPENED) && ((millis() - trunkTimer) >= TRUNK_OPEN_DURATION_IN_MS)) {
        closeTrunk();
    }
}

void Vehicle::setLightsMode(LightsMode mode)
{
    Serial.print("Setting lights mode: ");
    lightsMode = mode;
    Serial.println(mode);
}

void Vehicle::applyLightsMode()
{
    static uint32_t blinkLedState = LOW;
    static unsigned long blinkTime, blink1sTime, currentTime = 0;

    switch(lightsMode) {
    case LightsMode::OFF:
        if (blinkLedState == HIGH || blinkTime != 0) {
            blinkLedState = LOW;
            blinkTime = 0;
            blink1sTime = 0;
            setLights(blinkLedState);
        }

        break;
    case LightsMode::ON:
        if (blinkLedState == LOW || blinkTime != 0) {
            blinkLedState = HIGH;
            blinkTime = 0;
            blink1sTime = 0;
            setLights(blinkLedState);
        }

        break;
    case LightsMode::BLINKING:
        currentTime = millis();

        if (currentTime - blinkTime >= LIGHTS_BLINK_DURATION) {
            blinkLedState = (blinkLedState == LOW) ? HIGH : LOW;
            blinkTime = currentTime;
            blink1sTime = 0;
            setLights(blinkLedState);
        }

        break;
    case LightsMode::BLINKING_1S:
        currentTime = millis();

        if (blink1sTime == 0 || ((currentTime - blink1sTime) >= LIGHTS_BLINK_1S_PERIOD)) {
            for (uint8_t i = 0; i < 2; i++) {
                setLights(HIGH);
                delay(LIGHTS_BLINK_1S_DURATION);
                setLights(LOW);
                delay(LIGHTS_BLINK_1S_DURATION);
            }

            blink1sTime = currentTime;
        }

        break;
    }
}

void Vehicle::start()
{
    Serial.print("Starting the vehicle...");
    digitalWrite(IGNITION_PIN, HIGH);
    ignitionON = true;
    Serial.println("OK");
}

void Vehicle::stop()
{
    Serial.print("Stopping the vehicle...");
    digitalWrite(IGNITION_PIN, LOW);
    ignitionON = false;
    Serial.println("OK");
}

void Vehicle::applyShockSensitivity()
{
    imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_THS_6D, computeShockThreshold());
}

bool Vehicle::readShockDetected(bool resumeLightAfter)
{
    byte detection;
    
    imu.readRegister(&detection, 0x1C); 

    if (detection &= 0x40) {
        setShockDetected();

        if (trunkStatus != OPENED && trunkStatus != OPENING) { // Blink of the trunk LED in RED to signal a Shock if trunk is not open
            setTrunkLights(LightsColor::RED);
            delay(SHOCK_LIGHTS_BLINK_DURATION);
            setTrunkLights(LightsColor::NONE);
            delay(SHOCK_LIGHTS_BLINK_DURATION);
            setTrunkLights(LightsColor::RED);
            delay(SHOCK_LIGHTS_BLINK_DURATION);
            setTrunkLights(LightsColor::NONE);
            delay(SHOCK_LIGHTS_BLINK_DURATION);

            if (resumeLightAfter) {
                setTrunkLights(LightsColor::RED);
            }
        }
    }
    
    return shockDetected;
}

void Vehicle::setShockDetected()
{
    Serial.print("Set shock detected at ");
    shockDetected = true;
    digitalWrite(LIGHTS_BELLOW_RED, HIGH);
    shockTime = millis();
    Serial.println(shockTime);
}

void Vehicle::resetShockDetected()
{
    if (shockDetected && ((millis() - shockTime) >= SHOCK_DURATION_IN_MS)) {
        shockDetected = false;
	    digitalWrite(LIGHTS_BELLOW_RED, LOW);
        shockTime = 0;
    }
}

float Vehicle::readTemperature()
{
    if (settings.tempUnit == TemperatureUnit::CELSIUS) {
        temperature = imu.readTempC();
    } else {
        temperature = imu.readTempF();
    }
    
    return temperature;
}

uint8_t Vehicle::computeShockThreshold() const
{
    return settings.shockSensitivity == 0 ? 0 : map(settings.shockSensitivity, 1, 100, 15, 1);
}

void Vehicle::setLights(uint32_t ulVal) const
{
    digitalWrite(LIGHTS_FRONT_LEFT_PIN, ulVal);
	digitalWrite(LIGHTS_FRONT_RIGHT_PIN, ulVal);
	digitalWrite(LIGHTS_BACK_LEFT_PIN, ulVal);
	digitalWrite(LIGHTS_BACK_RIGHT_PIN, ulVal);
}

void Vehicle::setTrunkLights(LightsColor color) const
{
    switch(color) {
    case LightsColor::GREEN:
        digitalWrite(TRUNK_LIGHTS_GREEN, HIGH);
        digitalWrite(TRUNK_LIGHTS_RED, LOW);
        break;
    case LightsColor::RED:
        digitalWrite(TRUNK_LIGHTS_GREEN, LOW);
        digitalWrite(TRUNK_LIGHTS_RED, HIGH);
        break;
    default:
        digitalWrite(TRUNK_LIGHTS_GREEN, LOW);
        digitalWrite(TRUNK_LIGHTS_RED, LOW);
        break;
    }
}