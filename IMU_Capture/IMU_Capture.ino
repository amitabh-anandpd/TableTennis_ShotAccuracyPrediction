#include <Arduino_LSM9DS1.h> //to use inertial measurement unit(IMU)

const float motionThreshold = 2.5; // Threshold of significant motion in G's
const int shotDuration = 1000; // Duration of each shot in milliseconds

unsigned long shotStartTime = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Print the header
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // Wait for significant motion to start a shot
  while (shotStartTime == 0) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);
      float aSum = sqrt(aX * aX + aY * aY + aZ * aZ); // Calculate magnitude of acceleration vector
      if (aSum >= motionThreshold) {
        shotStartTime = millis(); // Record start time of shot
        break;
      }
    }
  }

  // Record data for the duration of the shot
  if (millis() - shotStartTime < shotDuration) {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      // Print data in CSV format
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();
    }
  } else {
    // Reset shot start time
    shotStartTime = 0;
  }
}
