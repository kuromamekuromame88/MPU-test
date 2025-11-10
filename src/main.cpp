#include <Arduino.h>
#include <Wire.h>
#include <MPU9250_asukiaaa.h>

#define SDA_PIN 7
#define SCL_PIN 6

MPU9250_asukiaaa mySensor;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  Serial.println("MPU9250 check start");
}

void loop() {
  mySensor.accelUpdate();
  mySensor.gyroUpdate();

  Serial.printf("Accel: X:%7.2f Y:%7.2f Z:%7.2f  ",
                mySensor.accelX(), mySensor.accelY(), mySensor.accelZ());
  Serial.printf("Gyro: X:%7.2f Y:%7.2f Z:%7.2f\n",
                mySensor.gyroX(), mySensor.gyroY(), mySensor.gyroZ());
  delay(500);
}
