/******************************************************************************
Adaptation du code de sparkfun pour la Tap. Croisé avec les exemple de STM32
******************************************************************************/

#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

LSM6DS3 myIMU( I2C_MODE, 0x6A );




void setup()
{
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Initialisation");

  Configuration_IMU_TAP(); 
}




void loop()
{
   if (IMU_Tap_Detection()){Serial.println("Tap detectée !");}
	 delay(30);  
}



bool Configuration_IMU_TAP()   // Return 1 si erreur, 0 sinon. 
{
  Wire.begin();
  Wire.setClock(400000);  //Met le I2C a 400kHz

  //Error accumulation variable
  uint8_t errorAccumulator = 0;

  // Configure the IMU
  errorAccumulator += myIMU.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, 0x60);  // ODR_XL = 416 Hz, FS_XL = ±2 g  ou mettre "dataToWrite"

  // Enable tap detection on X, Y, Z axis
  errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_TAP_CFG1, 0x0F ); //0x0F pour configurer le latch mode + affecter un pin avec la la commande suivant :
  errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_MD1_CFG, 0x40 );   //Affect l'interrupt 1, juste pour garder les valeurs dans le registre (Latch mode). 
  
  // Set tap threshold --> Write into TAP_THS_6D
  errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_TAP_THS_6D, 0x02 ); //Seuil : entre 1 et 31 (1F), 0 = pas de detection
  
  // Single & Double tap enabled (SINGLE_DOUBLE_TAP = 1) --> Write into WAKE_UP_THS
  errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_WAKE_UP_THS, 0x00 ); //Configure la Double et single Tap (=0x80) ou juste le Single Tap (=0x00) 
  
  // Set Duration, Quiet and Shock time windows --> Write into INT_DUR2
  errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_INT_DUR2, 0x0F );  //Valeur de SHOCK = durée maximal de la tap (1 LSB corresponds to 8/ODR_XL time) 

  if( errorAccumulator )
  {
    return 1 ; 
  }
  else
  {
    return 0 ; 
  }   
}

bool IMU_Tap_Detection()  //Return 1 si Tap, return 0 si pas de tap. 
{
    byte detection = 0;
    myIMU.readRegister(&detection, 0x1C); 

    if (detection &= 0x40){
      return 1 ;
    }
    else {
      return 0 ;
    }
}


bool Change_tap_TH(int TH) // Return 1 si erreur, 0 sinon.
{
  uint8_t errorAccumulator = 0;
  switch (TH){
  case 0 : 
     errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_TAP_THS_6D, 0x00 ); //Seuil : entre 1 et 31 (1F), 0 = pas de detection
  break;
  case 25 : 
     errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_TAP_THS_6D, 0x0E ); //Seuil : entre 1 et 31 (1F), 0 = pas de detection
  break;
  case 75 : 
     errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_TAP_THS_6D, 0x07 ); //Seuil : entre 1 et 31 (1F), 0 = pas de detection
  break;
  case 100 : 
     errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_TAP_THS_6D, 0x01 ); //Seuil : entre 1 et 31 (1F), 0 = pas de detection
  break;
  }
  
  if( errorAccumulator )
  {
    return 1 ; 
  }
  else
  {
    return 0 ; 
  }  
}
