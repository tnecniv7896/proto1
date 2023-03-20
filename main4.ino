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

BleKeyboard bleKeyboard;
Accessory nunchuck;
Adafruit_MPU6050 mpu;
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

void setup(void) {
  Serial.begin(115200);
  bleKeyboard.begin();
	nunchuck.begin();
  
	if (nunchuck.type == Unknown) {
		nunchuck.type = NUNCHUCK;
	}
  //valeur par default du gy521
  int gx=cal.gyro_zerorate[1];
  int gz=cal.gyro_zerorate[3];
}

void loop() {
Serial.println("ui");//verification de la comunication serial usb 
  /* Get new sensor events with the readings */

 Serial.print("JoyX = ");Serial.println(nunchuck.getJoyX());//Joystick axe X
  Serial.print("JoyY = ");Serial.println(nunchuck.getJoyY());//Joystick axe Y
  Serial.print("BoutonZ = ");Serial.println(nunchuck.getButtonZ());//Bouton Z
  Serial.print("BoutonC = ");Serial.println(nunchuck.getButtonC());//Bouton C
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
//condition 
int gx;
int gz;
if (nunchuck.getJoyY()< 70){yjb=true;}
if (nunchuck.getJoyY()>180){yjh=true;} 
if (nunchuck.getJoyX() < 70){xjb=true;}
if (nunchuck.getJoyX() > 180){xjh=true;}
if ( g.gyro.x<gx-2){gxb=true;}
if ( g.gyro.x>gx){gxh=true;} 
if ( g.gyro.z<gz-2){gzb=true;}
if ( g.gyro.z>gz){gzh=true;}
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
       Serial.print("waza5");}
    delay(100);
if(bz) { 
      bleKeyboard.press(KEY_NUM_6); 
       bleKeyboard.releaseAll();
       Serial.print("waza6");}
    delay(100);    
if(gzb) { 
      bleKeyboard.press(KEY_NUM_2); 
       bleKeyboard.releaseAll();
       Serial.print("waza7");}
    delay(100);  
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
       Serial.print("waza");}
    delay(100); 

  delay(200);
}