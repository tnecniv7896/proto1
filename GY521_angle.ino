//
//    FILE: GY521_angle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read angleX, angleY, angleZ
//    DATE: 2022-06-06

//Libraries used

#include "GY521.h"
#include "BluetoothSerial.h"
//bl
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
//
GY521 sensor(0x68);

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(2);  //  8g
  sensor.setGyroSensitivity(1);   //  500 degrees/s

  sensor.setThrottle();
  Serial.println("start...");

  //  set calibration values from calibration sketch.
  sensor.axe = 0.574;
  sensor.aye = -0.002;
  sensor.aze = -1.043;
  sensor.gxe = 10.702;
  sensor.gye = -6.436;
  sensor.gze = -0.676;
    //bl
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  //
}


void loop()
{
  sensor.read();
  float x = sensor.getAngleX();
  float y = sensor.getAngleY();
  float z = sensor.getAngleZ();
  float haut=0;
  float bas=0;
  float droite=0;
  float gauche=0;
if (100<=x && x>=260){droite=1;}
  else{droite=0;}
if (80<=x && x>=-80){gauche=1;}
if (10<=y && y>=170){haut=1;}
if (80<=y&& y>=-80){bas=1;}
Serial.print(droite);
Serial.print(bas);
Serial.print(haut);
Serial.print(gauche);
//bl
   if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
  //
}






//  -- END OF FILE --
