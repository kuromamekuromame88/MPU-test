#include <Wire.h>

// ==== ピン定義（自由に変更可能） ====
#define SDA_PIN 5
#define SCL_PIN 4

// ==== MPU9250 定義 ====
#define MPU9250_ADDR 0x68  // AD0=GND の場合
#define ACCEL_XOUT_H 0x3B

void setup() {
  Serial.begin(115200);
  delay(100);

  // I2C初期化
  Wire.begin(SDA_PIN, SCL_PIN);  // <-- ピンをここで指定
  Serial.println("Initializing MPU9250...");

  // 電源管理レジスタ設定（スリープ解除）
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);

  // 加速度レンジ設定（±2g）
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(0x1C);  // ACCEL_CONFIG
  Wire.write(0x00);
  Wire.endTransmission();

  Serial.println("MPU9250 initialized.");
}

void loop() {
  int16_t ax, ay, az;

  // 加速度データ読み取り
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, 6, true);

  if (Wire.available() == 6) {
    ax = (Wire.read() << 8) | Wire.read();
    ay = (Wire.read() << 8) | Wire.read();
    az = (Wire.read() << 8) | Wire.read();

    // ±2g のときのスケールファクタ（16384 LSB/g）
    float accel_scale = 16384.0;
    float ax_g = ax / accel_scale;
    float ay_g = ay / accel_scale;
    float az_g = az / accel_scale;

    Serial.print("Accel X: "); Serial.print(ax_g, 3);
    Serial.print(" g, Y: "); Serial.print(ay_g, 3);
    Serial.print(" g, Z: "); Serial.println(az_g, 3);
  } else {
    Serial.println("I2C read error");
  }

  delay(200);
}
