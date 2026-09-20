# Himmat Stride — Wearable Gait Analysis System

![C++](https://img.shields.io/badge/Firmware-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus)
![Python](https://img.shields.io/badge/Software-Python-3776AB?style=for-the-badge&logo=python)
![Platform](https://img.shields.io/badge/Hardware-ESP32%20%7C%20MPU6050-orange?style=for-the-badge)

An Internet-of-Medical-Things (IoMT) wearable sensing platform designed for multi-node biomechanical gait analysis, rehabilitation tracking, and motion analysis. The system utilizes distributed Inertial Measurement Unit (IMU) sensor nodes connected wirelessly to a central processing hub to capture spatiotemporal and kinematic gait parameters.

---

## 📌 System Architecture

```text
[6x Body IMU Nodes] ---BLE Wireless---> [Central Waist Unit] ---USB/BLE/Wi-Fi---> [Host Device / Web App]
 (Foot, Shank, Thigh)                   (Main MCU + Power)                         (Gait Analytics)
IMU Sensor Nodes: 6x lower-limb nodes (Foot, Shank, Thigh) + 1x optional CoG node reading 6-axis motion data ($a_x, a_y, a_z, g_x, g_y, g_z$)[cite: 5, 7].Central Waist Unit: Master waist-mounted unit handling centralized power distribution and node data aggregation.   Data Pipeline: Telemetry and processing system for calculating joint angles (Hip, Knee, Ankle), gait symmetry, cadence, and phase segmentation (Stance vs. Swing)[cite: 5, 7, 12].
🛠️ Hardware & Technical SpecificationsModuleComponent / ProtocolFunctionSensor ControllerESP32-S3 Mini / ESP32 MiniNode data acquisition & wireless telemetry   Motion SensorMPU6050 (I2C)6-Axis Accelerometer + Gyroscope sensing   Central HubWaist Unit HubMaster control & centralized power routing   CommunicationI2C (Local), BLE/Wi-Fi (Host)Sensor reading and packet transmission   📂 Repository StructurePlaintext├── docs/
│   ├── ARCHITECTURE.md         # Hardware data flow and system design specifications
│   └── HARDWARE_LAYOUT.md      # Pinouts, sensor placement, and power distribution plans
├── firmware/
│   └── esp32_imu_node.cpp      # C++ firmware for ESP32 Mini + MPU6050 I2C acquisition
├── software/
│   └── simulate_session.py     # Python telemetry pipeline simulator & CSV session parser
└── README.md                   # Repository overview
🚀 Getting StartedFirmware SetupOpen firmware/esp32_imu_node.cpp in PlatformIO or Arduino IDE.   Install dependencies: Adafruit_MPU6050, Adafruit_Sensor, and Wire.   Define the target NODE_ID (e.g., 1 for Left Foot, 2 for Right Foot, etc.).   Compile and flash to the ESP32 Mini controller.
