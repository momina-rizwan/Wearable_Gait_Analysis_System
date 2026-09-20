/**
 * @file main.cpp
 * @brief Himmat Stride — Autonomous Wearable Gait Analysis Node Firmware
 * @author Momina Rizwan
 * 
 * Hardware Platform: ESP32 Mini Controller + MPU6050 6-Axis Motion Sensor
 * Protocol: I2C (Sensor Reading), Serial / BLE (Telemetry Output)
 */

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ==========================================
// 1. HARDWARE CONFIGURATION & NODE IDS
// ==========================================

// Unique Node Identity Assignment
// 1: Left Foot, 2: Right Foot, 3: Left Shank, 4: Right Shank, 5: Left Thigh, 6: Right Thigh
#define NODE_ID 1 

#define SAMPLING_RATE_HZ 50
#define LOOP_DELAY_MS    (1000 / SAMPLING_RATE_HZ)

Adafruit_MPU6050 mpu;

// Structured Telemetry Data Packet
struct IMUDataPacket {
  uint8_t nodeId;
  unsigned long timestamp_ms;
  float ax, ay, az; // Accelerometer readings (m/s^2)
  float gx, gy, gz; // Gyroscope readings (rad/s)
};

// ==========================================
// 2. INITIALIZATION ROUTINES
// ==========================================

void setupHardware() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Wire.begin(); // Standard I2C SDA / SCL

  if (!mpu.begin()) {
    Serial.println("FATAL: MPU6050 IMU sensor initialization failed!");
    while (1) { delay(10); }
  }

  // Configure Sensor Measurement Ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

// ==========================================
// 3. SENSOR DATA ACQUISITION & TELEMETRY
// ==========================================

IMUDataPacket readSensorData() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  IMUDataPacket packet;
  packet.nodeId = NODE_ID;
  packet.timestamp_ms = millis();
  
  packet.ax = accel.acceleration.x;
  packet.ay = accel.acceleration.y;
  packet.az = accel.acceleration.z;
  
  packet.gx = gyro.gyro.x;
  packet.gy = gyro.gyro.y;
  packet.gz = gyro.gyro.z;

  return packet;
}

void transmitTelemetryCSV(const IMUDataPacket& packet) {
  // Serial / BLE Stream Output Format:
  // node_id, timestamp_ms, ax, ay, az, gx, gy, gz
  Serial.print(packet.nodeId); Serial.print(",");
  Serial.print(packet.timestamp_ms); Serial.print(",");
  Serial.print(packet.ax, 3); Serial.print(",");
  Serial.print(packet.ay, 3); Serial.print(",");
  Serial.print(packet.az, 3); Serial.print(",");
  Serial.print(packet.gx, 3); Serial.print(",");
  Serial.print(packet.gy, 3); Serial.print(",");
  Serial.println(packet.gz, 3);
}

// ==========================================
// 4. MAIN SETUP & EXECUTIVE LOOP
// ==========================================

void setup() {
  setupHardware();
}

void loop() {
  unsigned long startTime = millis();

  IMUDataPacket currentPacket = readSensorData();
  transmitTelemetryCSV(currentPacket);

  unsigned long elapsedTime = millis() - startTime;
  if (elapsedTime < LOOP_DELAY_MS) {
    delay(LOOP_DELAY_MS - elapsedTime);
  }
}
