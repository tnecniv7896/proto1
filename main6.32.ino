#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiiChuck.h>
#include <BleKeyboard.h>
#include <GY521.h>

GY521 sensor(0x68);

uint32_t counter = 0;

/*
pin scl->c->22
pin sda->z->21
*/

BleKeyboard bleKeyboard;
Accessory nunchuck;
Adafruit_MPU6050 mpu;
void setup() {

  Serial.begin(921600);
  Wire.begin(21, 22, 100000);  // sda, scl, clock speed
  Wire.write(0x6B);            // PWR_MGMT_1 register
  Wire.write(0);               // set to zero (wakes up the MPU−6050)
  Wire.endTransmission(1);
  Serial.println("Setup complete");
  bleKeyboard.begin();
  nunchuck.begin();
  mpu.begin();

  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
  //  set calibration values from calibration sketch.
  sensor.axe = 0.574;
  sensor.aye = -0.002;
  sensor.aze = -1.043;
  sensor.gxe = 10.702;
  sensor.gye = -6.436;
  sensor.gze = -0.676;
}



void loop() {
  sensor.read();
  float x = sensor.getAngleX();
  float y = sensor.getAngleY();
  float z = sensor.getAngleZ();

  nunchuck.readData();  // Read inputs and update maps
  Serial.println(x);
  Serial.println(z);

  Serial.print("Button: ");
  if (nunchuck.getButtonZ()) Serial.print(" Z ");
  if (nunchuck.getButtonC()) Serial.print(" C ");

  Serial.println();

  //touche du clavier en fonction des condition
  if (nunchuck.getJoyY() < 70) {
    bleKeyboard.press(KEY_NUM_0);

    Serial.print("waza1");
  }

  if (nunchuck.getJoyX() > 180) {
    bleKeyboard.press(KEY_NUM_1);

    Serial.print("waza2");
  }
  if ((nunchuck.getJoyX() > 180) and (x > 3) ){bleKeyboard.press(KEY_NUM_0);
   delay(10);
  }
  if (nunchuck.getJoyY() > 180) {
      bleKeyboard.press(KEY_NUM_3);

      Serial.print("waza3");
    }

  if (nunchuck.getJoyX() < 70) {
    bleKeyboard.press(KEY_NUM_4);

    Serial.print("waza4");
  }


  if (nunchuck.getButtonC()) {
    bleKeyboard.press(KEY_NUM_5);

    Serial.print("waza5");
  }

  if (nunchuck.getButtonZ()) {
    bleKeyboard.press(KEY_NUM_6);

    Serial.print("waza6");
  }

  if (z < -25) {
    bleKeyboard.press(KEY_NUM_2);

    Serial.print("waza7");
  }

  if (x < -3) {
    bleKeyboard.press(KEY_NUM_7);

    Serial.print("waza8");
  }

  if (x > 3) {
    bleKeyboard.press(KEY_NUM_8);

    Serial.print("waza9");
  }

  if (z > -5) {
    bleKeyboard.press(KEY_NUM_9);

    Serial.print("waza");
  }
  delay(50);
  bleKeyboard.releaseAll();
}
