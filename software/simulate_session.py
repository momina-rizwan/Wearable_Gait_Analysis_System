"""
Himmat Stride — Telemetry Stream & CSV Parser Simulator
Author: Momina Rizwan
Description: Generates multi-node 6-axis IMU session data streams for gait analysis processing.
"""

import csv
import time
import random

def generate_gait_session(filename="gait_session_log.csv", duration_sec=10, sample_rate_hz=50):
    nodes = {
        1: "Left Foot",
        2: "Right Foot",
        3: "Left Shank",
        4: "Right Shank",
        5: "Left Thigh",
        6: "Right Thigh"
    }

    total_samples = duration_sec * sample_rate_hz
    start_timestamp = int(time.time() * 1000)

    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["node_id", "node_location", "timestamp_ms", "ax", "ay", "az", "gx", "gy", "gz"])

        for step in range(total_samples):
            current_time = start_timestamp + (step * (1000 // sample_rate_hz))

            for node_id, location in nodes.items():
                # Simulated biomechanical gait acceleration and rotational motion
                ax = round(random.uniform(-1.5, 1.5), 3)
                ay = round(9.81 + random.uniform(-0.3, 0.3), 3)
                az = round(random.uniform(-0.8, 0.8), 3)

                gx = round(random.uniform(-20.0, 20.0), 3)
                gy = round(random.uniform(-10.0, 10.0), 3)
                gz = round(random.uniform(-5.0, 5.0), 3)

                writer.writerow([node_id, location, current_time, ax, ay, az, gx, gy, gz])

    print(f"Session dataset successfully generated: '{filename}'")

if __name__ == "__main__":
    generate_gait_session()
