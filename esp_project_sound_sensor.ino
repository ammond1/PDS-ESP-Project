#include <WiFi.h>
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include <Arduino.h>

// Wi-Fi credentials
const char* ssid = "SUTD_Guest";
const char* password = "";

// Firebase credentials
#define FIREBASE_HOST "fire-base-url"  // Your Firebase Realtime Database URL
#define FIREBASE_AUTH "fire-base-secret"           // Your Firebase Database Secret or API Key
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Sound sensor setup
const int soundSensorPin = 0;   // Analog pin connected to sound sensor (A0)
int soundValue = 0;  // Variable to store the sound sensor value

// Smoothing parameters
const int numReadings = 10;  // Number of readings for smoothing
int readings[numReadings];  // Array to store analog readings
int readIndex = 0;  // Index to keep track of current reading
int total = 0;  // Total of the readings
int average = 0;  // Average of the readings
int baseline = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set the sensor pin as input
  pinMode(soundSensorPin, INPUT);
  // Set segment pins as outputs

  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Set Firebase configuration
  firebaseConfig.database_url = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;  // For Database Secret or API Key

  // Initialize Firebase
  Firebase.reconnectNetwork(true);
  Firebase.begin(&firebaseConfig, &firebaseAuth);

  // Set baseline value
  baseline = analogRead(soundSensorPin) * 20;

  // Initialize all readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }

  Serial.print('ready');
}

void loop() {

    // Subtract the last reading
  total = total - readings[readIndex];

  // Read new sound value
  readings[readIndex] = analogRead(soundSensorPin) * 20 - baseline;
  total = total + readings[readIndex];

  // Update index
  readIndex = (readIndex + 1) % numReadings;

  // Compute average
  average = total / numReadings;

  // Display and Firebase update
  if (average >= 0) {
    Serial.print("Smoothed Sound Value: ");
    Serial.println(average);

    // Push data to Firebase
    String path = "noise_level";
    if (Firebase.RTDB.setInt(&firebaseData, path, average)) {
      Serial.println("Data pushed to Firebase successfully!");
    } else {
      Serial.println("Failed to push data to Firebase");
      Serial.println(firebaseData.errorReason());
    }
  }
}
