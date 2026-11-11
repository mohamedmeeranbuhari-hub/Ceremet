#include <Wire.h>

const int MPU_ADDR = 0x68; // The exact address your scanner found
const float CRASH_THRESHOLD_G = 1.5; // Set to 1.5 for the knuckle-tap test!

unsigned long lastCrashTime = 0;
const unsigned long CRASH_COOLDOWN_MS = 5000;

void setup() {
  Serial.begin(115200);
  delay(2000); // Give Serial Monitor time to open
  Serial.println("\n--- ESP32 Awake! ---");

  // Explicitly start the I2C bus on pins 21 (SDA) and 22 (SCL)
  Wire.begin(21, 22);

  // 1. Wake up the MPU-6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // 2. Set the Accelerometer to the maximum 16G range (crucial for crashes)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);  // ACCEL_CONFIG register
  Wire.write(0x18);  // Set bits 3 and 4 to 1 (configures 16G range)
  Wire.endTransmission(true);

  Serial.println("Bare-Metal MPU6050 Initialized! Waiting for impact...");
}

void loop() {
  // Tell the sensor we want to read the acceleration registers
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // Starting register for ACCEL_XOUT_H
  Wire.endTransmission(false);
  
  // Request 6 bytes of data (2 bytes for X, 2 for Y, 2 for Z)
  Wire.requestFrom(MPU_ADDR, 6, true);  

  // Combine the bytes into raw integer values
  int16_t rawX = Wire.read() << 8 | Wire.read();  
  int16_t rawY = Wire.read() << 8 | Wire.read();  
  int16_t rawZ = Wire.read() << 8 | Wire.read();  

  // Convert raw values to actual G-Force
  // At 16G range, the scale factor is exactly 2048
  float gForceX = rawX / 2048.0;
  float gForceY = rawY / 2048.0;
  float gForceZ = rawZ / 2048.0;

  // Calculate total 3D vector impact
  float totalG = sqrt((gForceX * gForceX) + (gForceY * gForceY) + (gForceZ * gForceZ));
  unsigned long currentMillis = millis();

  // Trigger the crash alert
  if (totalG > CRASH_THRESHOLD_G) {
    if (currentMillis - lastCrashTime > CRASH_COOLDOWN_MS) {
      lastCrashTime = currentMillis;
      
      Serial.println("\n============================");
      Serial.println("!!! CRASH DETECTED !!!");
      Serial.print("Impact Force: ");
      Serial.print(totalG);
      Serial.println(" G");
      Serial.println("============================\n");
    }
  }

  delay(2); // Keep loop stable
}