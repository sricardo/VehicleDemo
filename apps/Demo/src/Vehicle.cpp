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

    errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, IMU_CTRL1_XL);         	// 1. Turns on the accelerometer
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, IMU_TAP_CFG);          // 2. Enables tap detection
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_THS_6D, IMU_TAP_THS_6D);     // 3. Sets tap threshold
    errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_INT_DUR2, IMU_INT_DUR2);         	// 4. Sets Quiet and Shock time windows 
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_WAKE_UP_THS, IMU_WAKE_UP_THS);   // 5. Enables single or double tap
	errorAccumulator += imu.writeRegister(LSM6DS3_ACC_GYRO_MD1_CFG, IMU_MD1_CFG);           // 6. Single tap interrupt

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

    digitalWrite(LIGHTS_TRUNK_RED, HIGH);
    digitalWrite(LIGHTS_TRUNK_GREEN, LOW);

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
    Serial.print("Opening vehicle's trunk...");
    trunkStatus = TrunkState::OPENING;

    digitalWrite(LIGHTS_TRUNK_RED, LOW);
    digitalWrite(LIGHTS_TRUNK_GREEN, HIGH);

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
            digitalWrite(LIGHTS_FRONT_LEFT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_FRONT_RIGHT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_BACK_LEFT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_BACK_RIGHT_PIN,blinkLedState);
            blinkTime = 0;
        }
        break;
    case LightsMode::ON:
        if (blinkLedState == LOW || blinkTime != 0) {
            blinkLedState = HIGH;
            digitalWrite(LIGHTS_FRONT_LEFT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_FRONT_RIGHT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_BACK_LEFT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_BACK_RIGHT_PIN,blinkLedState);
            blinkTime = 0;
        }
        break;
    case LightsMode::BLINKING:
        currentTime = millis();

        if (currentTime - blinkTime >= LIGHTS_BLINK_DURATION) {
            blinkLedState = (blinkLedState == LOW) ? HIGH : LOW;
            digitalWrite(LIGHTS_FRONT_LEFT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_FRONT_RIGHT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_BACK_LEFT_PIN, blinkLedState);
	    digitalWrite(LIGHTS_BACK_RIGHT_PIN,blinkLedState);
            blinkTime = currentTime;
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
    uint8_t threshold = 31.0/100.0*settings.shockSensitivity;
    uint8_t errorAccumulator = imu.writeRegister(LSM6DS3_ACC_GYRO_TAP_THS_6D, threshold);
}

bool Vehicle::readShockDetected()
{
    byte detection;
    
    imu.readRegister(&detection, 0x1C); 

    if (detection &= 0x40) {
        shockDetected = true;
	
	// Blink of the trunk LED in RED to signal a Shock 
	digitalWrite(LIGHTS_TRUNK_RED, HIGH);
    	digitalWrite(LIGHTS_TRUNK_GREEN, LOW);
  	delay(LIGHTS_BLINK_SHOCK_DURATION);

	digitalWrite(LIGHTS_TRUNK_RED, LOW);
    	digitalWrite(LIGHTS_TRUNK_GREEN, LOW);
  	delay(LIGHTS_BLINK_SHOCK_DURATION);

	digitalWrite(LIGHTS_TRUNK_RED, HIGH);
    	digitalWrite(LIGHTS_TRUNK_GREEN, LOW);
  	delay(LIGHTS_BLINK_SHOCK_DURATION);

	digitalWrite(LIGHTS_TRUNK_RED, LOW);
    	digitalWrite(LIGHTS_TRUNK_GREEN, LOW);
  	delay(LIGHTS_BLINK_SHOCK_DURATION);

	// REMETTRE A L'ETAT PRECEDENT !!!! 
	

    } else {
        shockDetected = false;
    }

    return shockDetected;
}

void Vehicle::setShockDetected()
{
    shockDetected = true;
    digitalWriteLIGHTS_BELLOW_RED, HIGH);
    shockTime = millis();
}

void Vehicle::resetShockDetected()
{
    if (shockDetected && ((millis() - shockTime) >= SHOCK_DURATION_IN_MS)) {
        shockDetected = false;
	digitalWriteLIGHTS_BELLOW_RED, LOW);
        shockTime = 0;
    }
}

short int Vehicle::readTemperature()
{
    if (settings.tempUnit == TemperatureUnit::CELSIUS) {
        temperature = imu.readTempC();
    } else {
        temperature = imu.readTempF();
    }
    
    return temperature;
}

