
// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiiChuck.h>
#include <BleKeyboard.h>
#include "Adafruit_Sensor_Calibration.h"

// select either EEPROM or SPI FLASH storage:
#ifdef ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM
  Adafruit_Sensor_Calibration_EEPROM cal;
#else
  Adafruit_Sensor_Calibration_SDFat cal;
#endif
/*
pin scl->c->22
pin sda->z->21
*/
//declacration des bool
bool yjh=false;
bool yjb=false;
bool gxh=false;
bool gxb=false;
bool xjb=false;
bool xjh=false;
bool bc=false;
bool bz=false;
bool gzb=false;
bool gzh=false;
BleKeyboard bleKeyboard;
Accessory nunchuck;
Adafruit_MPU6050 mpu;
void setup() {

   Serial.begin(115200);
   Wire.begin(21, 22, 100000); // sda, scl, clock speed
   Wire.write(0x6B);  // PWR_MGMT_1 register
   Wire.write(0);     // set to zero (wakes up the MPU−6050)
   Wire.endTransmission(true);
   Serial.println("Setup complete");
  bleKeyboard.begin();
	nunchuck.begin();
  mpu.begin();
cal.loadCalibration();

Wire.write(0x3B); // demande de lecture du registre 0x3B
Wire.requestFrom(0x68, 6); // demande de 6 octets au capteur à l'adresse 0x68
int GyX = Wire.read() << 8 | Wire.read(); // lecture des deux premiers octets et combinaison en un entier signé
int GyZ = Wire.read() << 8 | Wire.read(); // lecture des deux octets suivants et combinaison en un entier signé
	if (nunchuck.type == Unknown) {
		nunchuck.type = NUNCHUCK;
	}
  //valeur par default du gy521
  int gx=cal.gyro_zerorate[1];
  int gz=cal.gyro_zerorate[3];
}



void loop() {
   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
   int GyX = Wire.read()  ;
   int GyZ = Wire.read() ;



   Serial.print(GyX); 
   Serial.print(GyZ);



    nunchuck.readData();    // Read inputs and update maps

  Serial.print("X: "); Serial.print(nunchuck.getAccelX());
  Serial.print(" \tY: "); Serial.print(nunchuck.getAccelY()); 
  Serial.print(" \tZ: "); Serial.println(nunchuck.getAccelZ()); 

  Serial.print("Joy: ("); 
  Serial.print(nunchuck.getJoyX());

  Serial.print(nunchuck.getJoyY());


  Serial.print("Button: "); 
  if (nunchuck.getButtonZ()) Serial.print(" Z "); 
  if (nunchuck.getButtonC()) Serial.print(" C "); 

  Serial.println();
  delay(100);


//condition 
int gx;
int gz;
if (nunchuck.getJoyY()< 70){yjb=true;}
if (nunchuck.getJoyY()>180){yjh=true;} 
if (nunchuck.getJoyX() < 70){xjb=true;}
if (nunchuck.getJoyX() > 180){xjh=true;}
if ( GyX<gx-2){gxb=true;}
if (GyX>8){gxh=true;} 
if ( GyZ<gz-2){gzb=true;}
if ( GyZ>8){gzh=true;}
if (nunchuck.getButtonC()){bc=true;}
if (nunchuck.getButtonZ()){bz=true;}

//touche du clavier en fonction des condition
if(yjb) { 
      bleKeyboard.press(KEY_NUM_0); 
       bleKeyboard.releaseAll();
       Serial.print("waza1");}
    delay(100);  
if(yjh) { 
      bleKeyboard.press(KEY_NUM_1); 
       bleKeyboard.releaseAll();
       Serial.print("waza2");}
    delay(100);  
if(xjb) { 
      bleKeyboard.press(KEY_NUM_3); 
       bleKeyboard.releaseAll();
       Serial.print("waza3");}
    delay(100);  
if(xjh) { 
      bleKeyboard.press(KEY_NUM_4); 
       bleKeyboard.releaseAll();
       Serial.print("waza4");}
    delay(100);  

if(bc) { 
      bleKeyboard.press(KEY_NUM_5); 
       bleKeyboard.releaseAll();
       Serial.print("waza5");delay(100);}
    
if(bz) { 
      bleKeyboard.press(KEY_NUM_6); 
       bleKeyboard.releaseAll();
       Serial.print("waza6");delay(100);    }
/*
if(gzb) { 
      bleKeyboard.press(KEY_NUM_2); 
       bleKeyboard.releaseAll();
       Serial.print("waza7");delay(100);}
      
if(gxb) { 
      bleKeyboard.press(KEY_NUM_7); 
       bleKeyboard.releaseAll();
       Serial.print("waza8");}
    delay(100);  
if(gxh) { 
      bleKeyboard.press(KEY_NUM_8); 
       bleKeyboard.releaseAll();
       Serial.print("waza9");}
    delay(100); 
if(gzh) { 
      bleKeyboard.press(KEY_NUM_9); 
       bleKeyboard.releaseAll();
       Serial.print("waza");
    delay(100); }
*/
bool yjh=false;
bool yjb=false;
bool gxh=false;
bool gxb=false;
bool xjb=false;
bool xjh=false;
bool bc=false;
bool bz=false;
bool gzb=false;
bool gzh=false;
  delay(200);



}
