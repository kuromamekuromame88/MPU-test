#include <Arduino.h>
#include <Wire.h>

#define SDA_PIN 5
#define SCL_PIN 4

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("I2C Scanner start...");

  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("Found device at 0x%02X\n", addr);
      delay(10);
    }
  }

  Serial.println("Scan complete.");
}

void loop() {}
